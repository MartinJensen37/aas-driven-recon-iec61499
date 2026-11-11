"""A module's specification and the IEC 61499 application generated from it.

``spec`` reads and validates a module specification (``module/filling.yaml``): equipment, primitive
skills, composite skills, procedures and capabilities. ``module`` generates the module's application
from it, which the synchroniser compares with the running program and makes the boot file from. The
block types the application uses are those of the 4diac projects in ``module/4diac``.
"""
from __future__ import annotations

from pathlib import Path

from .spec import ModuleSpec, load

SPECS = Path(__file__).resolve().parents[2] / "module"     # the module specifications

__all__ = ["ModuleSpec", "load", "SPECS"]
