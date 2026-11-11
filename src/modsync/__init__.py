"""The synchroniser, which keeps a module's running IEC 61499 application consistent with its AAS.

It reads the application back through management commands (``device``), reconstructs the composite
skills by the mapping rules in reverse (``structure``), compares them with the Skills submodel
(``desired``, ``described``), applies online what can be applied and refuses what needs a restart
(``sync``), verifies the change by reading it back, and adds it to the module's boot file.
"""
