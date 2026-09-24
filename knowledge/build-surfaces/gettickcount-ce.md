# `GetTickCount` — neutral developer build-surface model

## Scope and evidence

| Field | Value | Status / evidence |
|---|---|---|
| Symbol | `GetTickCount` | Documented in the CE 3.0 developer reference. |
| Syntax | `DWORD GetTickCount(void)` | Documented. |
| Return behavior | Milliseconds elapsed since Windows CE started; wraps after the 32-bit millisecond range. | Documented. |
| Minimum OS version | Windows CE 1.0 | Documented by the CE 5.0 reference; independently corroborated by the CE 3.0 developer reference. |
| Header | `Winbase.h` | Documented. |
| Link library | `Coredll.lib` | Documented by the CE 5.0 reference. |
| CPU / ABI | Unknown | Neither topic establishes a target CPU, export decoration, or calling convention. |
| Runtime availability | Platform-dependent | The CE 3.0 developer reference says particular OEM platforms may not support an API included in the complete OS package. |

Primary evidence retained in this corpus:

1. `docs/chm/windows-ce-3.0/wcesdkrGetTickCount.html` (official CE 3.0
   documentation archive): documents the developer-facing syntax, CE 1.0+
   applicability, `Winbase.h`, elapsed-time behavior, and OEM caveat.
2. `docs/mslearn/windows-ce-5.0/ms885645.html` (Microsoft Learn archival
   page): independently documents the syntax, CE 1.0+ applicability,
   `Winbase.h`, and `Coredll.lib`.

## Projection decision

`akari-dev` projects only the documented C signature and a fixed-width
project-owned `DWORD` typedef. It deliberately omits a calling-convention macro,
import declaration, decorated symbol name, `.def`, and import library: those
ABI/linker details remain `unknown` and must not be inferred from desktop Win32.

The `DWORD` width is an **inference** from the documented 49.7-day wrap interval
for a millisecond count; it is represented as `uint32_t` so the project header
has that documented value range on hosts where C `unsigned long` is not 32 bits.
This is a project representation choice, not a copied WinCE header definition.

## Open evidence predicates

* Observe or obtain a rights-cleared header/artifact for calling convention and
  target-specific import/export decoration.
* Inspect a Coredll import library or executable import table for at least one
  named WinCE CPU target before adding link metadata.
* Run on a compatible CE runtime before claiming timing resolution or debug-build
  behavior.
