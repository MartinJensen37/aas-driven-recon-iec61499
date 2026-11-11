"""The planner and the checker: a new composite skill from a module's primitive skills, and a skill's
flow checked over time against the capability constraints.

- ``expression``: the language of a constraint (an IDTA 02020 BasicConstraint);
- ``domain``: a module's planning domain: its state variables, its capabilities with what they
  need, do and keep, its rest state;
- ``vocabulary``: what holds of each kind of capability wherever it is used (the lab's vocabulary);
- ``read``: a module's planning domain from its AAS;
- ``check``: runs a skill's flow through the states and reports what does not hold;
- ``plan``: the steps of a new skill, a hybrid of HTN and goal regression on GTPyhop;
- ``lift``: a plan as a flow, with parallel blocks where nothing orders two steps;
- ``compose``: a planned skill, checked and described in the module's AAS;
- ``discover``: the process capabilities a module can carry out, by a skill or by a plan.
"""
