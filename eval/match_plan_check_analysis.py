"""The analysis of the checking, matching and planning test from the rows of match_plan_check.py.

    python eval/match_plan_check_analysis.py eval/results/match_plan_check-<when>.jsonl

Writes match_plan_check-<when>.md beside the rows: for part a, the method's check and the two baselines against the
oracle on every mutant (precision and recall with 95 % Wilson intervals, per operator, every
disagreement); for part b, the confusion matrix of the method's answer and the truth, the planned skills
and their times; for part t, the plans for filling from the bottom and whether they come out right.
"""
from __future__ import annotations

import argparse
import json
import statistics
from collections import Counter
from pathlib import Path

from drift_analysis import rate

METHODS = {"method": "The method's check", "rules": "Hand-written rules", "structure": "Structure only (4diac)"}
ANSWERS = ("offered", "after", "not")
ANSWER_NAMES = {"offered": "offered", "after": "after a reconfiguration", "not": "not offered"}
RULES = {"O1": "a step cannot be carried out", "O2": "spill", "O3": "crash into the bottom", "O4": "overflow",
         "O5": "foam (tip above the liquid)", "O6": "wrong volume", "O7": "no right weight", "O8": "tip left in the container"}


def confusion(rows, key):
    """``key``'s findings against the oracle: caught, missed, rejected though right, passed right."""
    c = Counter((r["wrong"], bool(r[key])) for r in rows)
    return c[(True, True)], c[(True, False)], c[(False, True)], c[(False, False)]   # TP FN FP TN


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("rows", type=Path)
    a = ap.parse_args()
    rows = [json.loads(line) for line in a.rows.read_text(encoding="utf-8").splitlines() if line.strip()]
    ra = [r for r in rows if r["part"] == "a"]
    rb = [r for r in rows if r["part"] == "b"]
    setups = sorted({r.get("commit") for r in rows}, key=str)
    md = [f"# Checking, matching and planning test results: {a.rows.name}", "", f"Setups (commit): {setups}", ""]

    if ra:
        wrong = sum(r["wrong"] for r in ra)
        md += ["## Part a: the check on mutants", "",
               f"{len(ra)} distinct mutants of {', '.join(sorted({r['skill'] for r in ra}))}; the oracle finds "
               f"{wrong} wrong (the product spoiled or a step that cannot be carried out), {len(ra) - wrong} right.", "",
               "| Method | Caught (TP) | Missed (FN) | Rejected though right (FP) | Passed right (TN) | Recall | Precision |",
               "| --- | --- | --- | --- | --- | --- | --- |"]
        for key, name in METHODS.items():
            tp, fn, fp, tn = confusion(ra, key)
            md.append(f"| {name} | {tp} | {fn} | {fp} | {tn} | {rate(tp, tp + fn)} | {rate(tp, tp + fp)} |")
        md += ["", "Per operator (the method's check): wrong of all, caught, rejected though right.", "",
               "| Operator | Mutants | Wrong | Caught | Rejected though right |", "| --- | --- | --- | --- | --- |"]
        for op in sorted({r["operator"] for r in ra}):
            rs = [r for r in ra if r["operator"] == op]
            tp, fn, fp, tn = confusion(rs, "method")
            md.append(f"| {op} | {len(rs)} | {tp + fn} | {tp} of {tp + fn} | {fp} of {fp + tn} |")
        md += ["", "Per skill (the method's check).", "", "| Skill | Mutants | Wrong | Caught | Rejected though right |",
               "| --- | --- | --- | --- | --- |"]
        for skill in sorted({r["skill"] for r in ra}):
            rs = [r for r in ra if r["skill"] == skill]
            tp, fn, fp, tn = confusion(rs, "method")
            md.append(f"| {skill} | {len(rs)} | {tp + fn} | {tp} of {tp + fn} | {fp} of {fp + tn} |")
        caught = [r for r in ra if r["wrong"] and r["method"] and r["mutated"]]
        md += ["", f"A finding of the check names the mutated step in {sum(r['named'] for r in caught)} of the "
               f"{len(caught)} caught mutants that changed an existing step.",
               f"Time to check a mutant: median {1000 * statistics.median(r['check_s'] for r in ra):.1f} ms, "
               f"at most {1000 * max(r['check_s'] for r in ra):.1f} ms."]
        md += ["", "### Missed by the check (the oracle's rule)", ""]
        missed = Counter()
        for r in ra:
            if r["wrong"] and not r["method"]:
                rule = sorted(r["oracle"])[0]
                missed[rule] += 1
                md.append(f"- {r['skill']}: {r['what']} -> {', '.join(f'{k} {v}' for k, v in sorted(r['oracle'].items()))}")
        md += ["", "By the first rule broken: " + ", ".join(f"{k} {RULES[k]}: {n}" for k, n in sorted(missed.items())), ""]
        md += ["### Rejected by the check though the product is right", ""]
        for r in ra:
            if not r["wrong"] and r["method"]:
                md.append(f"- {r['skill']}: {r['what']} -> {r['method'][0][:160]}")
        md += ["", "### The rules against the check", "",
               f"- Caught by the check, missed by the rules: {sum(r['wrong'] and bool(r['method']) and not r['rules'] for r in ra)}",
               f"- Caught by the rules, missed by the check: {sum(r['wrong'] and bool(r['rules']) and not r['method'] for r in ra)}", ""]
        for r in ra:
            if r["wrong"] and r["method"] and not r["rules"]:
                md.append(f"  - {r['skill']}: {r['what']}")

    if rb:
        md += ["", "## Part b: matching and planning", "",
               f"{len(rb)} cases: {len({(r['container'], r['volume'], r['weight']) for r in rb})} products on "
               f"{len({r['variant'] for r in rb})} module variants.", "",
               "| Answer \\ truth | " + " | ".join(ANSWER_NAMES[t] for t in ANSWERS) + " |", "| --- | --- | --- | --- |"]
        c = Counter((r["answer"], r["truth"]) for r in rb)
        for ans in ANSWERS:
            md.append(f"| {ANSWER_NAMES[ans]} | " + " | ".join(str(c[(ans, t)]) for t in ANSWERS) + " |")
        agree = sum(c[(t, t)] for t in ANSWERS)
        unsafe = sum(c[(ans, "not")] for ans in ("offered", "after"))
        md += ["", f"- Agreement: {rate(agree, len(rb))}.",
               f"- Offered (now or after a reconfiguration) though the module cannot: {unsafe}."]
        planned = [r for r in rb if r.get("route") == "planned"]
        if planned:
            right = sum(bool(r.get("planned_right")) for r in planned)
            times = [r["plan_s"] for r in planned]
            md += [f"- Planned: {len(planned)}; right the first time in the oracle: {rate(right, len(planned))}.",
                   f"- Time to plan (median of 5 each): median {1000 * statistics.median(times):.2f} ms, "
                   f"at most {1000 * max(times):.2f} ms.",
                   f"- Doses in the plans: {sorted(Counter(sum(1 for s in r['plan'] if s[0] == 'Dosing') for r in planned).items())}"]
        md += ["", "Per variant: agreement.", "", "| Variant | Cases | Agree | Offered | After | Not |", "| --- | --- | --- | --- | --- | --- |"]
        for v in sorted({r["variant"] for r in rb}, key=lambda v: ("full", "no scale", "small pump", "raised").index(v)):
            rs = [r for r in rb if r["variant"] == v]
            md.append(f"| {v} | {len(rs)} | {sum(r['answer'] == r['truth'] for r in rs)} | "
                      + " | ".join(str(sum(r["answer"] == t for r in rs)) for t in ANSWERS) + " |")
        md += ["", "### Disagreements", ""]
        for r in rb:
            if r["answer"] != r["truth"]:
                md.append(f"- {r['variant']}, {r['container']} {r['volume']} mL{', weight' if r['weight'] else ''}: "
                          f"answer {ANSWER_NAMES[r['answer']]} ({r.get('route', '')} {r.get('by', '')}), truth "
                          f"{ANSWER_NAMES[r['truth']]}")
    rt = [r for r in rows if r.get("part") == "t"]
    if rt:
        planned_t = [r for r in rt if r["answer"] == "after"]
        md += ["", "## Part t: filling from the bottom, the needle rising with the liquid", "",
               f"{len(rt)} cases: the syringe at {sorted({r['volume'] for r in rt})} mL, with and without its weight, "
               f"on {len({r['variant'] for r in rt})} module variants; the needle within 2 mm above and 3 mm below the "
               "liquid, planned by tracking, run in the oracle (which checks the 2 mm, not the 3).", "",
               "| Variant | Cases | Planned | Tracked | Right in the oracle | Not planned | Truth not |",
               "| --- | --- | --- | --- | --- | --- | --- |"]
        for v in sorted({r["variant"] for r in rt}, key=lambda v: ("full", "no scale", "small pump", "raised").index(v)):
            rs = [r for r in rt if r["variant"] == v]
            ps = [r for r in rs if r["answer"] == "after"]
            md.append(f"| {v} | {len(rs)} | {len(ps)} | {sum(bool(r.get('tracked')) for r in ps)} | "
                      f"{sum(bool(r.get('planned_right')) for r in ps)} | {len(rs) - len(ps)} | {sum(r['truth'] == 'not' for r in rs)} |")
        if planned_t:
            right = sum(bool(r.get("planned_right")) for r in planned_t)
            md += ["", f"- Planned: {len(planned_t)}; right the first time in the oracle: {rate(right, len(planned_t))}.",
                   f"- Not planned where the oracle says the module can: "
                   f"{sum(r['answer'] == 'not' and r['truth'] != 'not' for r in rt)}; planned where it cannot: "
                   f"{sum(r['answer'] == 'after' and r['truth'] == 'not' for r in rt)}.",
                   f"- Flow rates set: {sorted({r['flow_rate'] for r in planned_t if r.get('flow_rate')})} mL/s; time to plan: median "
                   f"{1000 * statistics.median(r['plan_s'] for r in planned_t):.2f} ms."]
        for r in rt:
            if r["answer"] == "after" and not r.get("planned_right"):
                md.append(f"- Wrong: {r['variant']}, {r['volume']} mL: {r.get('planned_broken')}")
    out = a.rows.with_suffix(".md")
    out.write_text("\n".join(md) + "\n", encoding="utf-8")
    print(out)


if __name__ == "__main__":
    main()
