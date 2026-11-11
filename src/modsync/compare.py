"""What runs on a module against the application its module spec generates for a target: the
application expected (``expected``, ``expected_values``) and the differences found (``Drift``), which
the synchroniser also uses to describe an online change."""
from __future__ import annotations

from dataclasses import dataclass, field
from functools import cached_property
from pathlib import Path
import xml.etree.ElementTree as ET

from iec61499_mgmt.sysfile import FlatApplication, flatten
from modgen.module import app_name, application, parameter_port, start_links
from modgen.spec import ModuleSpec, Parameter



def owner(port: str) -> str:
    """The instance of ``<instance>.<port>``."""
    return port.rpartition(".")[0]


def init_link(connection: tuple[str, str]) -> bool:
    """A link of the INIT chain: it only orders the initialisation."""
    return connection[0].endswith(".INITO") and connection[1].endswith(".INIT")


def expected(spec: ModuleSpec, target: str) -> FlatApplication:
    """The application modgen generates for ``target``, flattened as FORTE names its instances, with
    the links from the resource's START that start it."""
    app = application(ET.Element("System"), spec, target)
    return flatten(app.find("SubAppNetwork"), start_links(app))


def parameters(spec: ModuleSpec, fbs: dict[str, str]) -> dict[str, Parameter]:
    """Every skill parameter input of the program with its declaration: the values that may be
    changed online (a skill takes them over at its next start). These are the defaults of primitive
    skill instances (``<instance>.<parameter>``), the constants flows bind for their steps, and the
    defaults of composite skills (``<skill>.<parameter>.Default``)."""
    ports = {}
    for name, typ in fbs.items():
        package, _, t = typ.rpartition("::")
        if package == spec.package and t.startswith("SK_") and t[3:] in spec.skills:
            ports.update({f"{name}.{p}": pr for p, pr in spec.skills[t[3:]].parameters.items()})
    for skill, comp in spec.composites.items():
        ports.update({parameter_port(spec, skill, p): pr for p, pr in comp.parameters.items() if f"{skill}.{p}" in fbs})
    return ports


def expected_values(spec: ModuleSpec, app: FlatApplication) -> dict[str, str]:
    """Input values of the generated program: what the deployment writes, plus the parameter
    defaults it leaves to the type. An input a data connection drives (a parameter a flow binds to
    its composite skill's) holds whatever was passed last, so it has no expected value."""
    values = dict(app.parameters)
    driven = {d for _, d in app.data_connections}
    for port, pr in parameters(spec, app.fbs).items():
        if port not in driven:
            values.setdefault(port, pr.literal())
    return values


@dataclass
class Drift:
    """Differences of the running program from the generated one; empty means in sync."""
    missing: list[str] = field(default_factory=list)                    # instances
    unexpected: list[str] = field(default_factory=list)
    retyped: list[tuple[str, str, str]] = field(default_factory=list)   # instance, expected, running
    missing_connections: list[tuple[str, str]] = field(default_factory=list)
    unexpected_connections: list[tuple[str, str]] = field(default_factory=list)
    values: dict[str, tuple[str, str | None]] = field(default_factory=dict)   # port -> (expected, running)

    @property
    def structural(self) -> bool:
        """Instances, types or connections differ."""
        return bool(self.missing or self.unexpected or self.retyped or self.missing_connections
                    or self.unexpected_connections)

    @property
    def empty(self) -> bool:
        return not (self.structural or self.values)

    def size(self) -> int:
        return (len(self.missing) + len(self.unexpected) + len(self.retyped) + len(self.missing_connections)
                + len(self.unexpected_connections) + len(self.values))

    def lines(self) -> list[str]:
        """One line per difference, for reports and the AAS."""
        out = [f"missing instance {n}" for n in self.missing]
        out += [f"unexpected instance {n}" for n in self.unexpected]
        out += [f"{n} is {r}, expected {e}" for n, e, r in self.retyped]
        out += [f"missing connection {s} -> {d}" for s, d in self.missing_connections]
        out += [f"unexpected connection {s} -> {d}" for s, d in self.unexpected_connections]
        out += [f"{p} = {r}, spec {e}" for p, (e, r) in self.values.items()]
        return out


@dataclass
class Candidate:
    """A module spec and one of its targets: a program the module may be running."""
    path: Path | None
    spec: ModuleSpec
    target: str

    @cached_property
    def app(self) -> FlatApplication:
        return expected(self.spec, self.target)

    @property
    def container(self) -> str:
        """The application the program is deployed in, as the 4diac IDE deploys it."""
        return app_name(self.spec, self.target)
