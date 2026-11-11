"""The module's IEC 61499 application, generated from its module specification.

One application per target: the module level (occupation and the module state manager), one
equipment IO block per item of equipment (``EQ_<Item>``), one instance of every offered primitive
skill (``SK_<Skill>``), the procedures the module state manager runs while Resetting and Stopping,
and the composite skills.

A composite skill is an untyped subapplication of library blocks: its state machine (SKILL_Core),
the Start method with one latch per parameter, the OPC UA publishers, and its Execute and Stop
flows of private primitive skill instances, which run one after the other, in parallel blocks
(SKILL_Join<n>) or in decisions (SKILL_Condition_<type>, SKILL_Merge). Needing no type of its own,
it can be created in a running FORTE through management commands.
"""
from __future__ import annotations

from dataclasses import dataclass, field
from itertools import count

from .fbxml import SubNet, connections, elem, fb, publish, server, subapp, wstr
from .library import q
from .spec import AllOf, Comparison, ModuleSpec, Parallel, Parameter, Step, ms, walk


def tlit(duration: str) -> str:
    """IEC TIME literal of ``200ms`` or ``2s``."""
    return f"T#{ms(duration)}ms"


def value_lit(value, typ: str) -> str:
    """IEC literal of a constant for a parameter of type ``typ``."""
    return Parameter(type=typ, default=value).literal() if typ != "BOOL" else ("TRUE" if value else "FALSE")


def ua_literal(kind: str, paths) -> str:
    """WSTRING literal of the OPC UA ID (``opc_ua[<kind>;<path>;...]``) of an instance in the application."""
    return wstr(f"opc_ua[{kind};{';'.join(paths)}]")


def start_method(n: SubNet, params: dict[str, Parameter], methods: str, params_id: str) -> tuple[list[str], str]:
    """The Start method of a composite skill whose core is the instance ``Control`` (SKILL_Core) in ``n``.

    UaStart (Start(Session, parameters...), offered over OPC UA if ``methods``): each parameter latch
    (named like its parameter) checks its argument and passes the result on, the last one to
    Control.START_REQ. Control.RUN latches the arguments (or the defaults, for a start from a parent)
    one after the other and PubParams publishes them at ``params_id``. Returns the INIT chain after
    Control and the event that fires once the values are latched.
    """
    n.fb("UaStart", server(2, 1 + len(params)), QI=methods)
    n.da("Control.StartMethodId", "UaStart.ID")
    n.da("UaStart.RD_1", "Control.Session")
    n.ev("Control.START_RSP", "UaStart.RSP")
    n.da("Control.Accepted", "UaStart.SD_1")
    n.da("Control.StartError", "UaStart.SD_2")
    if not params:
        n.ev("UaStart.IND", "Control.START_REQ")
        return ["UaStart"], "Control.RUN"
    chain = list(params)
    for k, (x, pr) in enumerate(params.items()):
        bounds = {v: pr.literal(b) for v, b in (("Lower", pr.minimum), ("Upper", pr.maximum)) if b is not None}
        n.fb(x, q(f"SKILL_Param_{pr.type}"), Default=pr.literal(), **bounds)
        n.da(f"UaStart.RD_{k + 2}", f"{x}.Requested")
        n.da("Control.CalledByClient", f"{x}.CalledByClient")
        n.da(f"{x}.Value", f"PubParams.SD_{k + 1}")
    n.fb("PubParams", publish(len(params)), QI="TRUE", ID=params_id)
    n.ev("UaStart.IND", chain[0] + ".CHECK")
    n.ev("Control.RUN", chain[0] + ".LATCH")
    for a, z in zip(chain, chain[1:]):
        n.ev(a + ".CHECKED", z + ".CHECK")
        n.da(a + ".AllInRange", z + ".PreviousInRange")
        n.ev(a + ".LATCHED", z + ".LATCH")
    n.ev(chain[-1] + ".CHECKED", "Control.START_REQ")
    n.da(chain[-1] + ".AllInRange", "Control.ParamsInRange")
    n.ev(chain[-1] + ".LATCHED", "PubParams.REQ")
    n.ev("PubParams.INITO", "PubParams.REQ")           # publishes the defaults once
    return ["UaStart", *chain, "PubParams"], chain[-1] + ".LATCHED"


def result_type(spec: ModuleSpec, steps: list[Step], source: str) -> str:
    """Type of a flow's result ``<step>.<result>``: the equipment input behind the step's result."""
    step_name, _, res = source.partition(".")
    skill = spec.skills[next(s for s in steps if s.name == step_name).skill]
    return spec.equipment[skill.equipment].inputs[skill.results[res]].type


def skill_instance(net, spec: ModuleSpec, step: Step, x, y, ua_path: str, token: str, top: bool, methods: bool,
                   ua_root: str):
    """An SK_ instance for a step, with its constant parameter bindings; ``top``: it releases its
    equipment with its final command (ReleaseAfter)."""
    skill = spec.skills[step.skill]
    params = {"Module": wstr(spec.module), "UaRoot": ua_root, "UaPath": wstr(ua_path), "UaEnable": "TRUE",
              "Methods": "TRUE" if methods else "FALSE", "Holder": wstr(token),
              "ReleaseAfter": "TRUE" if top else "FALSE"}
    for n, v in step.bind.items():
        if not isinstance(v, str):
            params[n] = value_lit(v, skill.parameters[n].type)
    return fb(net, step.name, f"{spec.package}::SK_{step.skill}", x, y, **params)


@dataclass
class Block:
    """A part of a flow, as its connections see it: the event inputs that start it, the event outputs
    that say it is done, and its failures (event output, ErrorID output) not handled inside it."""
    starts: list[str]
    done: list[str]
    failures: list[tuple[str, str]] = field(default_factory=list)


def flow(net, spec: ModuleSpec, name: str, nodes: list, x, y, ua_prefix: str, token: str | None, comment: str,
         params: dict[str, Parameter] | None = None, results: dict[str, str] | None = None, parent_events: bool = True):
    """Subapp running a flow: START -> DONE, any FAILURE -> FAILED(ErrorID). Steps run one after the
    other; a parallel block starts its branches at once and its SKILL_Join<n> (named like the block)
    says when all are done, or halts the others when one fails; a decision's conditions
    (SKILL_Condition_<type>, named ``<decision>_C<k>``) choose a branch, which ends in its SKILL_Merge
    (named like the decision).

    ``token``: the lock token of a composite skill. Every step of a composite skill holds the skill's
    equipment under the skill's name and gives up nothing itself: which step uses an item last depends
    on the path, and the skill's Control releases everything when a run ends. None for a procedure,
    whose steps take and give up their own. Results come from steps that run on every path."""
    params, results = params or {}, results or {}
    ei = {"INIT": ([], "EInit"), "START": list(params)}
    if parent_events:
        ei.update({"HALT": [], "ABORT": [], "RESET": []})
    every = list(walk(nodes))
    rtypes = {r: result_type(spec, every, src) for r, src in results.items()}
    eo = {"INITO": ([], "EInit"), "DONE": list(results), "FAILED": ["ErrorID"]}
    _, inner = subapp(net, name, x, y, comment, ei, eo, {n: pr.type for n, pr in params.items()},
                      {"ErrorID": "UINT", **rtypes})
    ua_root = wstr(spec.opcua_root)
    ev: list[tuple[str, str]] = []
    da: list[tuple[str, str]] = []
    column = count()
    holder = token or ua_prefix.strip("/")

    def at() -> int:
        return 1000 + next(column) * 5000

    def merged(failures: list[tuple[str, str]], prefix: str, row: int) -> tuple[str, str]:
        """One failure of several (SKILL_FailMerge pairwise: a data input takes one connection)."""
        event, error = failures[0]
        for i, (e, err) in enumerate(failures[1:], 1):
            m = f"{prefix}{i}"
            fb(inner, m, q("SKILL_FailMerge"), at(), row + 3000)
            ev.extend([(event, f"{m}.FAIL_1"), (e, f"{m}.FAIL_2")])
            da.extend([(error, f"{m}.Error1"), (err, f"{m}.Error2")])
            event, error = f"{m}.FAIL", f"{m}.Error"
        return event, error

    def condition(c, owner: str, ids: count, row: int) -> tuple[str, list[str], list[str]]:
        """(the event input that evaluates it, its YES outputs, its NO outputs)."""
        if isinstance(c, Comparison):
            inst = f"{owner}_C{next(ids)}"
            typ = params[c.operand].type if c.operand in params else result_type(spec, every, c.operand)
            value = ("TRUE" if c.value else "FALSE") if typ == "BOOL" else value_lit(c.value, typ)
            fb(inner, inst, q(f"SKILL_Condition_{typ}"), at(), row, Expected=value, Operator=f"'{c.op}'")
            step_, _, res = c.operand.partition(".")
            da.append((c.operand if not res else f"{step_}.R_{res}", f"{inst}.Operand"))
            return f"{inst}.EVAL", [f"{inst}.YES"], [f"{inst}.NO"]
        parts = [condition(inner_, owner, ids, row) for inner_ in (c.all if isinstance(c, AllOf) else c.any)]
        for a, b in zip(parts, parts[1:]):
            ev.extend((out, b[0]) for out in (a[1] if isinstance(c, AllOf) else a[2]))
        if isinstance(c, AllOf):
            return parts[0][0], parts[-1][1], [o for part in parts for o in part[2]]
        return parts[0][0], [o for part in parts for o in part[1]], parts[-1][2]

    def node_block(node, row: int) -> Block:
        if isinstance(node, Step):
            skill_instance(inner, spec, node, at(), row, f"{ua_prefix}/{node.name}", holder, token is None, False,
                           ua_root)
            da.extend((v, f"{node.name}.{p_}") for p_, v in node.bind.items() if isinstance(v, str))
            return Block([f"{node.name}.START"], [f"{node.name}.SUCCESS"],
                         [(f"{node.name}.FAILURE", f"{node.name}.ErrorID")])
        if isinstance(node, Parallel):
            join, n = node.name, len(node.branches)
            fb(inner, join, q(f"SKILL_Join{n}"), at(), row)
            branches = [build(branch, row + (i + 1) * 6000) for i, branch in enumerate(node.branches)]
            for i, b in enumerate(branches, 1):
                ev.extend((d, f"{join}.DONE_{i}") for d in b.done)
                event, error = merged(b.failures, f"{join}_Fail{i}_", row)
                ev.append((event, f"{join}.FAILED_{i}"))
                da.append((error, f"{join}.Error{i}"))
            ev.extend((f"{join}.HALT", f"{s.name}.HALT") for branch in node.branches for s in walk(branch))
            # The join first: it forgets the last run before a branch can report.
            return Block([f"{join}.START", *[s for b in branches for s in b.starts]], [f"{join}.DONE"],
                         [(f"{join}.FAILED", f"{join}.Error")])
        meet = node.name
        entry, yes, no = condition(node.condition, meet, count(1), row)
        fb(inner, meet, q("SKILL_Merge"), at(), row)
        then = build(node.then, row + 6000)
        ev.extend((y_, s_) for y_ in yes for s_ in then.starts)
        ev.extend((d, f"{meet}.EI1") for d in then.done)
        failures = list(then.failures)
        if node.otherwise:
            other = build(node.otherwise, row + 12000)
            ev.extend((n_, s_) for n_ in no for s_ in other.starts)
            ev.extend((d, f"{meet}.EI2") for d in other.done)
            failures += other.failures
        else:
            ev.extend((n_, f"{meet}.EI2") for n_ in no)
        return Block([entry], [f"{meet}.EO"], failures)

    def build(seq: list, row: int) -> Block:
        whole: Block | None = None
        for node in seq:
            part = node_block(node, row)
            if whole is None:
                whole = part
                continue
            ev.extend((d, s_) for d in whole.done for s_ in part.starts)
            whole = Block(whole.starts, part.done, whole.failures + part.failures)
        return whole

    top = build(nodes, y)
    ev.extend(("START", s_) for s_ in top.starts)
    ev.extend((d, "DONE") for d in top.done)
    event, error = merged(top.failures, "Fail", y)
    ev.append((event, "FAILED"))
    da.append((error, "ErrorID"))
    names_ = [s_.name for s_ in every]
    ev += [("INIT", names_[0] + ".INIT"), (names_[-1] + ".INITO", "INITO")]
    ev += [(a + ".INITO", b + ".INIT") for a, b in zip(names_, names_[1:])]
    if parent_events:
        for e in ["HALT", "ABORT", "RESET"]:
            ev += [(e, f"{n_}.{e}") for n_ in names_]
    for r, src in results.items():
        st, _, res = src.partition(".")
        da.append((f"{st}.R_{res}", r))
    connections(inner, ev, da)
    return name


def module_skill(net, spec: ModuleSpec, name: str, x, y):
    """Subapp of a composite skill, of library instances only: Control (SKILL_Core), the Start method
    with one latch per parameter (named like the parameter) and the OPC UA publishers; then the Execute
    flow and the optional Stop flow. Control gives up all the skill holds at every end of a run
    (ReleaseAll, on the module's release channel). Its OPC UA IDs are written as values, since no type
    of its own computes them."""
    comp = spec.composites[name]
    _, inner = subapp(net, name, x, y, f"Composite skill {name}: {comp.description}".rstrip(": "),
                      {"INIT": ([], "EInit")}, {"INITO": ([], "EInit")})
    n = SubNet(inner)
    root, path = spec.opcua_root, f"/Skills/{name}"
    methods = "TRUE" if comp.offered else "FALSE"
    n.fb("Control", q("SKILL_Core"), Module=wstr(spec.module), UaRoot=wstr(root), UaPath=wstr(path),
         UaEnable="TRUE", Methods=methods, Holder=wstr(name), ReleaseAll="TRUE" if spec.uses(name) else "FALSE")
    params_id = ua_literal("WRITE", [f"{root}{path}/Parameters/{p}" for p in comp.parameters])
    start, go = start_method(n, comp.parameters, methods, params_id)
    chain = ["Control", *start]
    if comp.results:
        n.fb("PubResults", publish(len(comp.results)), QI="TRUE",
             ID=ua_literal("WRITE", [f"{root}{path}/Results/{r}" for r in comp.results]))
        n.ev("Execute.DONE", "PubResults.REQ")
        for k, r in enumerate(comp.results, 1):
            n.da(f"Execute.{r}", f"PubResults.SD_{k}")
        chain.append("PubResults")
    flow(inner, spec, "Execute", comp.execute, 1000, 5000, f"{path}/Execute", name,
         f"{name}: execute flow", comp.parameters, comp.results)
    chain.append("Execute")
    n.ev(go, "Execute.START")
    for p in comp.parameters:
        n.da(f"{p}.Value", f"Execute.{p}")
    for ev in ["HALT", "ABORT", "RESET"]:
        n.ev(f"Control.{ev}_SEQ", f"Execute.{ev}")
    n.ev("Execute.DONE", "Control.EXECUTE_DONE")
    n.ev("Execute.FAILED", "Control.EXECUTE_FAILED")
    n.da("Execute.ErrorID", "Control.ExecuteError")
    if comp.stop:
        # Published below .../Stopping: a "Stop" object would collide with the skill's Stop method.
        flow(inner, spec, "Stop", comp.stop, 9000, 5000, f"{path}/Stopping", name, f"{name}: stop flow")
        chain.append("Stop")
        n.ev("Control.RUN_STOPPING", "Stop.START")
        n.ev("Control.ABORT_SEQ", "Stop.ABORT")
        n.ev("Control.RESET_SEQ", "Stop.RESET")
        n.ev("Stop.DONE", "Control.STOPPING_DONE")
        n.ev("Stop.FAILED", "Control.STOPPING_DONE")
    else:
        n.ev("Control.RUN_STOPPING", "Control.STOPPING_DONE")
    n.chain("INIT", chain, "INITO")
    n.write()
    return name


def parameter_port(spec: ModuleSpec, skill: str, parameter: str) -> str:
    """Where the application holds a skill's parameter default: an input of the primitive skill's
    instance, or the Default of the composite skill's parameter latch."""
    return f"{skill}.{parameter}.Default" if skill in spec.composites else f"{skill}.{parameter}"


def app_name(spec: ModuleSpec, target: str) -> str:
    """Application of ``target``: the module's name for the first target, ``<Module>_<target>`` else."""
    return spec.module if target == next(iter(spec.targets)) else f"{spec.module}_{target}"


def application(root, spec: ModuleSpec, target: str):
    """The module's application on ``target``, in rows: module level, equipment IO, primitive skills,
    composite skills, procedures."""
    pkg, ua_root = spec.package, wstr(spec.opcua_root)
    module = wstr(spec.module)
    t = spec.targets[target]
    app = elem(root, "Application", Name=app_name(spec, target),
               Comment=f"Module {spec.module} on target {target} ({t.host}, IO {t.io}; generated by modgen)")
    net = elem(app, "SubAppNetwork")
    fb(net, "Occupation", q("MOD_Occupation"), 5000, 200, Module=module, UaRoot=ua_root, UaEnable="TRUE")
    fb(net, "Module", q("MOD_StateManager"), 9000, 200, Module=module, UaRoot=ua_root, UaEnable="TRUE",
       StopTimeout=tlit(spec.stop_timeout))
    chain = ["Occupation", "Module"]        # an IO point sets up its own line (its address): no line blocks
    for i, (name, eq) in enumerate(spec.equipment.items()):
        io = {}
        for s, point in [*eq.inputs.items(), *eq.outputs.items()]:
            if getattr(point, "computed", False):
                continue
            io[f"{s}_Address"] = f"'{spec.address(target, point)}'"
        fb(net, name, f"{pkg}::EQ_{name}", 2000 + i * 5000, 3000, Module=module, UaRoot=ua_root, UaEnable="TRUE", **io)
        chain.append(name)
    for i, (name, skill) in enumerate((n, s) for n, s in spec.skills.items() if s.offered):
        skill_instance(net, spec, Step(skill=name, name=name), 2000 + i * 5000, 6000, f"/Skills/{name}", name, True,
                       True, ua_root)
        chain.append(name)
    events, data = [], []                 # the resource's START starts the INIT chain (start_links)
    for i, proc in enumerate(["Resetting", "Stopping"]):
        upper = proc.upper()
        if proc in spec.procedures:
            flow(net, spec, proc, spec.procedures[proc], 2000 + i * 5000, 12000, f"/Procedures/{proc}", None,
                 f"Procedure the module runs while {proc}", parent_events=False)
            chain.append(proc)
            events += [(f"Module.RUN_{upper}", f"{proc}.START"), (f"{proc}.DONE", f"Module.{upper}_DONE"),
                       (f"{proc}.FAILED", f"Module.{upper}_FAILED")]
        else:
            events.append((f"Module.RUN_{upper}", f"Module.{upper}_DONE"))
    # Composite skills come last: one added online extends the INIT chain at its end.
    for i, name in enumerate(spec.composites):
        module_skill(net, spec, name, 2000 + i * 5000, 9000)
        chain.append(name)
    events += [(a + ".INITO", z + ".INIT") for a, z in zip(chain, chain[1:])]
    connections(net, events, data)
    return app


def start_links(app) -> list[tuple[str, str]]:
    """The resource's own START block (COLD, WARM) to the head of the application's INIT chain: the
    one block whose INIT nothing in the application drives."""
    pairs = [(c.get("Source"), c.get("Destination"))
             for c in app.iterfind("SubAppNetwork/EventConnections/Connection")]
    driven = {d for _, d in pairs if d.endswith(".INIT")}
    heads = [s[:-len("O")] for s, d in pairs
             if s.endswith(".INITO") and d.endswith(".INIT") and s[:-len("O")] not in driven]
    head = next(iter(dict.fromkeys(heads)))
    return [("START.COLD", head), ("START.WARM", head)]
