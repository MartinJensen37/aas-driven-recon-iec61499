"""Modbus TCP simulator of a module's equipment, driven by the ``sim`` sections of its spec.

Every IO point with a Modbus address is a register: coils (c) and holding registers (h) are
written by FORTE, discrete inputs (d) and input registers (i) are computed here. What an equipment
item's ``sim`` section (in module/filling.yaml) can hold:

``stepper`` a position in the item's own unit, moved at ``speed`` units per second while the
            ``step`` output (an LREAL: the pulses) is on and, if named, ``enable``; with the
            ``direction`` output on it increases, else it decreases; it stays within 0..``travel``;
            ``switches`` are inputs that are TRUE at their position (an end of the travel).
``values``  constant values of inputs.

The tests run it with ``separate``, in a process of its own.
"""
from __future__ import annotations

from contextlib import contextmanager
import multiprocessing
from pathlib import Path
import socket
import socketserver
import struct
import threading
import time

from modgen.spec import ModuleSpec, load


class Stepper:
    """One simulated stepper axis, its position in the item's unit."""
    def __init__(self, cfg):
        self.step, self.direction, self.enable = cfg["step"], cfg["direction"], cfg.get("enable")
        self.speed, self.travel = float(cfg["speed"]), float(cfg["travel"])
        self.position = float(cfg.get("start", 0.0))
        self.switches = {name: float(at) for name, at in cfg.get("switches", {}).items()}


class ModuleSim:
    """Register image and kinematics of one module."""
    def __init__(self, spec: ModuleSpec):
        self.spec = spec
        self.lock = threading.Lock()
        self.bits = {}        # ("c"|"d", address) -> bool
        self.regs = {}        # ("h"|"i", address) -> int
        self.points = {}      # "<Equipment>.<Point>" -> (table, address)
        self.axes: dict[str, Stepper] = {}
        self.values: dict[str, float] = {}
        for eq_name, eq in spec.equipment.items():
            for name, io in [*eq.inputs.items(), *eq.outputs.items()]:
                if io.modbus:
                    table, address = io.modbus[0], int(io.modbus[1:])
                    self.points[f"{eq_name}.{name}"] = (table, address)
                    (self.bits if table in "cd" else self.regs)[(table, address)] = 0 if table in "hi" else False
            sim = eq.sim or {}
            if "stepper" in sim:
                self.axes[eq_name] = Stepper(sim["stepper"])
            for name, value in sim.get("values", {}).items():
                self.values[f"{eq_name}.{name}"] = value
        self.step(0.0)

    # --- values in engineering units -------------------------------------------------------
    def output(self, eq: str, name: str):
        """Current value of an output: bool, or the LREAL value (None when off, i.e. raw 0)."""
        table, address = self.points[f"{eq}.{name}"]
        if table == "c":
            return self.bits[(table, address)]
        raw = self.regs[(table, address)]
        out = self.spec.equipment[eq].outputs[name]
        return None if raw == 0 else (raw - out.bias) / out.gain

    def set_input(self, eq: str, name: str, value):
        """Set an input in engineering units."""
        key = f"{eq}.{name}"
        if key not in self.points:
            return
        table, address = self.points[key]
        if table == "d":
            self.bits[(table, address)] = bool(value)
        else:
            scale = self.spec.equipment[eq].inputs[name].scale
            self.regs[(table, address)] = max(0, min(65535, int(round(float(value) / scale))))

    # --- Modbus access ----------------------------------------------------------------------
    def read_bits(self, table, start, count):
        with self.lock:
            return [self.bits.get((table, a), False) for a in range(start, start + count)]

    def read_regs(self, table, start, count):
        with self.lock:
            return [self.regs.get((table, a), 0) for a in range(start, start + count)]

    def write_bit(self, address, value):
        with self.lock:
            self.bits[("c", address)] = value

    def write_reg(self, address, value):
        with self.lock:
            self.regs[("h", address)] = value

    # --- kinematics -------------------------------------------------------------------------
    def step(self, dt):
        """Advance the kinematics by ``dt`` seconds."""
        with self.lock:
            for eq, axis in self.axes.items():
                stepping = self.output(eq, axis.step) and (axis.enable is None or self.output(eq, axis.enable))
                if stepping:
                    way = 1 if self.output(eq, axis.direction) else -1
                    axis.position = min(axis.travel, max(0.0, axis.position + way * axis.speed * dt))
                for name, at in axis.switches.items():
                    near = axis.position >= at - 1e-6 if at > axis.travel / 2 else axis.position <= at + 1e-6
                    if near:
                        axis.position = at                  # a switch is at an end: the axis is there
                    self.set_input(eq, name, near)
            for key, value in self.values.items():
                self.set_input(*key.split("."), value)


def _pack_bits(bits):
    data = bytearray((len(bits) + 7) // 8)
    for i, b in enumerate(bits):
        if b:
            data[i // 8] |= 1 << (i % 8)
    return bytes([len(data)]) + bytes(data)


class _Handler(socketserver.BaseRequestHandler):
    """Modbus TCP handler for one client connection (function codes 1-6, 15, 16)."""
    def handle(self):
        sim: ModuleSim = self.server.sim
        try:
            while True:
                header = self._recv(7)
                if not header:
                    return
                tid, pid, length, unit = struct.unpack(">HHHB", header)
                pdu = self._recv(length - 1)
                if pdu is None:
                    return
                reply = self._dispatch(sim, pdu)
                self.request.sendall(struct.pack(">HHHB", tid, pid, len(reply) + 1, unit) + reply)
        except (ConnectionResetError, ConnectionAbortedError):
            pass

    def _recv(self, n):
        data = b""
        while len(data) < n:
            chunk = self.request.recv(n - len(data))
            if not chunk:
                return None
            data += chunk
        return data

    @staticmethod
    def _dispatch(sim, pdu):
        fc = pdu[0]
        try:
            if fc in (1, 2):
                start, count = struct.unpack(">HH", pdu[1:5])
                return bytes([fc]) + _pack_bits(sim.read_bits("c" if fc == 1 else "d", start, count))
            if fc in (3, 4):
                start, count = struct.unpack(">HH", pdu[1:5])
                regs = sim.read_regs("h" if fc == 3 else "i", start, count)
                return bytes([fc, 2 * count]) + b"".join(struct.pack(">H", r) for r in regs)
            if fc == 5:
                address, value = struct.unpack(">HH", pdu[1:5])
                sim.write_bit(address, value == 0xFF00)
                return pdu[:5]
            if fc == 6:
                address, value = struct.unpack(">HH", pdu[1:5])
                sim.write_reg(address, value)
                return pdu[:5]
            if fc == 15:
                start, count, _ = struct.unpack(">HHB", pdu[1:6])
                for i in range(count):
                    sim.write_bit(start + i, bool(pdu[6 + i // 8] >> (i % 8) & 1))
                return pdu[:5]
            if fc == 16:
                start, count, _ = struct.unpack(">HHB", pdu[1:6])
                for i in range(count):
                    sim.write_reg(start + i, struct.unpack(">H", pdu[6 + 2 * i:8 + 2 * i])[0])
                return pdu[:5]
        except (IndexError, struct.error):
            return bytes([fc | 0x80, 3])
        return bytes([fc | 0x80, 1])


class SimServer(socketserver.ThreadingTCPServer):
    """Threaded Modbus TCP server with a kinematics loop; use as a context manager."""
    daemon_threads = True
    allow_reuse_address = True

    def __init__(self, sim: ModuleSim, host="127.0.0.1", port=1502, period=0.01):
        super().__init__((host, port), _Handler)
        self.sim = sim
        self._halt = threading.Event()
        self._workers = [threading.Thread(target=self.serve_forever, daemon=True),
                         threading.Thread(target=self._loop, args=(period,), daemon=True)]

    def _loop(self, period):
        last = time.monotonic()
        while not self._halt.wait(period):
            now = time.monotonic()
            self.sim.step(now - last)
            last = now

    def __enter__(self):
        for t in self._workers:
            t.start()
        return self

    def __exit__(self, *args):
        self._halt.set()
        self.shutdown()
        self.server_close()


def _serve(spec_path: str, host: str, port: int) -> None:
    with SimServer(ModuleSim(load(Path(spec_path))), host=host, port=port):
        threading.Event().wait()


@contextmanager
def separate(spec_path: Path | str, host="127.0.0.1", port=1502, timeout=15.0):
    """The simulator of a module in a process of its own, so that what the process using it does
    (a test that builds an AAS for seconds) cannot hold up the equipment it simulates."""
    process = multiprocessing.get_context("spawn").Process(target=_serve, args=(str(spec_path), host, port), daemon=True)
    process.start()
    try:
        deadline = time.monotonic() + timeout
        while True:
            try:
                socket.create_connection(("127.0.0.1" if host == "0.0.0.0" else host, port), timeout=1).close()
                break
            except OSError:
                if not process.is_alive() or time.monotonic() > deadline:
                    raise RuntimeError(f"the simulator of {spec_path} did not start on port {port}") from None
                time.sleep(0.1)
        yield process
    finally:
        process.terminate()
        process.join(5)
