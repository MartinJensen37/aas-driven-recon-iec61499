"""Reading an AAS as plain JSON, as an AAS server gives it: the elements an element holds, one by its
path of idShorts, a submodel by its idShort, the meanings of an element, the skills of a Skills
submodel. Shared by the synchroniser, the planner and the registration service."""
from __future__ import annotations

BASE = "https://smartproductionlab.aau.dk"
SKILL = f"{BASE}/skill"
# The variables every command has; a command's other variables are its parameters and results.
OWN = ("Session", "Accepted", "ErrorID")


def children(element: dict | None) -> list[dict]:
    if not element:
        return []
    kids = element.get("submodelElements") or element.get("statements") or element.get("value") or []
    return [k for k in kids if isinstance(k, dict)] if isinstance(kids, list) else []


def at(element: dict | None, *path: str) -> dict | None:
    for step in path:
        element = next((c for c in children(element) if c.get("idShort") == step), None)
    return element


def submodel(env: dict, id_short: str) -> dict | None:
    return next((s for s in env.get("submodels", []) if s.get("idShort") == id_short), None)


def meaning(element: dict) -> str:
    keys = (element.get("semanticId") or {}).get("keys") or []
    return keys[0]["value"] if keys else ""


def also(element: dict) -> list[str]:
    """The supplemental semanticIds of an element: the kind of a skill, what a step is called."""
    return [k["value"] for ref in element.get("supplementalSemanticIds") or [] for k in ref.get("keys", [])[:1]]


def parts(structure: dict | None) -> list[dict]:
    """The Nodes of a Hierarchical Structures submodel's EntryNode that are parts, not points of
    interest (a point is a CoManagedEntity with a meaning, such as where a shuttle stands)."""
    return [n for n in children(at(structure, "EntryNode"))
            if not (n.get("entityType") == "CoManagedEntity" and also(n))]


def skills_in(held: dict | None) -> list[dict]:
    """The skills of a Skills submodel: its elements with the meaning of a skill."""
    return [s for s in children(held) if meaning(s) == SKILL]


def target(reference: dict | None) -> list[str]:
    """The key values of a ReferenceElement's reference."""
    return [k["value"] for k in ((reference or {}).get("value") or {}).get("keys", [])]


def variables(operation: dict | None, kind: str) -> list[dict]:
    return [v["value"] for v in (operation or {}).get(kind) or [] if v["value"]["idShort"] not in OWN]


def qualifier(element: dict, name: str) -> str | None:
    return next((q.get("value") for q in element.get("qualifiers") or [] if q.get("type") == name), None)
