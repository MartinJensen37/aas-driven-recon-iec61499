"""The AASs of the use case: the filling module and its components, described from the module's
specification (module/filling.yaml), the line that holds the module, and two products, a 2 mL vial and
a 1 mL prefilled syringe.

    python aas/build.py                                   # writes aas/json/<idShort>.json
    python aas/build.py --publish http://localhost:8081   # and sends them to an AAS server

The process AAS of a product (its recipe bound to the module's skills) is made in the web UI's Process
Sequence module by Match and plan, which the skill service answers.
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

from aas_model.constants import BASE_URL
from aas_model.id_injector import inject_ids
from aas_model.resource_template.modules import (
    RESOURCE, LocatedEntryNode, LocatedNode, LocatedStructures, ProductionSystem,
)
from aas_pydantic.submodel_templates.hierarchical_structures import ArcheType
from modgen import SPECS, load
from modreg import model, profile
from modreg.service import AasServer, mapped_last

sys.path.insert(0, str(Path(__file__).resolve().parent))
from products.prefilled_syringe_1ml import prefilled_syringe_1ml  # noqa: E402
from products.vial_2ml import vial_2ml                              # noqa: E402

OUT = Path(__file__).resolve().parent / "json"


def module() -> list[dict]:
    """The AASs of the filling module (the first) and of its components."""
    spec = load(SPECS / "filling.yaml")
    return [model.build(found) for found in profile.describe_all(spec, next(iter(spec.targets)))]


def line(module_env: dict) -> dict:
    """The line the products are made on: a production system whose Hierarchical Structures name the
    filling module's asset, so a process AAS can bind a recipe to it."""
    shell = module_env["assetAdministrationShells"][0]
    asset = f"{BASE_URL}/assets/FillingLine"
    system = ProductionSystem(id_short="FillingLineAAS", id=f"{BASE_URL}/aas/FillingLineAAS", asset_type=f"{RESOURCE}/System",
                              description="The line of the use case: the filling module")
    system.hierarchical_structures = LocatedStructures(
        id_short="HierarchicalStructures", ArcheType=ArcheType(value="OneDown"),
        EntryNode=LocatedEntryNode(global_asset_id=asset, description="The line", Node={
            "FillingModule": LocatedNode(entity_type="SelfManagedEntity", description=shell["idShort"],
                                         global_asset_id=shell["assetInformation"]["globalAssetId"])}))
    return model.build(model.profile(ProductionSystem.model_validate(system.model_dump()), global_asset_id=asset))


def products() -> list[dict]:
    """The AASs of the products; each asset is ``<base>/assets/<idShort without AAS>``."""
    found = []
    for make in (vial_2ml, prefilled_syringe_1ml):
        asset = make()
        inject_ids(asset)
        found.append(model.environment(asset, f"{BASE_URL}/assets/{asset.id_short.removesuffix('AAS')}"))
    return found


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--out", type=Path, default=OUT, help="folder the AASs are written to")
    parser.add_argument("--publish", metavar="URL", help="AAS server to send them to, e.g. http://localhost:8081")
    args = parser.parse_args(argv)
    resources = module()
    envs = resources + [line(resources[0])] + products()
    args.out.mkdir(parents=True, exist_ok=True)
    for env in envs:
        name = env["assetAdministrationShells"][0]["idShort"]
        (args.out / f"{name}.json").write_text(json.dumps(env, indent=1), encoding="utf-8")
        print(f"{name}: {len(env['submodels'])} submodels")
    if args.publish:
        server = AasServer(args.publish)
        for env in mapped_last(envs):
            done = server.publish(env)
            print(f"{env['assetAdministrationShells'][0]['idShort']}: published ({len(done)} requests)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
