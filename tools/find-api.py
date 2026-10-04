#!/usr/bin/env python3
"""tools/find-api.py -- look up an API name across the whole corpus.

Answers the question the corpus exists for: *where* is this name documented —
in Windows CE, in Win32, or both?

    $ python3 tools/find-api.py CreateFile
    CreateFile  [win32-shared: windows-ce-5.0;windows-embedded-ce-6.0]
      ce        aa517318(v=msdn.10)   learn/windows-ce-5.0
                CreateFile (Windows CE 5.0)
                corpus/learn/windows-ce-5.0/aa517318(v=msdn.10).html
      ce        _wcesdk_Win32_CreateFile   chm/windows-ce-3.0
                CreateFile
                corpus/chm/windows-ce-3.0/_wcesdk_Win32_CreateFile.html
      win32     nf-fileapi-createfilew   win32/api/fileapi
                CreateFileW function
                corpus/win32/api/fileapi/nf-fileapi-createfilew.md

Search modes:

    python3 tools/find-api.py NAME      exact API name (case-insensitive)
    python3 tools/find-api.py --grep STR  substring match on API names
    python3 tools/find-api.py --prefix Cr   prefix match (min 3 characters)

Options:

    --ce / --win32        restrict to one side of the corpus
    --shared              only names from data/reports/win32-shared.tsv
    --limit N             max names to print (default 20)
    --json                machine-readable output
    --db PATH             SQL index to use (default data/index/corpus.sqlite3)

Uses the SQL index built by ``tools/build-index-sql.py``; falls back to
``data/index/INDEX.tsv`` when the DB is missing.
"""
import argparse
import collections
import gzip
import json
import os
import sqlite3
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB = os.path.join(ROOT, "data", "index", "corpus.sqlite3")
TSV = os.path.join(ROOT, "data", "index", "INDEX.tsv")
SHARED = os.path.join(ROOT, "data", "reports", "win32-shared.tsv")
KB = os.path.join(ROOT, "knowledge", "kb", "entities.jsonl.gz")


def load_kb():
    """name -> the knowledge-base record for it (None when kb/ is not built)."""
    entities = {}
    path = KB if os.path.exists(KB) else KB[:-3]
    if not os.path.exists(path):
        return entities
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            try:
                record = json.loads(line)
            except ValueError:
                continue
            entities[record.get("id", "")] = record
    return entities


def kb_line(record):
    """One line summarizing what the knowledge base has for an entity."""
    if not record:
        return None
    parts = [f"kb: {record.get('doc_role', '?')}"]
    if record.get("surface"):
        # where the name sits in the Windows CE / Win32 split; Windows CE is
        # the CE-specific surface plus the shared part, not all of Win32
        parts.append(f"surface: {record['surface']}")
    if record.get("kinds"):
        parts.append("/".join(record["kinds"]))
    if record.get("syntax_declarations"):
        parts.append(f"{len(record['syntax_declarations'])} declaration(s)")
    if record.get("headers"):
        parts.append("header: " + ", ".join(record["headers"][:3]))
    if record.get("libraries"):
        parts.append("lib: " + ", ".join(record["libraries"][:3]))
    if record.get("ce_sets"):
        parts.append("sets: " + ",".join(record["ce_sets"][:3]))
    if record.get("variants_of"):
        variant = record["variants_of"]
        parts.append(f"{variant.get('kind', '?')} spelling of "
                     f"{variant.get('name')} ({variant.get('basis')})")
    if record.get("documented_fields"):
        # the page documents the members but prints no declaration body: the
        # names and their order are the fact, offsets are not stated anywhere
        parts.append(f"{len(record['documented_fields'])} documented member(s), "
                     "no offsets")
    leads = collections.OrderedDict()
    for relation in record.get("relations", ()):
        if relation.get("type") == "ce-name-lead":
            leads.setdefault(relation["name"], []).append(relation["page"])
    for name, pages in leads.items():
        parts.append(f"CE page(s) print {name!r} ({len(pages)} page(s))")
    return "  ".join(parts)


def load_shared():
    """name -> (ce_sets, ce_page_ids, win32_pages)"""
    shared = {}
    if not os.path.exists(SHARED):
        return shared
    with open(SHARED, encoding="utf-8") as fh:
        next(fh, None)
        for line in fh:
            parts = line.rstrip("\n").split("\t")
            if len(parts) == 4:
                shared[parts[0].lower()] = parts[1:]
    return shared


def query_db(db_path, mode, needle):
    """Return rows (name, kind, page_id, section, title, path)."""
    con = sqlite3.connect(f"file:{db_path}?mode=ro", uri=True)
    where = {"exact": "lower(n.name) = ?",
             "grep": "lower(n.name) LIKE ?",
             "prefix": "lower(n.name) LIKE ?"}[mode]
    if mode == "grep":
        param = f"%{needle}%"
    elif mode == "prefix":
        param = f"{needle}%"
    else:
        param = needle
    sql = f"""
        SELECT n.name, n.kind, p.page_id, p.section, p.title, p.path
        FROM names n JOIN pages p ON p.page_id = n.page_id
        WHERE {where}
        ORDER BY n.name, p.section
    """
    rows = con.execute(sql, (param,)).fetchall()
    con.close()
    return rows


def query_tsv(mode, needle):
    """Fallback: INDEX.tsv only has ids/titles, matched loosely."""
    rows = []
    with open(TSV, encoding="utf-8") as fh:
        next(fh, None)
        for line in fh:
            parts = line.rstrip("\n").split("\t")
            if len(parts) < 4:
                continue
            page_id, section, path, title = parts
            if needle in page_id.lower() or needle in title.lower():
                rows.append((page_id, "tsv", page_id, section, title, path))
    return rows


def pretty_id(page_id):
    """aa517318|msdn.10 -> aa517318(v=msdn.10)"""
    if "|" in page_id:
        stem, ver = page_id.split("|", 1)
        return f"{stem}(v={ver})"
    return page_id


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("name", nargs="?")
    ap.add_argument("--grep")
    ap.add_argument("--prefix")
    ap.add_argument("--ce", action="store_true", help="only CE trees")
    ap.add_argument("--win32", action="store_true", help="only corpus/win32")
    ap.add_argument("--shared", action="store_true",
                    help="only names in data/reports/win32-shared.tsv")
    ap.add_argument("--limit", type=int, default=20)
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--db", default=DB)
    args = ap.parse_args()

    if not (args.name or args.grep or args.prefix):
        ap.error("give a NAME, --grep or --prefix")

    needle = (args.name or args.grep or args.prefix).lower()
    mode = "exact" if args.name else ("grep" if args.grep else "prefix")
    if mode == "prefix" and len(needle) < 3:
        ap.error("--prefix needs at least 3 characters")

    shared = load_shared()
    if os.path.exists(args.db):
        rows = query_db(args.db, mode, needle)
    elif os.path.exists(TSV):
        rows = query_tsv(mode, needle)
    else:
        sys.exit("no index found: run tools/build-index-sql.py first")

    def is_ce(section):
        return not section.startswith("win32/")

    filtered = []
    for row in rows:
        name, kind, page_id, section, title, path = row
        if args.ce and not is_ce(section):
            continue
        if args.win32 and is_ce(section):
            continue
        if args.shared and name.lower() not in shared:
            continue
        filtered.append(row)

    by_name = {}
    for row in filtered:
        by_name.setdefault(row[0], []).append(row)

    # Names that are catalogued on the CE side but whose Win32 page is filed
    # under an A/W variant (CreateFile -> CreateFileW) come from the shared
    # map instead of the name join.
    if not args.ce and not args.grep:
        for name in list(by_name):
            sh = shared.get(name.lower())
            if not sh or not sh[2]:
                continue
            have = {r[5] for r in by_name[name]}
            for path in sh[2].split(";"):
                if path and path not in have:
                    by_name[name].append(
                        (name, "shared", os.path.splitext(
                            os.path.basename(path))[0],
                         os.path.dirname(path).replace("corpus/", ""),
                         "", path))

    names = list(by_name)[:args.limit]
    if args.json:
        out = []
        for name in names:
            out.append({
                "name": name,
                "shared": shared.get(name.lower()),
                "pages": [
                    {"kind": kind, "page_id": page_id, "section": section,
                     "title": title, "path": path}
                    for _n, kind, page_id, section, title, path in by_name[name]
                ],
            })
        print(json.dumps(out, ensure_ascii=False, indent=2))
        return 0

    kb = load_kb()
    for name in names:
        sh = shared.get(name.lower())
        print(f"{name}" + (f"  [win32-shared: {sh[0]}]" if sh else ""))
        line = kb_line(kb.get(name.lower()))
        if line:
            print(f"  {line}")
        for _n, kind, page_id, section, title, path in by_name[name]:
            side = "ce   " if is_ce(section) else "win32"
            print(f"  {side} {kind:5s} {pretty_id(page_id):32s} {section}")
            if title:
                print(f"        {title}")
            print(f"        {path}")
    if len(by_name) > len(names):
        print(f"... and {len(by_name) - len(names)} more names "
              f"(raise --limit)")
    total_pages = sum(len(v) for v in by_name.values())
    print(f"\n{len(by_name)} name(s), {total_pages} page(s)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
