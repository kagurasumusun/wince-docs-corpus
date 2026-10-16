# Toolchain surface — what may be compiled and linked

`winsur/include/*.h` and `winsur/link/*.def` are for building **Windows CE
applications and drivers** (compiler + linker).  Facts are mixed from
several licences.  **No C header file is copied** from any third-party
tree.

## How to include

```c
#include "Windows.h"   /* WinDef, WinNT, winerror, Winbase, Winuser, Wingdi, Winreg */
#include "CEDDK.h"     /* drivers */
#include "Winsock2.h"  /* sockets, not in the umbrella */
#include "Commctrl.h"  /* common controls, not in the umbrella */
```

A GCC syntax check of `WinMain` + `CreateFile`/`MessageBox` and of `DllMain` + `CEDDK.h` is `tools/tests/test_compile_surface.py`.

Link with `link/coredll.def` (and the other module `.def` files you actually import).

## 1. Quoted from Windows CE documentation (`knowledge/`)

Header/library/DLL names, prototypes, structs, and **numbers a CE page printed**.
Each fact names its page.  Those pages are mostly **not** licensed for
redistribution (Learn terms, CE 3.0 internal-reference notice, CHM/MVB with
no permission statement).  See `docs/LICENSING.md`.

This is also what CeGCC/mingw.org w32api was written *from* (Anders Norlander
reconstructed headers from public MSDN, not from Microsoft SDK files).

## 2. Shared Win32 reference (CC-BY-4.0)

`corpus/win32/api/` and `corpus/win32/common/` (MicrosoftDocs/sdk-api and
the Windows Data Types page).  Numbers and typedefs a CE page named but
did not spell.  Attribution: CC-BY-4.0.

## 3. Gap-fill from CeGCC w32api (public domain) — not a copy

When a CE page **names** a constant but prints no number, the generator may
take the `#define` from the pinned CeGCC `w32api` headers (membership +
value only; never a whole file).

| | |
|--|--|
| What | CeGCC `w32api` module, classic mingw.org Win32 API **adapted for CE** |
| Not | Microsoft SDK headers; not Wine; not ReactOS; not mingw-w64 |
| Acquisition | `https://codeload.github.com/MaxKellermann/w32api/tar.gz/8e64b608fc9c4d81e206e920ecc977d941577bef` (2026-10-14) |
| Pin | commit `8e64b608fc9c4d81e206e920ecc977d941577bef` |
| Bytes | `sources/w32api-cegcc/w32api-cegcc-8e64b608fc9c4d81e206e920ecc977d941577bef-src.tar.gz` |
| Licence | `sources/w32api-cegcc/PUBLIC-DOMAIN-README.w32api.txt`: “THIS SOFTWARE IS NOT COPYRIGHTED… offered for use in the public domain. You may use, modify or distribute it freely.” |
| Provenance | `sources/w32api-cegcc/PROVENANCE.md` |
| Not copied | `winsock.h` / `winsock2.h` / `ws2tcpip.h` (UCB/DEC copyright); `gl.h` / `glext.h` / `glu.h` (Mesa / SGI) |
| Never overlaid | `MAX_PATH` (CE pages print **128**); C type names (`BOOL`, `DWORD`, `HANDLE`, …) |

## 4. Last-rank numbers from dotnet/pinvoke (MIT) — not a copy

When a CE page still names a constant that (1)–(3) did not number, an
integer from the pinned MIT snapshot may be used.

| | |
|--|--|
| What | Archived .NET Foundation `github.com/dotnet/pinvoke` (pinvoke.net data as C#) |
| Acquisition | already pinned: `sources/dotnet-pinvoke/` (commit `d974353ca67c4b8e6009096bd3ab7e6f284ed11d`) |
| Licence | MIT (`sources/dotnet-pinvoke/pinvoke-LICENSE.txt`) |
| Provenance | `sources/dotnet-pinvoke/PROVENANCE.md` |
| Scope | integer `public const` / enum members only; CE-named; never `MAX_PATH` |

A CE-printed number always wins, then a Win32 CC-BY number, then w32api,
then pinvoke.
