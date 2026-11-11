"""Names and codes of the module library (package ``modlib``): the module-independent block types
every module's application uses (occupation, module state manager, skill state machine, parameter
latches, the blocks of a composite skill's flow, IO points), compiled into FORTE once for all modules.
"""
LIB = "modlib"
# Module PackML states (ISA-TR88 numbering) used by the module state manager.
STATES = {"Clearing": 1, "Stopped": 2, "Starting": 3, "Idle": 4, "Execute": 6, "Stopping": 7, "Aborting": 8,
          "Aborted": 9, "Resetting": 15}
# Skill states (every primitive and composite skill).
SKILL_STATES = {"Idle": 0, "Running": 1, "Stopping": 2, "Succeeded": 3, "Failed": 4, "Aborted": 5}
# Types a skill parameter can have, with the widest range: the Lower and Upper a parameter latch
# (SKILL_Param_<type>) has when the parameter declares no limits.
PARAM_RANGE = {"LREAL": ("-1.0E308", "1.0E308"), "INT": ("-32768", "32767"), "DINT": ("-2147483648", "2147483647"),
               "UINT": ("0", "65535"), "BOOL": None}


def q(name):
    """Qualify a library type name."""
    return f"{LIB}::{name}"
