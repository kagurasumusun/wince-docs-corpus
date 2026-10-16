#!/usr/bin/env python3
"""Fill unnamed CE constants from the pinned public-domain CeGCC w32api.

Licence (sources/w32api-cegcc/PUBLIC-DOMAIN-README.w32api.txt):
    THIS SOFTWARE IS NOT COPYRIGHTED.  This source code is offered for
    use in the public domain. You may use, modify or distribute it freely.

Provenance: sources/w32api-cegcc/PROVENANCE.md
    tarball 8e64b608fc9c4d81e206e920ecc977d941577bef, fetched 2026-10-14
    from the CeGCC w32api module (not Microsoft).

Scope:
    * include/*.h at the tarball top level (no GL/, no recursion)
    * NOT winsock.h / winsock2.h / ws2tcpip.h (UCB/DEC copyright)
    * NOT gl.h / glext.h / glu.h (Mesa / SGI)
    * a value is taken only when a CE page *names* the constant and no
      CE/Win32 documentation page in knowledge/ numbers it
    * MAX_PATH is never taken (CE pages print 128)

This is gap-fill for a compiler/linker surface, not a replacement of
the CE documentation.
"""

from __future__ import annotations

import os
import re
import tarfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TARBALL = os.path.join(
    ROOT, "sources", "w32api-cegcc",
    "w32api-cegcc-8e64b608fc9c4d81e206e920ecc977d941577bef-src.tar.gz")
COMMIT = "8e64b608fc9c4d81e206e920ecc977d941577bef"
PREFIX = f"w32api-{COMMIT}/include/"

SKIP_FILES = {
    "winsock.h", "winsock2.h", "ws2tcpip.h",
    "gl.h", "glext.h", "glu.h",
}

_DEFINE = re.compile(
    r"^[ \t]*#[ \t]*define[ \t]+([A-Z][A-Z0-9_]{1,80})[ \t]+(\S+)",
    re.M)
_TYPEDEF = re.compile(
    r"^[ \t]*typedef[ \t]+(.+?)[ \t]+([A-Za-z_][A-Za-z0-9_]*)\s*;",
    re.M)

# Never overlay these from w32api: CE pages print a different number,
# or the name is a C type not a constant.
NEVER = {
    "MAX_PATH",  # CE documents 128
    "BOOL", "BYTE", "WORD", "DWORD", "HANDLE", "HWND", "HINSTANCE",
    "HMODULE", "HDC", "HMENU", "HKEY", "HBITMAP", "HFONT", "HPEN",
    "UINT", "INT", "LONG", "ULONG", "SHORT", "CHAR", "WCHAR", "TCHAR",
    "FLOAT", "ATOM", "BOOLEAN", "COLORREF", "LPVOID", "LPCVOID",
    "FAR", "NEAR", "PASCAL", "CONST",
}


def iter_public_domain_headers():
    if not os.path.exists(TARBALL):
        return
    with tarfile.open(TARBALL, "r:gz") as tf:
        for member in tf.getmembers():
            name = member.name
            if not name.startswith(PREFIX) or not name.endswith(".h"):
                continue
            rel = name[len(PREFIX):]
            if "/" in rel or rel.lower() in SKIP_FILES:
                continue
            fh = tf.extractfile(member)
            if not fh:
                continue
            text = fh.read().decode("latin1", errors="replace")
            yield rel, name, text


def parse_defines(ce_named, already_numbered):
    """CE-named constants the pages did not number, filled from w32api."""
    out = {}
    for rel, member, text in iter_public_domain_headers() or []:
        header = rel.split("/")[-1]
        for match in _DEFINE.finditer(text):
            name, value = match.group(1), match.group(2).rstrip("\\")
            if name in NEVER or name in already_numbered:
                continue
            if name not in ce_named and name not in ESSENTIALS:
                continue
            if name in out:
                continue
            if value.startswith("(") and not re.match(
                    r"^\((0x[0-9A-Fa-f]+|-?\d+|[A-Z][A-Z0-9_]*[+-]\d+)\)$",
                    value):
                # skip wide macros
                if '"' in value or "{" in value:
                    continue
            out[name] = {
                "name": name,
                "value": value,
                "header": header,
                "layer": "ce",
                "origin": "w32api-cegcc-public-domain",
                "win32_fallback": False,
                "discarded": [],
                "source": {
                    "path": f"sources/w32api-cegcc/{os.path.basename(TARBALL)}",
                    "member": member,
                    "layer": "reference",
                    "set": "w32api-cegcc",
                    "title": rel,
                    "page_id": "",
                    "license": "w32api-public-domain",
                },
            }
    return out
