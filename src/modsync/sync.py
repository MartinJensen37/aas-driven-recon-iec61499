"""The online change of a running module and what guards it, used by the synchroniser (``desired``).

- ``online`` gives the management commands that bring a difference into the running application
  without a restart, ``summary`` says what they do;
- ``guard`` refuses a change (``Refused``) while the module runs or is occupied, and ``lacking``
  finds the block types FORTE does not have;
- ``LocalDeployer`` keeps the module's boot file, to which a verified online change is added.
"""
from __future__ import annotations

from pathlib import Path

from iec61499_mgmt.protocol import Client, Command, ManagementError
from iec61499_mgmt.sysfile import FlatApplication
from modgen.fbxml import GENERIC
from modgen.library import STATES

from .compare import Drift, init_link, owner
from .device import Snapshot

# Library internals read for the guard: the state manager's and the occupation's logic FBs.
MODULE_STATE, OCCUPIED = "Module.Logic.State", "Occupation.Logic.Occupied"
# The module's name as deployed: every generated module has this parameter.
MODULE_NAME = "Occupation.Module"
QUIET = {STATES["Stopped"], STATES["Idle"], STATES["Aborted"]}


# Deployment ------------------------------------------------------------------------------------

class LocalDeployer:
    """The module's boot file on this machine, ``<folder>/boot/forte.fboot``, which FORTE loads when it
    starts."""

    def __init__(self, folder: Path):
        self.folder = Path(folder)

    def load(self) -> str:
        """The boot file FORTE starts with."""
        return (self.folder / "boot" / "forte.fboot").read_text(encoding="utf-8")

    def save(self, boot: str):
        """Replace the boot file; the running application is not touched."""
        (self.folder / "boot").mkdir(parents=True, exist_ok=True)
        (self.folder / "boot" / "forte.fboot").write_text(boot, encoding="utf-8", newline="\n")


class Refused(RuntimeError):
    """The module may not be changed now (running, occupied) or cannot be (types missing in FORTE, a
    difference that needs a restart)."""


def guard(client: Client, snap: Snapshot):
    """Changes only while the module is Stopped, Idle or Aborted and nobody occupies it."""
    def read(port: str) -> str:
        command = snap.at(Command(op="read", resource=snap.resource, source=port))
        return client.execute(command).read_value(command.source)
    try:
        state, occupied = int(read(MODULE_STATE)), read(OCCUPIED) == "TRUE"
    except (ManagementError, ValueError):
        raise Refused("Cannot read the module state and occupation (not a generated module?); force the change "
                      "to skip this check")
    names = {v: k for k, v in STATES.items()}
    if state not in QUIET or occupied:
        raise Refused(f"Module is {names.get(state, state)}{' and occupied' if occupied else ''}; "
                      "stop and release it first, or force the change")


def lacking(client: Client, types, known) -> list[str]:
    """The types FORTE does not have; generic comm FBs are made on demand (GEN_*), so not asked for.
    Asked of the device, which answers also while it has no program (no resource yet)."""
    missing = []
    for typ in sorted(set(types) - set(known)):
        if GENERIC.fullmatch(typ):
            continue
        try:
            if not client.execute(Command(op="query_type", resource="", type=typ)).types:
                missing.append(typ)
        except ManagementError:
            missing.append(typ)
    return missing


def online(app: FlatApplication, drift: Drift, resource: str = "RES", container: str = "") -> list[Command]:
    """The management commands that apply ``drift`` to the running application without a restart
    (``container``: the application's the program lies in, ``Snapshot.container``).

    Changed parameters are written. New instances are created, given their values, wired and
    started; then the INIT event where the INIT chain enters them from the running program is
    fired once (``$e``), which initialises them in order (OPC UA nodes, channels).
    """
    fresh = set(drift.missing)
    new = [n for n in app.fbs if n in fresh]              # in the order of the program
    cmd = lambda op, **kw: Command(op=op, resource=resource, **kw).inside(container)  # noqa: E731
    return [*[cmd("write", destination=p, value=e) for p, (e, _) in drift.values.items()],
            *[cmd("create_fb", name=n, type=app.fbs[n]) for n in new],
            *[cmd("write", destination=p, value=v) for p, v in app.parameters.items() if owner(p) in fresh],
            *[cmd("disconnect", source=s, destination=d) for s, d in drift.unexpected_connections],
            *[cmd("connect", source=s, destination=d) for s, d in drift.missing_connections],
            *[cmd("start", name=n) for n in new],
            *[cmd("write", destination=d, value="$e") for s, d in drift.missing_connections
              if init_link((s, d)) and owner(s) not in fresh and owner(d) in fresh]]


def summary(drift: Drift, commands: list[Command]) -> list[str]:
    """What the online change does: the values written, the instances created (by their top-level
    name), where they are initialised from, and the number of management commands."""
    lines = [f"write {p} := {e} (was {r})" for p, (e, r) in drift.values.items()]
    if created := list(dict.fromkeys(n.split(".")[0] for n in drift.missing)):
        count = lambda op: sum(c.op == op for c in commands)  # noqa: E731
        lines.append(f"create {', '.join(created)}: {count('create_fb')} instances, {count('connect')} connections"
                     + (f", {count('disconnect')} INIT links moved" if count("disconnect") else ""))
        lines += [f"initialise from {c.destination}" for c in commands if c.value == "$e"]
    return lines + [f"{len(commands)} management commands"]
