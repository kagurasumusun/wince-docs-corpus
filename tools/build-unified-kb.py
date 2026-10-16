#!/usr/bin/env python3
"""tools/build-unified-kb.py -- fold knowledge/kb into knowledge/unified/.

The quote store (entities / declarations / constants jsonl.gz) is left
alone.  This writes a small, grep-friendly consumer view:

    knowledge/unified/catalog.json        inventory + counts
    knowledge/unified/constants.jsonl     one name, one CE-preferred value
    knowledge/unified/declarations.jsonl  one name, one C declaration
    knowledge/unified/macros.jsonl        leftover / function-like #define
    knowledge/unified/headers.jsonl       header -> names
    knowledge/unified/modules.jsonl       library/dll -> export names
    knowledge/unified/names.tsv           lookup table

    python3 tools/build-unified-kb.py
    python3 tools/build-kb.py             # calls this after a full rebuild

Clean-room: reads knowledge/ only.  Does not open corpus/.
"""

from __future__ import annotations

import collections
import csv
import datetime
import gzip
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import header_map  # noqa: E402
import kb_unify  # noqa: E402
import quality_filters  # noqa: E402

KB = os.path.join(ROOT, "knowledge", "kb")
UNIFIED = os.path.join(ROOT, "knowledge", "unified")

ENUM_MEMBER = re.compile(
    r"\b([A-Z][A-Z0-9_]{2,})\s*=\s*(0x[0-9A-Fa-f]+|-?\d+)[uUlL]*"
)


def open_jsonl(path):
    if not os.path.exists(path):
        alt = path[:-3] if path.endswith(".gz") else path + ".gz"
        path = alt if os.path.exists(alt) else path
    if not os.path.exists(path):
        return
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            line = line.strip()
            if line:
                yield json.loads(line)


def load_tsv(path):
    if not os.path.exists(path):
        return []
    with open(path, encoding="utf-8") as fh:
        return list(csv.DictReader(fh, delimiter="\t"))


def write_jsonl(path, rows):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as fh:
        for row in rows:
            fh.write(json.dumps(row, ensure_ascii=False, separators=(",", ":"))
                     + "\n")


def write_json(path, obj):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(obj, fh, ensure_ascii=False, indent=2)
        fh.write("\n")


def entity_layer_hint(entity):
    layers = entity.get("layers") or []
    if "ce" in layers:
        return "ce"
    if "win32" in layers:
        return "win32"
    return (layers[0] if layers else "ce")


def collect_constant_records():
    """name -> [raw constant dicts], including extra #define / enum members."""
    by_name = collections.defaultdict(list)
    for rec in list(open_jsonl(os.path.join(KB, "constants.jsonl.gz"))) + list(
            open_jsonl(os.path.join(KB, "harvest-constants.jsonl"))):
        name = rec.get("name") or ""
        if not name:
            continue
        rec = dict(rec)
        rec["layer"] = rec.get("layer") or (rec.get("source") or {}).get("layer")
        by_name[name].append(rec)

    for row in load_tsv(os.path.join(KB, "extra-defines.tsv")):
        name = row.get("name") or ""
        value = (row.get("value") or "").strip()
        if not name or not value:
            continue
        if quality_filters.is_sample_source(row.get("source") or ""):
            continue
        if quality_filters.is_sample_name(name):
            continue
        by_name[name].append({
            "name": name,
            "value": value,
            "layer": "ce",
            "origin": "extra-define",
            "headers": [],
            "source": {"path": row.get("source") or "", "layer": "ce",
                       "set": "", "title": "", "page_id": ""},
            "row": row.get("definition") or "",
        })

    extra_decl = os.path.join(KB, "extra-declarations.jsonl")
    if os.path.exists(extra_decl):
        with open(extra_decl, encoding="utf-8") as fh:
            for line in fh:
                rec = json.loads(line)
                text = rec.get("declaration") or ""
                if rec.get("type") not in ("enum", "struct"):
                    continue
                if quality_filters.is_sample_source(rec.get("source") or ""):
                    continue
                for match in ENUM_MEMBER.finditer(text):
                    name, value = match.group(1), match.group(2)
                    by_name[name].append({
                        "name": name,
                        "value": value,
                        "layer": "ce",
                        "origin": "extra-enum",
                        "headers": [],
                        "source": {"path": rec.get("source") or "",
                                   "layer": "ce", "set": "",
                                   "title": "", "page_id": ""},
                        "row": match.group(0),
                    })
    return by_name


def load_resolved():
    out = {}
    for row in load_tsv(os.path.join(KB, "constant-conflicts.tsv")):
        name = row.get("name") or ""
        value = row.get("resolved_value") or ""
        if name and value:
            out[name] = value
    return out


def load_constant_links():
    out = collections.defaultdict(list)
    for row in load_tsv(os.path.join(KB, "constant-headers.tsv")):
        name = row.get("name") or ""
        header = row.get("header") or ""
        if name and header:
            out[name].append(header)
    return out


def load_heuristic():
    out = {}
    for row in load_tsv(os.path.join(KB, "heuristic-headers.tsv")):
        if row.get("name") and row.get("header"):
            out[row["name"]] = row["header"]
    return out


def build_constants():
    resolved = load_resolved()
    links = load_constant_links()
    heuristic = load_heuristic()
    rows = []
    discarded_n = 0
    for name, records in sorted(collect_constant_records().items()):
        if quality_filters.is_language_runtime_constant(name):
            continue
        if quality_filters.is_sample_name(name):
            continue
        value, layer, origin, discarded = kb_unify.choose_constant_value(
            records, resolved.get(name))
        discarded_n += len(discarded)
        if not value:
            continue
        header_bits = []
        for rec in records:
            header_bits.extend(rec.get("headers") or [])
        header_bits.extend(links.get(name) or [])
        if heuristic.get(name):
            header_bits.append(heuristic[name])
        header = kb_unify.choose_header(name, header_bits)
        src = None
        for rec in records:
            if str(rec.get("value")) == str(value) and rec.get("source"):
                src = rec["source"]
                if rec.get("layer") == "ce" or (
                        isinstance(src, dict) and src.get("layer") == "ce"):
                    break
        if isinstance(src, dict):
            source = src
        else:
            source = {"path": "", "layer": layer or "ce", "set": "",
                      "title": "", "page_id": ""}
        rows.append({
            "name": name,
            "value": value,
            "header": header or "",
            "layer": layer or "ce",
            "origin": origin or "table",
            "win32_fallback": layer == "win32",
            "discarded": discarded,
            "source": source,
        })
    return rows, discarded_n


def best_decl_text(entity, decl_by_id):
    ids = list(entity.get("syntax_declarations") or []) or list(
        entity.get("declarations") or [])
    ce = []
    win32 = []
    for did in ids:
        rec = decl_by_id.get(did)
        if not rec:
            continue
        text = rec.get("text") or ""
        if rec.get("implementation") or rec.get("role") == "example":
            continue
        if not quality_filters.looks_like_c_declaration(text):
            continue
        if rec.get("layer") == "ce":
            ce.append(rec)
        elif rec.get("layer") == "win32":
            win32.append(rec)
    pool = ce or win32
    if not pool:
        return None, None
    pool.sort(key=lambda r: (
        0 if (r.get("spacing") or "") != "collapsed" else 1,
        -(len(r.get("text") or "")),
        (r.get("source") or {}).get("path") or "",
    ))
    rec = pool[0]
    return rec, "ce" if rec.get("layer") == "ce" else "win32-reference"


def build_declarations(entities, extra_decls):
    decl_by_id = {d["id"]: d for d in open_jsonl(
        os.path.join(KB, "declarations.jsonl.gz")) if d.get("id")}
    extra_by_name = {}
    for rec in extra_decls:
        name = rec.get("name") or ""
        if not name or name in extra_by_name:
            continue
        cleaned = quality_filters.sanitize_declaration(
            rec.get("declaration") or "", name, rec.get("type") or "")
        if not cleaned:
            continue
        extra_by_name[name] = {**rec, "declaration": cleaned}

    heuristic = load_heuristic()
    rows = []
    seen = set()
    for entity in entities:
        name = entity.get("name") or ""
        if not name or name in seen:
            continue
        rec, mark = best_decl_text(entity, decl_by_id)
        text = (rec.get("text") if rec else "") or ""
        if not text and name in extra_by_name:
            text = extra_by_name[name]["declaration"]
            rec = None
            mark = "extra"
        if not text:
            continue
        headers = list(entity.get("headers") or [])
        if heuristic.get(name):
            headers.append(heuristic[name])
        header = kb_unify.choose_header(
            name, headers, entity.get("kinds") or [])
        if not header:
            header = header_map.header_for_entity(
                name, entity.get("kinds") or []) or ""
        libs = (entity.get("libraries") or []) + (entity.get("dlls") or [])
        rows.append({
            "name": name,
            "kind": (entity.get("kinds") or ["?"])[0],
            "header": header or "",
            "libraries": libs,
            "text": text,
            "layer": (rec or {}).get("layer") or "ce",
            "mark": mark or "",
            "surface": entity.get("surface") or "",
            "source": (rec or {}).get("source") or {
                "path": extra_by_name.get(name, {}).get("source") or "",
                "layer": "ce",
            },
        })
        seen.add(name)

    for name, rec in extra_by_name.items():
        if name in seen:
            continue
        if quality_filters.is_sample_name(name):
            continue
        header = kb_unify.choose_header(name, [], [rec.get("type") or ""]) or ""
        rows.append({
            "name": name,
            "kind": rec.get("type") or "function",
            "header": header,
            "libraries": [],
            "text": rec["declaration"],
            "layer": "ce",
            "mark": "extra",
            "surface": "ce-only",
            "source": {"path": rec.get("source") or "", "layer": "ce"},
        })
        seen.add(name)
    rows.sort(key=lambda r: r["name"].lower())
    return rows


def build_macros(constant_names):
    rows = []
    for row in load_tsv(os.path.join(KB, "extra-defines.tsv")):
        name = row.get("name") or ""
        if not name or name in constant_names:
            continue
        if quality_filters.is_sample_source(row.get("source") or ""):
            continue
        best = quality_filters.pick_best_define([row])
        if not best:
            continue
        defn = best.get("definition") or ""
        if defn.rstrip().endswith("\\") or "</" in defn or "<" in defn:
            continue
        header = header_map.header_for_entity(name, ["macro"]) or ""
        if name.startswith(("IDC_", "IDI_")) and name not in header_map.EXACT_TO_HEADER:
            header = ""
        rows.append({
            "name": name,
            "type": best.get("type") or "object-like",
            "args": best.get("args") or "",
            "value": best.get("value") or "",
            "definition": best.get("definition") or "",
            "header": header,
            "source": best.get("source") or "",
        })
    rows.sort(key=lambda r: r["name"].lower())
    return rows


def build_headers(constants, declarations, macros):
    buckets = collections.defaultdict(lambda: {
        "constants": [], "declarations": [], "macros": []})
    for rec in constants:
        if rec.get("header") and rec.get("value"):
            buckets[rec["header"]]["constants"].append(rec["name"])
    for rec in declarations:
        if rec.get("header"):
            buckets[rec["header"]]["declarations"].append(rec["name"])
    for rec in macros:
        if rec.get("header"):
            buckets[rec["header"]]["macros"].append(rec["name"])
    rows = []
    for header in sorted(buckets, key=str.lower):
        b = buckets[header]
        rows.append({
            "header": header,
            "constants": b["constants"],
            "declarations": b["declarations"],
            "macros": b["macros"],
            "n_constants": len(b["constants"]),
            "n_declarations": len(b["declarations"]),
            "n_macros": len(b["macros"]),
        })
    return rows


def build_modules(entities):
    buckets = collections.defaultdict(lambda: {"names": [], "kind": ""})
    for entity in entities:
        kinds = entity.get("kinds") or []
        if not any(k in ("function", "callback") for k in kinds):
            continue
        name = entity.get("name") or ""
        files = list(entity.get("libraries") or []) + list(entity.get("dlls") or [])
        for raw in files:
            match = re.search(
                r"([\w.+-]+)\.(lib|dll|drv|sys)\b", raw or "", re.I)
            if not match:
                continue
            stem = match.group(1)
            ext = match.group(2).lower()
            key = stem.lower()
            bucket = buckets[key]
            bucket["kind"] = ext
            bucket.setdefault("printed", stem)
            if name not in bucket["names"]:
                bucket["names"].append(name)
    rows = []
    for key in sorted(buckets):
        b = buckets[key]
        rows.append({
            "module": b.get("printed") or key,
            "kind": b["kind"],
            "exports": b["names"],
            "n_exports": len(b["names"]),
        })
    return rows


def build():
    os.makedirs(UNIFIED, exist_ok=True)
    entities = list(open_jsonl(os.path.join(KB, "entities.jsonl.gz")))
    extra_decls = []
    extra_path = os.path.join(KB, "extra-declarations.jsonl")
    if os.path.exists(extra_path):
        with open(extra_path, encoding="utf-8") as fh:
            extra_decls = [json.loads(l) for l in fh if l.strip()]
    harvest_decl = os.path.join(KB, "harvest-declarations.jsonl")
    if os.path.exists(harvest_decl):
        with open(harvest_decl, encoding="utf-8") as fh:
            extra_decls.extend(json.loads(l) for l in fh if l.strip())

    constants, discarded_n = build_constants()
    declarations = build_declarations(entities, extra_decls)
    const_names = {r["name"] for r in constants}
    macros = build_macros(const_names)
    headers = build_headers(constants, declarations, macros)
    modules = build_modules(entities)

    write_jsonl(os.path.join(UNIFIED, "constants.jsonl"), constants)
    write_jsonl(os.path.join(UNIFIED, "declarations.jsonl"), declarations)
    write_jsonl(os.path.join(UNIFIED, "macros.jsonl"), macros)
    write_jsonl(os.path.join(UNIFIED, "headers.jsonl"), headers)
    write_jsonl(os.path.join(UNIFIED, "modules.jsonl"), modules)

    names_path = os.path.join(UNIFIED, "names.tsv")
    with open(names_path, "w", encoding="utf-8") as fh:
        fh.write("name\tkind\theader\tmodule\tvalue\torigin\n")
        seen = set()
        for rec in constants:
            fh.write("\t".join((
                rec["name"], "constant", rec.get("header") or "",
                "", rec.get("value") or "", rec.get("origin") or "")) + "\n")
            seen.add(rec["name"])
        for rec in macros:
            if rec["name"] in seen:
                continue
            fh.write("\t".join((
                rec["name"], "macro", rec.get("header") or "",
                "", rec.get("value") or "", rec.get("type") or "")) + "\n")
            seen.add(rec["name"])
        for rec in declarations:
            if rec["name"] in seen:
                continue
            mods = ",".join(rec.get("libraries") or [])
            fh.write("\t".join((
                rec["name"], rec.get("kind") or "", rec.get("header") or "",
                mods, "", rec.get("mark") or "")) + "\n")

    catalog = {
        "schema": "wince-unified-kb/v1",
        "generated": datetime.date.today().isoformat(),
        "source": "knowledge/kb (quote store) + extra-defines/declarations",
        "counts": {
            "constants": len(constants),
            "constants_with_header": sum(1 for r in constants if r.get("header")),
            "constants_win32_fallback": sum(1 for r in constants if r.get("win32_fallback")),
            "discarded_values": discarded_n,
            "declarations": len(declarations),
            "declarations_with_header": sum(1 for r in declarations if r.get("header")),
            "macros": len(macros),
            "headers": len(headers),
            "modules": len(modules),
            "entities": len(entities),
        },
        "files": [
            "catalog.json", "constants.jsonl", "declarations.jsonl",
            "macros.jsonl", "headers.jsonl", "modules.jsonl", "names.tsv",
        ],
        "rules": [
            "Every value is a number or expression a page printed.",
            "CE-layer rows outrank Win32-reference rows.",
            "Charset/code-page correspondence columns are not constant values.",
            "One header per name; header_map beats a weak win32-reference.",
            "The quote store under knowledge/kb/ is unchanged.",
        ],
    }
    write_json(os.path.join(UNIFIED, "catalog.json"), catalog)

    readme = os.path.join(UNIFIED, "README.md")
    with open(readme, "w", encoding="utf-8") as fh:
        fh.write("# `knowledge/unified/` — consumer view of the knowledge base\n\n")
        fh.write("One identifier, one chosen Windows CE fact.  The quote store\n")
        fh.write("(`knowledge/kb/*.jsonl.gz`) is the evidence; this tree is what\n")
        fh.write("`tools/gen-include-def.py` files into include/def fragments.\n\n")
        fh.write("| file | what |\n|------|------|\n")
        fh.write("| `constants.jsonl` | numbered `#define` candidates (CE value preferred) |\n")
        fh.write("| `declarations.jsonl` | one C declaration per name |\n")
        fh.write("| `macros.jsonl` | function-like / leftover `#define` |\n")
        fh.write("| `headers.jsonl` | header → names |\n")
        fh.write("| `modules.jsonl` | `.lib`/`.dll` → export names |\n")
        fh.write("| `names.tsv` | grep-friendly lookup |\n")
        fh.write("| `catalog.json` | counts |\n\n")
        fh.write("Rebuild with `python3 tools/build-unified-kb.py`.\n")
        counts = catalog["counts"]
        fh.write("\n## Counts\n\n")
        for k, v in counts.items():
            fh.write(f"- **{k}**: {v:,}\n")
    return catalog


def main():
    catalog = build()
    c = catalog["counts"]
    print("unified kb:",
          f"{c['constants']:,} constants",
          f"({c['constants_with_header']:,} with header),",
          f"{c['declarations']:,} declarations,",
          f"{c['macros']:,} macros,",
          f"{c['headers']:,} headers,",
          f"{c['modules']:,} modules",
          f"-> {os.path.relpath(UNIFIED, ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
