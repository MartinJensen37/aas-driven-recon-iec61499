"""The skill service: matching, planning and checking on the AASs an AAS server holds, for the web
UI's Process Sequence module and its skill editor (``modreg serve --basyx <AAS server>``).

HTTP (JSON):

    POST   /match               which resources offer what a step requires (modreg.match): {"requirements":
                                [{"name", "reference"}], "parameters": [the recipe's], "aasIds": [...]};
                                a reference is a model reference to a product's required capability on
                                the AAS server, or an external one naming its meaning. Per resource
                                (default: every AAS offering a capability) match, mismatch or unknown
                                with the reasons (matches), the AASs a skill can be planned on
                                (candidates), and the capability and values a plan or a check is asked
                                with (requirement)
    POST   /plan/<shell>        plan a composite skill: {"capability": "Filling", "values": {"FillVolume":
                                2.0}, "results": ["FillWeight"], "name": "FillTwo", "write": true}; the
                                steps and the flow, and with write the skill described on the AAS server
                                and the module's offered capabilities derived anew. The capability may
                                be one the module does not offer, narrower than one it does
                                (BottomUpFilling): planned as the vocabulary defines it, and every plan
                                checked in time against the requirement first. A value may be text: a
                                number written as text is a number, other text the planner ignores
                                where it uses none
    POST   /check/<shell>       the checker's findings on the module's composite skills (modplan); the
                                body may hold {"skill": <a skill element as the editor has it>}, checked
                                in its place, and a requirement {"capability": "BottomUpFilling",
                                "values": {...}}: each skill run in time with the product's geometry and
                                checked against what the capability keeps (its bounds the values give)
    POST   /capabilities/<shell>  derive a module's offered capabilities anew from its skills, on the
                                  AAS server, and put them back (the skill editor, after saving)
    GET    /vocabulary/<name>   a capability class of the lab's vocabulary: its label, whether a product
                                can require it, the classes it narrows, itself first (lineage), and the
                                results it can give (FillWeight)
    POST   /process/<product>   the product's process AAS on its line, from the bindings the planner
                                saved in its recipe, written to the AAS server with the plan check's
                                result as its Validation; the body may hold {"line": ..., "status": ...}
    GET    /health

``<shell>`` is a module's AAS, by its id or idShort. What the service does not do is answered with
an HTTP status that says why, and {"error", "step", "reasons"}.
"""
from __future__ import annotations

import base64
import copy
from dataclasses import asdict
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
import math
import urllib.error
import urllib.parse
import urllib.request

from modplan.check import check
from modplan.compose import compose, planned, requiring
from modplan.lift import flow, parts
from modplan.plan import NoPlan, start_state
from modplan.read import read
from modplan.vocabulary import LAB, Vocabulary
from modsync.aasjson import at, children, submodel
from modsync.described import NotDescribed, described
from modsync.sources import environments, load, store
from rdflib import OWL, RDF

from . import match as matching
from .offer import capabilities
from .process import SYSTEM, NotBound, line_for, process_of
from .profile import OFFERED_SET


class Refused(Exception):
    """A request the service did not carry out: the HTTP status that says why, the step it stopped
    at, and the reasons."""

    def __init__(self, status: int, step: str, reasons: list[str]):
        super().__init__(f"{step}: {reasons[0] if reasons else ''}")
        self.status, self.step, self.reasons = status, step, reasons


def b64(identifier: str) -> str:
    """Identifier as the AAS HTTP API expects it in a path (base64url, no padding)."""
    return base64.urlsafe_b64encode(identifier.encode()).decode().rstrip("=")


def mapped_last(items: list[dict]) -> list[dict]:
    """AASs, or their profiles, in the order to publish them: those with a mapping configuration (a
    module's AIMC, which refers to its components' Operations) after the others. The DMP resolves a
    mapping when it reads the AIMC and does not come back to one whose references were missing."""
    def holds(item: dict) -> bool:
        return (any(sm.get("idShort") == "AssetInterfacesMappingConfiguration" for sm in item.get("submodels", []))
                or bool(item.get("asset_interfaces_mapping_configuration")))
    return sorted(items, key=holds)


def given(values) -> dict:
    """The values a plan is asked with, as the planner takes them: a number written as text is a
    number, a value not given (null, NaN, empty) is left out, other text stays text (the planner
    ignores what it does not use)."""
    found = {}
    for name, value in (values.items() if isinstance(values, dict) else ()):
        if isinstance(value, str):
            value = matching.typed(value)
        if value is None or (isinstance(value, float) and math.isnan(value)):
            continue
        found[name] = value
    return found


class AasServer:
    """An AAS repository with the HTTP API of the AAS specification part 2 (BaSyx AAS environment)."""

    def __init__(self, url: str, timeout: float = 10):
        self.url, self.timeout = url.rstrip("/"), timeout

    def call(self, method: str, path: str, body: dict | None = None) -> int:
        data = json.dumps(body).encode() if body is not None else None
        request = urllib.request.Request(f"{self.url}/{path}", data, method=method,
                                         headers={"Content-Type": "application/json"})
        try:
            with urllib.request.urlopen(request, timeout=self.timeout) as response:
                return response.status
        except urllib.error.HTTPError as e:
            if e.code == 404:
                return 404
            raise RuntimeError(f"{method} {self.url}/{path}: HTTP {e.code} {e.read()[:300]!r}") from e
        except OSError as e:
            raise RuntimeError(f"{method} {self.url}/{path}: {e}") from e

    def get(self, path: str, query: dict | None = None):
        """What the server holds at ``path`` (JSON); None if it holds nothing there."""
        url = f"{self.url}/{path}" + (f"?{urllib.parse.urlencode(query)}" if query else "")
        try:
            with urllib.request.urlopen(urllib.request.Request(url, headers={"Accept": "application/json"}),
                                        timeout=self.timeout) as response:
                return json.loads(response.read())
        except urllib.error.HTTPError as e:
            if e.code == 404:
                return None
            raise RuntimeError(f"GET {url}: HTTP {e.code} {e.read()[:300]!r}") from e
        except (OSError, ValueError) as e:
            raise RuntimeError(f"GET {url}: {e}") from e

    def listing(self, kind: str, query: dict | None = None) -> list[dict]:
        """Every item of a kind (shells, submodels) the server holds, page by page."""
        found, cursor = [], None
        while True:
            page = self.get(kind, {"limit": 200, **(query or {}), **({"cursor": cursor} if cursor else {})}) or {}
            found += page.get("result") or []
            cursor = (page.get("paging_metadata") or {}).get("cursor")
            if not cursor:
                return found

    def put(self, kind: str, item: dict) -> str:
        """Replace the item, or create it if the server does not have it."""
        if self.call("PUT", f"{kind}/{b64(item['id'])}", item) != 404:
            return f"PUT {kind} {item['id']}"
        self.call("POST", kind, item)
        return f"POST {kind} {item['id']}"

    def publish(self, env: dict) -> list[str]:
        """Create or replace the shells and submodels of an AAS environment; what was done."""
        # Submodels first: a shell that is visible has its submodels. The mapping configuration last:
        # the DMP resolves its references when it reads it (see ``mapped_last``).
        submodels = sorted(env.get("submodels", []), key=lambda sm: sm.get("idShort") == "AssetInterfacesMappingConfiguration")
        return [*[self.put("submodels", sm) for sm in submodels],
                *[self.put("shells", shell) for shell in env.get("assetAdministrationShells", [])]]


class SkillService:
    """What the service does, on the AASs of the AAS server ``server`` (None: none given, so only the
    vocabulary is answered)."""

    def __init__(self, server: AasServer | None = None):
        self.server = server

    def derive(self, shell: str) -> dict:
        """The offered capabilities of a module on the AAS server derived anew from its skills and
        those of its components (``modreg.offer.capabilities``), and put back: after the skill
        editor saved the Skills submodel, or a skill was built."""
        module, components = self.module(shell, "derive")
        derived = capabilities(module, components)
        stored = store(self.server.url, derived, module)
        found = []
        for box in children(at(submodel(derived, "CapabilityDescription"), OFFERED_SET)):
            capability = at(box, "Capability")
            relation = next(iter(children(at(box, "CapabilityRelations"))), {})
            found.append({"idShort": box["idShort"],
                          "capability": capability["supplementalSemanticIds"][0]["keys"][0]["value"],
                          "skill": (relation.get("second") or {}).get("keys", [{}])[-1].get("value"),
                          **{q["type"]: q["value"] for q in capability.get("qualifiers", [])
                             if q["type"] in ("Derived", "Availability")}})
        return {"shell": derived["assetAdministrationShells"][0]["idShort"], "stored": stored, "capabilities": found}

    def match(self, request: dict) -> dict:
        """How the resources on the AAS server answer a step's required capabilities (``modreg.match``):
        per resource match, mismatch or unknown with the reasons, the capabilities it answers with and
        whether a reconfiguration builds their skills first; with one requirement the AASs a skill can
        be planned on, and the capability and values a plan or a check is asked with. ``request``:
        {"requirements": [{"name", "reference"}], "parameters": [the recipe's, as the web UI holds
        them], "aasIds": [the resources; default every AAS that offers a capability]}."""
        if self.server is None:
            raise Refused(400, "match", ["the service has no AAS server (--basyx) to read the resources from"])
        wanted, ids = request.get("requirements"), request.get("aasIds")
        if not isinstance(wanted, list) or not all(isinstance(r, dict) for r in wanted) or not isinstance(ids, (list, type(None))):
            raise Refused(400, "match", ["requirements: a list of {name, reference}; aasIds: a list of AAS ids"])
        try:
            shells = self.server.listing("shells")
            held = {s["id"]: s for s in self.server.listing("submodels", {"semanticId": b64(matching.DESCRIPTION)})}
            # A requirement in a submodel not marked a Capability Description is read by its id.
            for keys in [(r.get("reference") or {}).get("keys") or [] for r in wanted]:
                if keys and keys[0].get("type") == "Submodel" and keys[0].get("value") not in held:
                    found = self.server.get(f"submodels/{b64(str(keys[0]['value']))}")
                    if found is not None:
                        held[found["id"]] = found
        except RuntimeError as e:
            raise Refused(502, "match", [f"the AAS server was not read: {e}"]) from e
        envs = [{"assetAdministrationShells": [shell],
                 "submodels": [held[ref["keys"][0]["value"]] for ref in shell.get("submodels") or [] if ref["keys"][0]["value"] in held]}
                for shell in shells]
        owned = {s["id"] for env in envs for s in env["submodels"]}
        envs += [{"assetAdministrationShells": [{}], "submodels": [s]} for k, s in held.items() if k not in owned]
        requirements = [matching.required(r.get("reference"), envs, str(r.get("name") or "")) for r in wanted]
        parameters = [matching.Parameter.from_json(p) for p in request.get("parameters") or [] if isinstance(p, dict)]
        by_id = {env["assetAdministrationShells"][0].get("id"): env for env in envs}
        resources = [by_id[i] for i in dict.fromkeys(ids) if i in by_id] if ids is not None else envs
        matches = matching.match(requirements, resources, parameters)
        one = requirements[0] if len(requirements) == 1 and requirements[0].meanings else None
        return {"matches": [m.json() for m in matches],
                "candidates": matching.candidates(one, matches, resources) if one else [],
                "requirement": {"capability": matching.local(one.meanings[0]), "values": matching.values(one, parameters)}
                if one else None}

    def module(self, shell: str, step: str) -> tuple[dict, list[dict]]:
        """A module's AAS and its components' from the AAS server."""
        if self.server is None:
            raise Refused(400, step, ["the service has no AAS server (--basyx) to read the module from"])
        try:
            return load(self.server.url, shell)
        except NotDescribed as e:
            raise Refused(404, step, [str(e)]) from e

    def check_skills(self, shell: str, edited: dict | None = None, requirement: dict | None = None) -> dict:
        """What does not hold in the composite skills of a module on the AAS server, run through the
        states (``modplan.check``): per skill, each finding with the skills that would fix it.
        ``edited`` is a skill as the editor holds it, not saved yet: it is checked in place of the
        skill of its name. ``requirement`` ({"capability", "values"}): each skill is run from the
        state that requirement starts from (the product's geometry) and checked against what the
        capability keeps."""
        if edited is not None and not (isinstance(edited, dict) and edited.get("idShort")):
            raise Refused(400, "check", ["the skill to check is an element of the Skills submodel, with its idShort"])
        module, components = self.module(shell, "check")
        if edited is not None:
            module = copy.deepcopy(module)
            skills = submodel(module, "Skills")
            elements = skills.setdefault("submodelElements", [])
            elements[:] = [e for e in elements if e.get("idShort") != edited.get("idShort")] + [edited]
        try:
            domain, composites = read(module, components), described(module, components).composites
            against = {}
            if requirement and requirement.get("capability"):
                capability, values = requirement["capability"], requirement.get("values") or {}
                domain = requiring(domain, capability)
                against = {"start": start_state(domain, capability, values), "task": domain.capabilities[capability],
                           "values": values}
        except NoPlan as e:
            raise Refused(422, "check", [str(e)]) from e
        except (NotDescribed, ValueError, KeyError) as e:
            raise Refused(422, "check", [str(e)]) from e
        names = [edited["idShort"]] if edited is not None else list(composites)
        return {"shell": shell, "skills": {name: [asdict(f) for f in check(domain, composites[name], **against)] for name in names}}

    def plan(self, shell: str, request: dict) -> dict:
        """A new composite skill planned for a capability of a module on the AAS server (``modplan``):
        its steps and its flow; with ``write`` the skill described on the server, as the skill editor
        saves one (the synchroniser builds it), and the module's offered capabilities derived anew
        (``derived``, as ``derive`` answers)."""
        capability, values = request.get("capability"), given(request.get("values"))
        results = tuple(request.get("results") or ())
        if not capability:
            raise Refused(400, "plan", ["name the capability to plan"])
        module, components = self.module(shell, "plan")
        try:
            domain, steps = planned(read(module, components), capability, values, results)
            found = {"shell": shell, "capability": capability, "flow": flow(domain, steps),
                     "steps": [{"skill": domain.capabilities[p.capability].skill, "capability": p.capability,
                                "component": domain.capabilities[p.capability].component, "args": p.args,
                                **({"along": s.capability} if p is not s else {})}
                               for s in steps for p in parts(s)]}
            if request.get("write"):
                composed = compose(module, components, capability, values, results, request.get("name"))
                found.update(name=composed.name, stored=store(self.server.url, composed.module, module))
        except NoPlan as e:
            raise Refused(422, "plan", [str(e)]) from e
        except (NotDescribed, ValueError) as e:
            raise Refused(422, "plan", [str(e)]) from e
        if request.get("write"):
            # Whoever planned it (the skill editor, Match and plan) is told what the module offers now.
            try:
                found["derived"] = self.derive(shell)
            except Refused as e:
                found["derived"] = {"error": str(e), "reasons": e.reasons}
        return found

    @staticmethod
    def vocabulary(name: str) -> dict:
        """A capability class of the lab's vocabulary: its label, whether a product can require it,
        the classes it narrows, itself first (BottomUpFilling, Filling), and the results it can give."""
        voc = Vocabulary()
        if (LAB[name], RDF.type, OWL.Class) not in voc.graph:
            raise Refused(404, "vocabulary", [f"the vocabulary has no class {name}"])
        return {"name": name, "label": voc.label(name), "process": voc.process(name), "lineage": voc.lineage(name),
                "results": voc.results(name)}

    def process(self, shell: str, request: dict) -> dict:
        """The process AAS of a product on its line (``modreg.process``), from the bindings the planner
        saved in the product's recipe, written to the AAS server; its Validation is the plan check's.
        The line is the one that holds every module the recipe is bound to, or ``request["line"]``."""
        if self.server is None:
            raise Refused(400, "process", ["the service has no AAS server (--basyx) to read the product from"])
        try:
            envs = environments(self.server.url)
        except (OSError, ValueError) as e:
            raise Refused(502, "process", [f"the AAS server was not read: {e}"]) from e
        named = lambda env, name: name in (env["assetAdministrationShells"][0]["id"], env["assetAdministrationShells"][0]["idShort"])  # noqa: E731
        product = next((env for env in envs if named(env, shell)), None)
        if product is None:
            raise Refused(404, "process", [f"the AAS server holds no {shell}"])
        resources = {env["assetAdministrationShells"][0]["idShort"]: env for env in envs if env is not product}
        lines = [env for env in envs if env["assetAdministrationShells"][0]["assetInformation"].get("assetType") == SYSTEM]
        if request.get("line"):
            lines = [env for env in lines if named(env, request["line"])]
        try:
            env = process_of(product, line_for(product, lines, resources), resources, request.get("status") or "Draft")
        except NotBound as e:
            raise Refused(422, "process", [str(e)]) from e
        try:
            published = self.server.publish(env)
        except RuntimeError as e:
            raise Refused(502, "publish", [str(e)]) from e
        held = env["assetAdministrationShells"][0]
        validation = next(sm for sm in env["submodels"] if sm["idShort"] == "Validation")
        result = next(e["value"] for e in validation["submodelElements"] if e["idShort"] == "Result")
        findings = [f["value"] for e in validation["submodelElements"] if e["idShort"] == "Findings" for f in e.get("value") or []]
        return {"product": shell, "process": held["id"], "idShort": held["idShort"], "result": result, "findings": findings,
                "published": published}


class Handler(BaseHTTPRequestHandler):
    service: SkillService
    server_version = "modreg"

    def answer(self, status: int, body):
        data = json.dumps(body, indent=1).encode()
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(data)))
        # The web UI (another origin) calls it from the browser, without credentials.
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(data)

    def body(self):
        length = int(self.headers.get("Content-Length") or 0)
        try:
            return json.loads(self.rfile.read(length))
        except ValueError as e:
            raise Refused(400, "read", [f"not JSON: {e}"]) from e

    def route(self, method: str):
        url = urllib.parse.urlsplit(self.path)
        parts = [p for p in url.path.split("/") if p]
        service = self.service
        try:
            if method == "GET" and parts == ["health"]:
                return self.answer(200, {"status": "ok", "aas_server": service.server.url if service.server else None})
            if method == "POST" and parts[:1] == ["capabilities"] and len(parts) == 2:
                return self.answer(200, service.derive(urllib.parse.unquote(parts[1])))
            if method == "POST" and parts[:1] == ["check"] and len(parts) == 2:
                given = self.body() if int(self.headers.get("Content-Length") or 0) else {}
                requirement = {k: given[k] for k in ("capability", "values") if k in given} or None
                checked = service.check_skills(urllib.parse.unquote(parts[1]), given.get("skill"), requirement)
                return self.answer(200, checked)
            if method == "GET" and parts[:1] == ["vocabulary"] and len(parts) == 2:
                return self.answer(200, service.vocabulary(urllib.parse.unquote(parts[1])))
            if method == "POST" and parts == ["match"]:
                return self.answer(200, service.match(self.body()))
            if method == "POST" and parts[:1] == ["plan"] and len(parts) == 2:
                return self.answer(200, service.plan(urllib.parse.unquote(parts[1]), self.body()))
            if method == "POST" and parts[:1] == ["process"] and len(parts) == 2:
                given = self.body() if int(self.headers.get("Content-Length") or 0) else {}
                return self.answer(200, service.process(urllib.parse.unquote(parts[1]), given))
            return self.answer(404, {"error": f"no {url.path}"})
        except Refused as e:
            self.answer(e.status, {"error": str(e), "step": e.step, "reasons": e.reasons})

    def do_GET(self):          # noqa: N802 (http.server's naming)
        self.route("GET")

    def do_POST(self):         # noqa: N802
        self.route("POST")

    def do_OPTIONS(self):      # noqa: N802 (a browser asks before it posts JSON to another origin)
        self.send_response(204)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    def log_message(self, format, *args):       # noqa: A002
        print(f"{self.address_string()} {format % args}", flush=True)


def serve(service: SkillService, host: str = "0.0.0.0", port: int = 8090) -> ThreadingHTTPServer:
    """The HTTP server of the skill service; ``serve_forever`` runs it."""
    handler = type("SkillHandler", (Handler,), {"service": service})
    return ThreadingHTTPServer((host, port), handler)
