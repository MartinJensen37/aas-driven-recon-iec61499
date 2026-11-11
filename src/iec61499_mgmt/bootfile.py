"""FORTE boot files: one management request per line, prefixed by its resource (empty: the device)."""
from __future__ import annotations

from .protocol import Command
from .sysfile import FlatApplication


def boot_file(commands: list[Command]) -> str:
    """Render commands as boot-file lines ``<resource>;<Request .../>``."""
    return "".join(f"{c.resource};{c.xml(i)}\n" for i, c in enumerate(commands, 1))


def deployment(app: FlatApplication, resource: str = "RES", resource_type: str = "iec61499::system::EMB_RES",
               overrides: dict[str, str] | None = None, container: str = "") -> list[Command]:
    """Create the resource and the application in it, then start the resource.

    ``overrides``: values written instead of the application's own. ``container``: the application's
    name, to create its instances inside it (``Filling.Home``), as the 4diac IDE does; the IDE can
    then monitor the program."""
    commands = [Command(op="create_fb", resource="", name=resource, type=resource_type)]
    commands += [c.inside(container) for c in app.commands(resource, overrides)]
    commands.append(Command(op="start", resource="", name=resource))
    return commands
