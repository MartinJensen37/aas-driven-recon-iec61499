"""Values read back from a running FORTE, made comparable: an IEC TIME literal in milliseconds."""
from __future__ import annotations

import re


def time_ms(text: str) -> float | None:
    """Milliseconds of an IEC TIME literal such as T#1s500ms, or None if unparsable."""
    match = re.fullmatch(r"(?:T|TIME)#(-)?((?:\d+(?:\.\d+)?(?:d|h|ms|m|s|us|ns)_?)+)", text.strip(), re.IGNORECASE)
    if not match:
        return None
    factors = {"d": 86400000, "h": 3600000, "m": 60000, "s": 1000, "ms": 1, "us": 1e-3, "ns": 1e-6}
    total = sum(float(v) * factors[u.lower()]
                for v, u in re.findall(r"(\d+(?:\.\d+)?)(ms|us|ns|d|h|m|s)", match[2], re.I))
    return -total if match[1] else total
