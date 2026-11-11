"""The filling module on a PC: FORTE started from a boot file, the module's IO simulated over Modbus,
and the module driven over OPC UA. Shared by the deployment (deployment.py) and drift (drift.py) tests; the
module's AAS and the skills the tests add are here too (also used by match_plan_check.py)."""
from __future__ import annotations

from contextlib import ExitStack, contextmanager
import copy
import os
from pathlib import Path
import socket
import subprocess
import time

from iec61499_mgmt.bootfile import boot_file, deployment
from iec61499_mgmt.protocol import Client
from modgen import SPECS, load
from modgen.library import SKILL_STATES, STATES
from modgen.spec import Composite, ModuleSpec
from modreg import model, profile
from modsync.aasjson import at, children, submodel
from modsync.compare import Candidate

from module_sim import separate
from module_ua import ModuleUa

ROOT = Path(__file__).resolve().parents[1]
FILLING = SPECS / "filling.yaml"
RESULTS = ROOT / "eval" / "results"
SESSION = "evaluation"                     # the session id the tests occupy the module with
FORTE = os.environ.get("FORTE")            # the FORTE executable (set in the container)

# A skill written in the AAS for the prefilled syringe: the needle starts deep in the barrel and rises
# while the pump doses (a parallel block of the axis and the pump), then the syringe is weighed.
BOTTOM_UP = Composite(**{
    "description": "Fill from the bottom: the needle starts deep and rises while the pump doses, then weigh",
    "capability": "BottomUpFilling",
    "parameters": {"Volume": {"unit": "mL", "minimum": 0.5, "maximum": 10.0, "default": 1.0,
                              "description": "Fill volume"}},
    "execute": [{"MoveAxis": {"Position": 58.0}, "as": "NeedleDeep"},
                {"parallel": [[{"Dispense": {"Volume": "Volume", "FlowRate": 0.7}}],
                              [{"MoveAxis": {"Position": 40.0}, "as": "NeedleRise"}]], "as": "Rising"},
                "Home", "Weigh"],
    "stop": ["Home"],
    "results": {"Weight": "Weigh.Weight"}})

# A skill with two doses, a needle position and a weighing to change (checking and drift tests).
DOUBLE_DOSE = Composite(**{
    "description": "Needle down, two doses, needle up, weigh",
    "parameters": {"Dose": {"unit": "mL", "minimum": 0.5, "maximum": 10.0, "default": 0.5}},
    "execute": [{"MoveAxis": {"Position": 40.0}, "as": "NeedleDown"}, {"Dispense": {"Volume": "Dose", "FlowRate": 1.0}},
                {"Dispense": {"Volume": "Dose", "FlowRate": 1.0}}, {"MoveAxis": {"Position": 0.0}, "as": "NeedleUp"},
                "Weigh"],
    "stop": ["Home"],
    "results": {"Weight": "Weigh.Weight"}})


def aas(spec: ModuleSpec, target: str = "pc") -> tuple[dict, list[dict]]:
    """The AAS of a module and those of its components, as delivered with the module."""
    module, *components = [model.build(found) for found in profile.describe_all(spec, target)]
    return module, components


def with_value(module: dict, skill: str = "Dispensing", step: str = "Dispense", name: str = "FlowRate",
               value: float = 2.0) -> dict:
    """The AAS with a step's constant changed: by default Dispensing's FlowRate 2.0 instead of 1.0."""
    module = copy.deepcopy(module)
    steps = at(submodel(module, "Skills"), skill, "Start", "Steps")
    found = next(s for s in children(steps) if at(s, "NodeId")["value"] == step)
    binding = next(b for b in children(at(found, "Bindings")) if at(b, "Name")["value"] == name)
    at(binding, "Value")["value"] = str(value)
    return module


def with_bound(composite: Composite, step: str, name: str, value: float) -> Composite:
    """``composite`` with its step ``step`` (by name or primitive) given ``name`` = ``value``."""
    data = composite.model_dump()
    for found in data["execute"]:
        if step in (found.get("name"), found.get("skill")):
            found["bind"][name] = value
    return Composite.model_validate(data)


def commit(root: Path = ROOT) -> str:
    """The repository's commit, with ``+`` if its code differs from it (``?`` outside a git checkout)."""
    found = subprocess.run(["git", "-C", str(root), "rev-parse", "--short=12", "HEAD"], capture_output=True, text=True)
    if found.returncode:
        return "?"
    dirty = subprocess.run(["git", "-C", str(root), "status", "--porcelain", "--untracked-files=no", "src", "eval", "module"],
                           capture_output=True, text=True).stdout.strip()
    return found.stdout.strip() + ("+" if dirty else "")


# FORTE ---------------------------------------------------------------------------------------------

def free_port() -> int:
    """A free TCP port on localhost."""
    with socket.socket() as reservation:
        reservation.bind(("127.0.0.1", 0))
        return reservation.getsockname()[1]


@contextmanager
def launch_forte(executable: Path, folder: Path, args: list[str]):
    """FORTE in ``folder`` (its log there) on a free loopback management port; yields the port and
    always stops FORTE."""
    port = free_port()
    with (folder / "forte.log").open("w+b") as log:
        process = subprocess.Popen([str(executable), "-c", f"127.0.0.1:{port}", *args], cwd=folder,
                                   stdout=log, stderr=subprocess.STDOUT)
        try:
            deadline = time.monotonic() + 15
            while True:
                if process.poll() is not None:
                    raise RuntimeError(f"FORTE exited with code {process.returncode}")
                try:
                    with socket.create_connection(("127.0.0.1", port), timeout=0.3):
                        break
                except (ConnectionRefusedError, TimeoutError):
                    if time.monotonic() >= deadline:
                        raise TimeoutError("FORTE did not start") from None
                    time.sleep(0.1)
            yield port
        finally:
            if process.poll() is None:
                process.terminate()
                try:
                    process.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    process.kill()
                    process.wait(timeout=5)


class Bench:
    """The filling module: its simulated IO, and FORTE started anew from a boot file for every run."""
    host, target, reset_s = "127.0.0.1", "pc", 30.0

    def __init__(self, forte: Path, folder: Path, spec: Path = FILLING):
        self.forte, self.folder, self.spec, self.stack = forte, folder, spec, ExitStack()
        self.cand = Candidate(spec, load(spec), self.target)
        # The simulator on a port of its own: the IO addresses in the boot file point there.
        self.modbus = free_port()
        endpoint = f"{self.cand.spec.modbus.host}:{self.cand.spec.modbus.port}:"
        self.overrides = {k: v.replace(endpoint, f"127.0.0.1:{self.modbus}:") for k, v in self.cand.app.parameters.items()
                          if v.startswith("'modbus[")}
        self.stack.enter_context(separate(spec, host="127.0.0.1", port=self.modbus))
        self.running: ExitStack | None = None
        self.forte_dir: Path | None = None             # the last FORTE's folder, with its forte.log

    def boot(self, spec: ModuleSpec | None = None) -> str:
        """The boot file of the module's program (or of ``spec``'s), its IO pointed at the simulator."""
        cand = self.cand if spec is None else Candidate(self.spec, spec, self.target)
        return boot_file(deployment(cand.app, overrides=self.overrides, container=cand.container))

    def start(self, boot: str) -> None:
        """FORTE started with ``boot``; returns once the module is Stopped (its program loaded)."""
        self.running = ExitStack()
        folder = self.folder / f"forte{time.monotonic_ns()}"
        folder.mkdir(parents=True)
        self.forte_dir = folder
        (folder / "forte.fboot").write_text(boot, encoding="utf-8", newline="\n")
        self.ua_port = free_port()
        self.port = self.running.enter_context(launch_forte(
            self.forte, folder, ["-f", str(folder / "forte.fboot"), "-op", str(self.ua_port)]))
        self.client = self.running.enter_context(Client("127.0.0.1", self.port))
        self.ua = ModuleUa(self.ua_port, self.cand.spec.module)
        self.running.callback(self.ua.close)
        self.ua.expect("Module/State", STATES["Stopped"], timeout=20)

    def stop(self) -> None:
        if self.running is not None:
            self.running.close()
            self.running = None

    @property
    def marker(self) -> Path | None:
        """Which FORTE ran last: its folder."""
        return self.forte_dir

    def log(self, marker: Path | None = None) -> str:
        """The log of the FORTE ``marker`` names (the last one started if None)."""
        path = (marker or self.forte_dir) / "forte.log"
        return path.read_text(encoding="utf-8", errors="replace") if path.exists() else "ERROR: no FORTE log"

    def execute(self) -> None:
        """Occupy, Reset and Start the module: it is in Execute."""
        self.ua.call("Occupation/Occupy", SESSION)
        self.ua.call("Module/Reset", SESSION)
        self.ua.expect("Module/State", STATES["Idle"], timeout=self.reset_s)
        self.ua.call("Module/Start", SESSION)
        self.ua.expect("Module/State", STATES["Execute"], timeout=10)

    def idle(self) -> None:
        """Stop the module and release it, so that a value may be written."""
        self.ua.call("Module/Stop", SESSION)
        self.ua.expect("Module/State", STATES["Stopped"], timeout=30)
        self.ua.call("Occupation/Release", SESSION)

    def run(self, skill: str, *args, timeout: float = 60.0) -> float:
        """Run a skill to Succeeded; its duration in seconds."""
        started = time.perf_counter()
        assert self.ua.call(f"Skills/{skill}/Start", SESSION, *args) == [True, 0], skill
        self.ua.expect(f"Skills/{skill}/State", SKILL_STATES["Succeeded"], timeout=timeout)
        return time.perf_counter() - started

    def close(self) -> None:
        self.stop()
        self.stack.close()
