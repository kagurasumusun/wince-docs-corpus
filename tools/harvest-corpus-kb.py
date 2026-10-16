#!/usr/bin/env python3
"""Re-read CE corpus pages with the current extractors and keep new facts.

Does not rewrite ``entities.jsonl.gz``.  Writes the missed constants and
C declarations the live ``page_parse`` now sees:

    knowledge/kb/harvest-constants.jsonl
    knowledge/kb/harvest-declarations.jsonl

    python3 tools/harvest-corpus-kb.py
    python3 tools/harvest-corpus-kb.py --workers 8

Clean-room for the generator is unchanged: this script *does* open
``corpus/`` (it is a knowledge-base builder, like ``build-kb.py``).
``tools/gen-include-def.py`` still reads ``knowledge/`` only.
"""

from __future__ import annotations

import argparse
import concurrent.futures
import hashlib
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import license_scopes  # noqa: E402
import page_parse  # noqa: E402
import quality_filters  # noqa: E402

INDEX = os.path.join(ROOT, "data", "index", "INDEX.tsv")
KB = os.path.join(ROOT, "knowledge", "kb")
LICENSES = license_scopes.Registry.load()
PAPERWORK = {"README.md", "PROVENANCE.md"}


def layer_of(book):
    if book.startswith("win32/") or book.startswith("win32"):
        return "win32"
    if book.startswith("dotnet"):
        return "dotnet"
    if book.startswith("oss"):
        return "oss"
    if book.startswith("pinvoke"):
        return "pinvoke"
    return "ce"


def read_index():
    rows = []
    with open(INDEX, encoding="utf-8") as fh:
        for line in fh:
            if line.startswith("#") or not line.strip():
                continue
            parts = line.rstrip("\n").split("\t")
            if len(parts) < 4:
                continue
            page_id, book, path, title = parts[0], parts[1], parts[2], parts[3]
            if os.path.basename(path) in PAPERWORK:
                continue
            if layer_of(book) != "ce":
                continue
            if quality_filters.is_sample_source(path):
                continue
            rows.append((page_id, book, path, title))
    return rows


def _license(path):
    return LICENSES.scope_for(path) or ""


_KW = {
    "WINAPI", "CALLBACK", "APIENTRY", "STDAPI", "PASCAL", "FAR", "NEAR",
    "CDECL", "const", "volatile", "unsigned", "signed", "struct", "enum",
    "union", "typedef", "static", "extern", "inline", "virtual", "class",
    "public", "private", "protected", "void", "VOID", "int", "INT", "long",
    "LONG", "short", "SHORT", "char", "CHAR", "BOOL", "DWORD", "WORD",
    "BYTE", "UINT", "ULONG", "HANDLE", "HWND", "HRESULT", "LRESULT",
    "NTSTATUS", "__stdcall", "__cdecl", "__fastcall", "STDCALL", "CDECL",
}


def identifier_from_decl(text, kind=""):
    text = text or ""
    if "(" in text and kind not in ("struct", "enum", "typedef"):
        head = text.split("(", 1)[0]
        ids = re.findall(r"[A-Za-z_][A-Za-z0-9_]*", head)
        for tok in reversed(ids):
            if tok not in _KW:
                return tok
        return ids[-1] if ids else ""
    if "}" in text:
        tail = text.rsplit("}", 1)[-1]
        ids = re.findall(r"[A-Za-z_][A-Za-z0-9_]*", tail)
        # "} CHOOSECOLOR, *LPCHOOSECOLOR;" -- the type name, not the
        # last pointer alias.
        if ids:
            return ids[0]
    ids = re.findall(r"[A-Za-z_][A-Za-z0-9_]*", text)
    for tok in reversed(ids):
        if tok not in _KW:
            return tok
    return ""


def harvest_page(job):
    page_id, book, path, title = job
    full = os.path.join(ROOT, path)
    try:
        raw = open(full, "rb").read()
    except OSError:
        return path, 0, [], []
    constants = []
    declarations = []
    src = {
        "layer": "ce",
        "license": _license(path),
        "page_id": page_id,
        "path": path,
        "set": book,
        "title": title,
    }
    try:
        if path.endswith(".md"):
            text = page_parse.decode(raw)
            _f, _r, decls, _sf = page_parse.markdown(text)
            rows = (page_parse.syntax_constant_rows(decls)
                    + page_parse.prose_constants_text(text)
                    + page_parse.constant_tables_text(text)
                    + page_parse.define_line_constants(text))
        else:
            fragment = page_parse.article_html(raw)
            decls = page_parse.declarations(fragment, page_title=title)
            rows = (page_parse.constant_tables(fragment)
                    + page_parse.prose_constants(fragment)
                    + page_parse.syntax_constant_rows(decls)
                    + page_parse.define_line_constants(fragment, True))
        for rec in rows:
            name = rec.get("name") or ""
            value = rec.get("value")
            if not name or value in (None, ""):
                continue
            if quality_filters.is_sample_name(name):
                continue
            constants.append({
                "name": name,
                "value": value,
                "decimal": rec.get("decimal"),
                "origin": rec.get("origin") or "define",
                "headers": rec.get("headers") or [],
                "table": rec.get("table") or "",
                "row": rec.get("row") or "",
                "layer": "ce",
                "page_id": page_id,
                "source": src,
                "license": src["license"],
            })
        for d in decls or []:
            if d.get("role") != "syntax" or d.get("implementation"):
                continue
            text = d.get("text") or ""
            if not quality_filters.looks_like_c_declaration(text):
                continue
            name = d.get("name") or identifier_from_decl(
                text, d.get("kind") or "")
            if not name or quality_filters.is_sample_name(name):
                continue
            if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", name):
                continue
            declarations.append({
                "type": d.get("kind") or "function",
                "name": name,
                "declaration": text,
                "source": path,
                "page_id": page_id,
            })
    except Exception:
        return path, len(raw), [], []
    return path, len(raw), constants, declarations


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--workers", type=int, default=min(8, os.cpu_count() or 4))
    ap.add_argument("--limit", type=int, default=0)
    args = ap.parse_args()
    jobs = read_index()
    if args.limit:
        jobs = jobs[:args.limit]
    print(f"[harvest] {len(jobs):,} CE page(s), {args.workers} worker(s)",
          flush=True)
    constants = []
    declarations = []
    visits = []
    with concurrent.futures.ProcessPoolExecutor(max_workers=args.workers) as ex:
        for path, nbytes, consts, decls in ex.map(harvest_page, jobs, chunksize=32):
            visits.append((path, nbytes, len(consts), len(decls)))
            constants.extend(consts)
            declarations.extend(decls)
    # unique by (name, value, path)
    seen_c = set()
    uniq_c = []
    for rec in constants:
        key = (rec["name"], str(rec["value"]), rec["source"]["path"])
        if key in seen_c:
            continue
        seen_c.add(key)
        rec["id"] = "h" + hashlib.sha1(
            "|".join(key).encode("utf-8")).hexdigest()[:12]
        uniq_c.append(rec)
    seen_d = set()
    uniq_d = []
    for rec in declarations:
        key = (rec.get("name"), rec.get("source"))
        if key in seen_d:
            continue
        seen_d.add(key)
        uniq_d.append(rec)
    os.makedirs(KB, exist_ok=True)
    cpath = os.path.join(KB, "harvest-constants.jsonl")
    dpath = os.path.join(KB, "harvest-declarations.jsonl")
    with open(cpath, "w", encoding="utf-8") as fh:
        for rec in uniq_c:
            fh.write(json.dumps(rec, ensure_ascii=False) + "\n")
    with open(dpath, "w", encoding="utf-8") as fh:
        for rec in uniq_d:
            fh.write(json.dumps(rec, ensure_ascii=False) + "\n")
    vpath = os.path.join(KB, "harvest-visits.tsv")
    with open(vpath, "w", encoding="utf-8") as fh:
        fh.write("path\tbytes\tconstants\tdeclarations\n")
        for path, nbytes, nc, nd in visits:
            fh.write(f"{path}\t{nbytes}\t{nc}\t{nd}\n")
    missing = sum(1 for _p, b, _c, _d in visits if b == 0)
    print(f"[harvest] {len(uniq_c):,} constant row(s) -> {cpath}")
    print(f"[harvest] {len(uniq_d):,} declaration(s) -> {dpath}")
    print(f"[harvest] opened {len(visits):,} page(s) one-by-one "
          f"({missing} unreadable) -> {vpath}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
