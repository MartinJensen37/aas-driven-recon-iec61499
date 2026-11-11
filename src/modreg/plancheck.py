"""The plan check: whether a product's recipe fits the resources its process AAS binds it to. Every
link is followed from the product's AAS and its process AAS into the resources' AASs, the way an
executor would.

    step -> process -> required capability -> offered capability -> skill -> bound parameter

A parameter of a skill is an input variable of the Operation of its Start command. The required
capability is compared with what the resource offers by the matcher (``modreg.match``). Works on AAS
environments (the JSON an AAS server holds), whoever built them.
"""
from __future__ import annotations

from .match import evaluate, number, offered, read, unit_of


# What an AAS environment holds ------------------------------------------------------------------

def children(element: dict | None) -> list[dict]:
    """The elements an element holds (of an Operation: its variables); none for an element that is
    not there."""
    element = element or {}
    if element.get("modelType") == "Operation":
        return [v["value"] for kind in ("inputVariables", "inoutputVariables", "outputVariables")
                for v in element.get(kind) or []]
    held = element.get("submodelElements") or element.get("statements") or element.get("value")
    return [c for c in held if isinstance(c, dict) and "modelType" in c] if isinstance(held, list) else []


def at(element: dict | None, *path: str) -> dict | None:
    for step in path:
        element = next((c for c in children(element) if c.get("idShort") == step), None)
    return element


def resolve(envs: list[dict], ref: dict | None) -> dict | None:
    """The submodel element a model reference names, in any of the environments."""
    keys = (ref or {}).get("keys") or []
    if not keys or keys[0]["type"] != "Submodel":
        return None
    node = next((s for env in envs for s in env["submodels"] if s["id"] == keys[0]["value"]), None)
    for key in keys[1:]:
        node = at(node, key["value"]) if node else None
    return node


def shell_of(env: dict) -> dict:
    return env["assetAdministrationShells"][0]


# Checking ---------------------------------------------------------------------------------------

def step_fits(name: str, envs: list[dict], process: dict | None, resource: dict | None, skill: dict | None,
              bindings: list[dict]) -> list[str]:
    """What does not hold of one step bound to ``resource`` and its ``skill``, ``bindings`` handing
    each input (by ``Name``) a value: a ``SourceElement`` of the product, or a constant ``Value``."""
    if process is None or resource is None or skill is None:
        missing = [what for what, it in (("process", process), ("resource", resource), ("skill", skill)) if it is None]
        return [f"{name}: no such {' or '.join(missing)}"]
    found = []

    # The capability the process requires is one the resource offers (modreg.match), realized by this
    # skill: of several of its meaning, the one this skill realizes.
    reference = at(process, "RequiredCapability")["value"]
    needs = resolve(envs, {**reference, "keys": reference["keys"][:-1]})
    requirement = read(needs) if needs is not None else None
    offers = evaluate(requirement, offered(resource)) if requirement is not None and requirement.meanings else []
    if not offers:
        return [f"{name}: {shell_of(resource)['idShort']} offers no capability with the meaning the process requires"]

    def realizes(candidate) -> bool:
        return skill in [resolve(envs, r) for r in candidate.capability.realized_by]
    candidate = next((c for c in offers if realizes(c)), offers[0])
    offer = candidate.capability.container
    if not realizes(candidate):
        found.append(f"{name}: the capability {offer['idShort']} is not realized by {skill['idShort']}")
    for asked, check in zip(requirement.properties, candidate.checks):
        given = next((p for p in candidate.capability.properties if p.meaning == asked.meaning), None)
        asked_for = {"range": f"{asked.min} to {asked.max}", "values": ", ".join(asked.values)}.get(asked.kind, asked.value)
        if check.status == "match":
            continue
        if check.why == "undescribed":
            found.append(f"{name}: {offer['idShort']} says nothing about {asked.name}")
        elif check.why == "unit":
            found.append(f"{name}: {asked.name} is asked in {asked.unit or None} and offered in {given.unit or None}")
        elif check.status == "mismatch":
            found.append(f"{name}: {asked.name} = {asked_for} is not covered by {offer['idShort']}")
        else:
            found.append(f"{name}: {asked.name} = {asked_for} cannot be compared with {offer['idShort']}: {check.detail}")

    # What is bound reaches a parameter of the skill, within its limits.
    for binding in bindings:
        parameter = at(skill, "Start", "Start", at(binding, "Name")["value"])
        given = at(binding, "SourceElement")
        # A binding without a source is a constant: its own Value.
        source = resolve(envs, given["value"]) if given else at(binding, "Value")
        label = f"{name}: {skill['idShort']}.{at(binding, 'Name')['value']}"
        if parameter is None:
            found.append(f"{label} is not a parameter of the skill")
        elif source is None:
            found.append(f"{label} is bound to a product parameter that does not exist")
        else:
            limits = {q["type"]: number(q["value"]) for q in parameter.get("qualifiers") or []}
            value, what = number(source.get("value")), source["idShort"] if given else "the constant"
            if given and unit_of(parameter) != unit_of(source):
                found.append(f"{label} is in {unit_of(parameter)}, {source['idShort']} in {unit_of(source)}")
            elif value is None or not (limits.get("Minimum", value) <= value <= limits.get("Maximum", value)):
                found.append(f"{label}: {what} = {source.get('value')} is outside "
                             f"{limits.get('Minimum')} to {limits.get('Maximum')}")
        # A process AAS also names the input itself.
        named = at(binding, "InputReference")
        if named is not None and parameter is not None and resolve(envs, named["value"]) is not parameter:
            found.append(f"{label}: its InputReference is not that input")
    return found


def check_process(product: dict, process: dict, resources: dict[str, dict]) -> list[str]:
    """What does not hold when the process AAS's bindings of the product's recipe are followed into
    the resources: one line each, none if every step can be run as bound. Every step of the recipe
    needs a binding."""
    envs, found = [product, process, *resources.values()], []
    by_id = {shell_of(env)["id"]: env for env in resources.values()}
    recipe = next(s for s in product["submodels"] if s["idShort"] == "ProductionSequence")
    bound = set()
    for binding in children(next(s for s in process["submodels"] if s["idShort"] == "Bindings")):
        step = resolve(envs, at(binding, "Step")["value"])
        if step is None:
            found.append(f"{binding['idShort']}: its step is not in the recipe")
            continue
        bound.add(step["idShort"])
        resource = by_id.get(at(binding, "Resource")["value"]["keys"][0]["value"]) if at(binding, "Resource") else None
        skill = resolve(envs, at(binding, "Skill")["value"]) if at(binding, "Skill") else None
        found += step_fits(at(step, "Name")["value"], envs, resolve(envs, at(step, "ProcessReference")["value"]),
                           resource, skill, children(at(binding, "Bindings")))
    found += [f"{at(step, 'Name')['value']}: not bound" for step in children(at(recipe, "Steps"))
              if step["idShort"] not in bound]
    return found
