"""4diac XML of an application's network: FB instances, untyped subapplications and connections.

The module's application is built as the XML a 4diac system file holds and flattened from it into
management commands (``iec61499_mgmt.sysfile``).
"""
from __future__ import annotations

import re
import xml.etree.ElementTree as ET

NET = "iec61499::net"
# The generic communication blocks, which FORTE makes in any size at runtime (from GEN_SERVER,
# GEN_PUBLISH, GEN_SUBSCRIBE): a running FORTE has them without their types being compiled in.
GENERIC = re.compile(rf"{NET}::(SERVER|PUBLISH|SUBSCRIBE)_(\d+)(?:_(\d+))?")


def server(sds: int, rds: int) -> str:
    """SERVER_sds_rds: an OPC UA method with rds arguments in and sds results out."""
    return f"{NET}::SERVER_{sds}_{rds}"


def publish(n: int) -> str:
    """PUBLISH_n: publishes n values (over OPC UA or on a device-local channel)."""
    return f"{NET}::PUBLISH_{n}"


def elem(parent, tag, **attrs):
    """Append an XML child with stringified attributes."""
    return ET.SubElement(parent, tag, {k: str(v) for k, v in attrs.items()})


def wstr(text):
    """Quote text as a WSTRING literal."""
    return '"' + text + '"'


def interface(root, inputs, outputs, iv=None, ov=None):
    """Add an untyped subapplication's interface, as the 4diac IDE writes it (``SubAppInterfaceList``).

    ``inputs``/``outputs``: {event: [vars]} or {event: ([vars], "EInit")}; ``iv``/``ov``: {name: type}.
    Like the IDE, it writes no With on a subapplication's events and no empty variable lists.
    """
    iface = elem(root, "SubAppInterfaceList")
    for tag, events in [("SubAppEventInputs", inputs), ("SubAppEventOutputs", outputs)]:
        group = elem(iface, tag)
        for name, variables in events.items():
            elem(group, "SubAppEvent", Name=name, Type=variables[1] if isinstance(variables, tuple) else "Event")
    for tag, variables in [("InputVars", iv or {}), ("OutputVars", ov or {})]:
        if variables:
            group = elem(iface, tag)
            for name, typ in variables.items():
                elem(group, "VarDeclaration", Name=name, Type=typ)
    return iface


def connections(net, events, data):
    """Add event and data connection lists to a network."""
    for tag, pairs in [("EventConnections", events), ("DataConnections", data)]:
        if pairs:                                         # as the IDE saves it: no empty lists
            group = elem(net, tag)
            for s, d in pairs:
                elem(group, "Connection", Source=s, Destination=d)


def fb(net, name, typ, x, y, **params):
    """Add an FB instance with parameters to a network."""
    f = elem(net, "FB", Name=name, Type=typ, x=x, y=y)
    for p, v in params.items():
        elem(f, "Parameter", Name=p, Value=v)
    return f


def subapp(net, name, x, y, comment, ei, eo, iv=None, ov=None):
    """Add an untyped subapplication; return it and its inner network."""
    sa = elem(net, "SubApp", Name=name, x=x, y=y, Comment=comment)
    interface(sa, ei, eo, iv, ov)
    return sa, elem(sa, "SubAppNetwork")


class SubNet:
    """FB instances and connections collected for a subapplication's network; ``write`` adds them to it."""

    def __init__(self, net):
        self.net = net
        self.fbs, self.events, self.data = [], [], []

    def fb(self, name, typ, **params):
        """Add an FB instance with parameter values."""
        self.fbs.append((name, typ, params))
        return name

    def ev(self, source, *destinations):
        """Add event connections from ``source`` to each destination."""
        self.events += [(source, d) for d in destinations]

    def da(self, source, *destinations):
        """Add data connections from ``source`` to each destination."""
        self.data += [(source, d) for d in destinations]

    def chain(self, event, names, last):
        """Chain INIT through ``names`` (INITO -> INIT), starting at ``event`` and ending at ``last``."""
        self.ev(event, names[0] + ".INIT")
        for a, z in zip(names, names[1:]):
            self.ev(a + ".INITO", z + ".INIT")
        self.ev(names[-1] + ".INITO", last)

    def write(self):
        """Write the instances in one row and the connections; FBs go ahead of the subapplications
        already in the network, as the IDE orders them."""
        for i, (name, typ, params) in enumerate(self.fbs):
            fb(self.net, name, typ, 1000 + i * 4000, 1000, **params)
        connections(self.net, self.events, self.data)
        order = {"FB": 0, "SubApp": 1}
        self.net[:] = sorted(self.net, key=lambda e: order.get(e.tag, 2))
