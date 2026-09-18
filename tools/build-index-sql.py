#!/usr/bin/env python3
"""build-index-sql.py [--db PATH] [--full]

Build/refresh data/index/corpus.sqlite3 - a persistent SQL index of
every harvested page so tools (and the harvester resume check) do not
have to rescan ~87k HTML files on every run.

Schema
  pages(page_id TEXT PRIMARY KEY, section TEXT, path TEXT, title TEXT,
        size INTEGER)
  names(name TEXT, page_id TEXT, kind TEXT,
        PRIMARY KEY(name, page_id, kind))
      kind: 'title'  - name parsed from the page <title>
            'const'  - `NAME = value` / `#define NAME value` print
            'proto'  - C prototype printed on the page
            'struct' - typedef struct/union printed on the page
            'enum'   - typedef enum printed on the page
  meta(key TEXT PRIMARY KEY, value TEXT)
      'state' holds JSON {path: [mtime, size]} for incremental runs.

Incremental: unchanged files (mtime+size) are skipped; changed/new
files are re-extracted; files removed from disk drop their rows.
--full rebuilds from scratch.

Writes are wrapped in a single transaction; the DB is safe to commit
to git (WAL off, page_size 4096).
"""
import argparse
import glob
import html
import json
import os
import re
import sqlite3
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

TITLE = re.compile(r"<title>([^<]*)", re.I)
# "CeGetDeviceId Function (Ceutil.h)", "NAME (Windows CE 5.0)"
TITLENAME = re.compile(
    r"^([A-Za-z_]\w+)\s*(?:\((?:Windows|RAPI)\b|\b(?:Function|Structure|"
    r"Enumeration|Macro|Constant|Notification|Message|Union|Callback)\b)")
CONST_DEF = re.compile(r"#?define\s+([A-Za-z_]\w+)\s+(\S.*?)$")
CONST_EQ = re.compile(
    r"([A-Za-z_]\w*)\s*=\s*(\(?\s*(?:0[xX][0-9a-fA-F]+|\d+)\s*\)?)\s*,?\s*$")
PROTO = re.compile(
    r"\b([A-Za-z_]\w[\w \*]*?[\* ])([A-Za-z_]\w+)\s*\(([^;{}()]{0,600})\)\s*;")
STRUCT = re.compile(
    r"typedef\s+(?:struct|union)\s*([A-Za-z_]\w*)?\s*\{")
ENUM = re.compile(r"typedef\s+enum\s*([A-Za-z_]\w*)?\s*\{")
CLOSE_TAG = re.compile(r"\}\s*([A-Za-z_][\w, \*]*?)\s*;")


def strip_scripts(h):
    return re.sub(r"<script.*?</script>", "", h, flags=re.S)


def extract(path, page_id):
    """Return (title, [(name, kind), ...]) for one HTML file."""
    try:
        raw = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return "", []
    head = raw[:4000]
    m = TITLE.search(head)
    title = m.group(1).strip() if m else ""
    rows = []
    tn = TITLENAME.match(title)
    if tn and not re.fullmatch(r"[A-Z][a-z]+", tn.group(1)):
        rows.append((tn.group(1), "title"))
    h = strip_scripts(raw)
    # pre blocks + table cells: the two print carriers used by the
    # harvested MSDN/Learn trees
    texts = [html.unescape(re.sub(r"<[^>]+>", "", b))
             for b in re.findall(r"<pre[^>]*>(.*?)</pre>", h, re.S)]
    texts += [html.unescape(re.sub(r"<[^>]+>", "", t))
              for t in re.findall(r"<td[^>]*>(.*?)</td>", h, re.S)]
    seen = set()
    for t in texts:
        for line in t.replace("\r", "").split("\n"):
            line = line.strip()
            if not line:
                continue
            cm = CONST_DEF.match(line) or CONST_EQ.match(line)
            if cm and ("const", cm.group(1)) not in seen:
                seen.add(("const", cm.group(1)))
                rows.append((cm.group(1), "const"))
            for pm in PROTO.finditer(line):
                nm = pm.group(2)
                if ("proto", nm) not in seen and nm not in (
                        "if", "for", "while", "switch", "return", "sizeof"):
                    seen.add(("proto", nm))
                    rows.append((nm, "proto"))
    for sm in STRUCT.finditer(re.sub(r"\s+", " ", html.unescape(
            re.sub(r"<[^>]+>", " ", h)))):
        pass  # struct/enum target names are collected below
    flat = re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ", h)))
    for rx, kind in ((STRUCT, "struct"), (ENUM, "enum")):
        for sm in rx.finditer(flat):
            tail = flat[sm.end():sm.end() + 4000]
            cm = CLOSE_TAG.search(tail)
            if not cm:
                continue
            for nm in re.split(r"[,\s]+", cm.group(1)):
                nm = nm.strip(" *")
                if re.fullmatch(r"[A-Za-z_]\w*", nm or "") and \
                        (kind, nm) not in seen:
                    seen.add((kind, nm))
                    rows.append((nm, kind))
    return title, rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--db", default=os.path.join(
        ROOT, "data", "index", "corpus.sqlite3"))
    ap.add_argument("--full", action="store_true")
    args = ap.parse_args()
    os.makedirs(os.path.dirname(args.db), exist_ok=True)
    con = sqlite3.connect(args.db)
    con.execute("PRAGMA journal_mode=DELETE")
    con.execute("PRAGMA page_size=4096")
    con.executescript("""
    CREATE TABLE IF NOT EXISTS pages(
      page_id TEXT PRIMARY KEY, section TEXT, path TEXT,
      title TEXT, size INTEGER);
    CREATE TABLE IF NOT EXISTS names(
      name TEXT, page_id TEXT, kind TEXT,
      PRIMARY KEY(name, page_id, kind));
    CREATE INDEX IF NOT EXISTS idx_names_name ON names(name);
    CREATE TABLE IF NOT EXISTS meta(key TEXT PRIMARY KEY, value TEXT);
    """)
    state = {}
    if not args.full:
        row = con.execute(
            "SELECT value FROM meta WHERE key='state'").fetchone()
        if row:
            state = json.loads(row[0])
    files = sorted(glob.glob(os.path.join(ROOT, "docs", "**", "*.html"),
                             recursive=True))
    changed = removed = 0
    live = set()
    tx = con
    tx.execute("BEGIN")
    for f in files:
        try:
            st = os.stat(f)
        except OSError:
            continue
        rel = os.path.relpath(f, ROOT)
        live.add(rel)
        base = os.path.basename(f)[:-5]
        ver = base.find("(v=")
        page_id = base if ver < 0 else base[:ver] + "|" + base[ver + 3:-1]
        prev = state.get(rel)
        # size-only comparison: git checkout resets mtimes, so an
        # mtime check would force a full rebuild on every runner.
        # Harvested pages are write-once; same-size rewrites are
        # corrected by the next --full rebuild.
        if prev and prev[-1] == st.st_size:
            continue
        title, rows = extract(f, page_id)
        tx.execute("DELETE FROM names WHERE page_id=?", (page_id,))
        tx.execute(
            "INSERT OR REPLACE INTO pages VALUES(?,?,?,?,?)",
            (page_id, rel.split(os.sep)[1] + "/" + rel.split(os.sep)[2]
             if rel.count(os.sep) >= 2 else rel, rel, title, st.st_size))
        tx.executemany(
            "INSERT OR IGNORE INTO names VALUES(?,?,?)",
            [(n, page_id, k) for n, k in rows])
        state[rel] = [st.st_mtime, st.st_size]
        changed += 1
    for rel in list(state):
        if rel not in live:
            base = os.path.basename(rel)[:-5]
            ver = base.find("(v=")
            page_id = base if ver < 0 else base[:ver] + "|" + base[ver + 3:-1]
            tx.execute("DELETE FROM names WHERE page_id=?", (page_id,))
            tx.execute("DELETE FROM pages WHERE page_id=?", (page_id,))
            del state[rel]
            removed += 1
    tx.execute("INSERT OR REPLACE INTO meta VALUES('state',?)",
               (json.dumps(state),))
    con.commit()
    npages = con.execute("SELECT COUNT(*) FROM pages").fetchone()[0]
    nnames = con.execute("SELECT COUNT(*) FROM names").fetchone()[0]
    print(f"[index-sql] files={len(files)} updated={changed} "
          f"removed={removed} pages={npages} name-rows={nnames}")
    con.close()


if __name__ == "__main__":
    sys.exit(main())
