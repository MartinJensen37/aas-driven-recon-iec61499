# FORTE for the filling module

The Dockerfile builds Eclipse 4diac FORTE 3.3.0 from source with the patches below, applied in name order, and links in the
module's block types (`types/`, exported from the 4diac projects in `module/4diac` by the 4diac IDE 3.3).

| Patch | Why |
| --- | --- |
| 0001 | An IO handle keeps its own copy of its id (callers pass temporaries). |
| 0002 | PWM on Linux through sysfs (`PWMChip`), for the module's Raspberry Pi. |
| 0003 | Stand-ins for `GPIOChip` and `PWMChip` where they are not built, so the module's types are the same everywhere. |
| 0004 | A GPIO input is read, never written, so deleting a running resource does not restart the IO controller. |
| 0005 | The management port is reused at once after a restart, instead of being held in TIME_WAIT. |
| 0006 | An IO configuration block deleted while running stops its controller without calling into a deleted object. |
| 0007 | Reading back: a generic type (`GEN_SERVER` for `SERVER_2_2`) passes the type query instead of failing it. |
| 0008 | Reading back: the connections of a large program are queried part by part (one answer holds at most 64 KiB). |
| 0009 | The stand-ins of 0003 also on a Linux PC without GPIO (the container). |

0007 and 0008 are the two runtime patches the paper's synchroniser needs to read a program back. The event lists are
1024 long (`FORTE_EventChain*ListSize`): the module's state reaches every block at once, more than 256 events for 20
composites.
