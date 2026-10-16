#!/usr/bin/env python3
"""Last-rank numeric gap-fill from the pinned MIT dotnet/pinvoke snapshot.

Not a copy of any C header.  A value is used only when:

* a Windows CE page *names* the constant
* no CE page, Win32 CC-BY page, or public-domain CeGCC w32api numbers it
* the snapshot prints a single integer (hex or decimal)

Licence: MIT (sources/dotnet-pinvoke/pinvoke-LICENSE.txt)
Provenance: sources/dotnet-pinvoke/PROVENANCE.md
    commit d974353ca67c4b8e6009096bd3ab7e6f284ed11d, archived github.com/dotnet/pinvoke
Acquisition: the tarball already stored under sources/dotnet-pinvoke/
             (fetched as the project's pinned aux snapshot)

This is the source family mingw/CeGCC did *not* invent: community
numbers of names Microsoft documented.  It is weaker than a CE page
and weaker than w32api public-domain headers.
"""

from __future__ import annotations

import gzip
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import header_map  # noqa: E402
import w32api_gaps  # noqa: E402

JSONL = os.path.join(ROOT, "knowledge", "aux", "pinvoke-constants.jsonl.gz")
COMMIT = "d974353ca67c4b8e6009096bd3ab7e6f284ed11d"

_NUM = re.compile(r"^(0x[0-9A-Fa-f]+|-?\d+)[uUlL]*$")

MODULE_HEADER = {
    "User32": "Winuser.h",
    "Kernel32": "Winbase.h",
    "Gdi32": "Wingdi.h",
    "AdvApi32": "Winreg.h",
    "Ntdll": "Winnt.h",
    "Shell32": "Shellapi.h",
    "Comctl32": "Commctrl.h",
    "Comdlg32": "Commdlg.h",
    "Ole32": "Objbase.h",
    "Ws2_32": "Winsock2.h",
}


def parse_constants(ce_named, already_numbered):
    """CE-named constants still unnumbered, filled from MIT pinvoke."""
    out = {}
    path = JSONL
    if not os.path.exists(path):
        path = path[:-3]
    if not os.path.exists(path):
        return out
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if not line:
                continue
            rec = json.loads(line)
            name = rec.get("name") or ""
            if name in w32api_gaps.NEVER or name in already_numbered:
                continue
            if name not in ce_named:
                continue
            if name in out:
                continue
            value = str(rec.get("value") or "").strip()
            if not _NUM.match(value):
                continue
            header = header_map.header_for_constant(name)
            if not header:
                header = MODULE_HEADER.get(rec.get("module") or "")
            if not header or header.lower() == "windows.h":
                header = MODULE_HEADER.get(rec.get("module") or "") or "Winuser.h"
            src = rec.get("source") if isinstance(rec.get("source"), dict) else {}
            out[name] = {
                "name": name,
                "value": value,
                "header": header,
                "layer": "ce",
                "origin": "dotnet-pinvoke-mit",
                "win32_fallback": False,
                "discarded": [],
                "source": {
                    "path": src.get("path") or (
                        "sources/dotnet-pinvoke/"
                        f"pinvoke-{COMMIT}-src.tar.gz"),
                    "member": src.get("archive_member") or "",
                    "line": src.get("line") or "",
                    "layer": "aux",
                    "set": "sources/dotnet-pinvoke",
                    "title": rec.get("page_id") or name,
                    "page_id": rec.get("page_id") or "",
                    "license": "dotnet-pinvoke-mit",
                },
            }
    return out
