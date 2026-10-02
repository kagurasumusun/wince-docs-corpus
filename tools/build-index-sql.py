#!/usr/bin/env python3
"""build-index-sql.py [--db PATH] [--full]

Build/refresh data/index/corpus.sqlite3 - a persistent SQL index of
every page in corpus/ so tools (and the harvester resume check) do not
have to rescan ~78k HTML files on every run.

Schema
  pages(path TEXT PRIMARY KEY, page_id TEXT, section TEXT, title TEXT,
        size INTEGER)
  names(name TEXT, page_id TEXT, kind TEXT,
        PRIMARY KEY(name, page_id, kind))
      kind: 'api'    - markdown page name (nf-createfilew.md -> CreateFileW)
            'title'  - name parsed from the page <title>
            'const'  - `NAME = value` / `#define NAME value` print
            'proto'  - C prototype printed on the page
            'struct' - typedef struct/union printed on the page
            'enum'   - typedef enum printed on the page
  meta(key TEXT PRIMARY KEY, value TEXT)
      'state' holds JSON {path: [mtime, size]} for incremental runs.

Incremental: unchanged files (mtime+size) are skipped; changed/new
files are re-extracted; files removed from disk drop their rows.
--full rebuilds from scratch.

Handles both page formats in corpus/: ``.html`` (harvested Learn pages, CHM
extractions, MSDN Library captures) and ``.md`` (the Win32 pages imported from
MicrosoftDocs, see corpus/win32/README.md).  Markdown pages get their title
from the ``title:`` front-matter field and their API name from the ``nf-`` /
``ns-`` / ... file-name prefix instead of the HTML print patterns.

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
CORPUS = os.path.join(ROOT, "corpus")

TITLE = re.compile(r"<title>([^<]*)", re.I)
# "CeGetDeviceId Function (Ceutil.h)", "NAME (Windows CE 5.0)"
TITLENAME = re.compile(
    r"^([A-Za-z_]\w+)\s*(?:\((?:Windows|RAPI)\b|\b(?:Function|Structure|"
    r"Enumeration|Macro|Constant|Notification|Message|Union|Callback)\b)")
BARE_NAME = re.compile(r"^[A-Za-z_]\w{1,60}$")
# "CreateFile", "BM_CLICK", "LINEINITINFO", "listview_setitem" are API names;
# single capitalised words ("Introduction", "Terms") are section headings.
CAMEL_NAME = re.compile(r"^[A-Za-z]+[A-Z_]\w*$")
ALL_CAPS_NAME = re.compile(r"^[A-Z][A-Z0-9_]{2,}$")
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


MD_TITLE = re.compile(r"^title:\s*(.+?)\s*$", re.M)
MD_NAME = re.compile(r"^(?:nf|ns|ne|nc|ni|nn|nl|na)-[^-]+-(.+)$")


def extract_markdown(path):
    """Return (title, [(name, kind), ...]) for one markdown page."""
    try:
        head = open(path, encoding="utf-8", errors="replace").read(4000)
    except OSError:
        return "", []
    match = MD_TITLE.search(head)
    title = match.group(1).strip() if match else ""
    rows = []
    # "CreateFileW function (fileapi.h)" -> CreateFileW
    tn = re.match(r"([A-Za-z_]\w*)\s+(?:function|structure|enumeration|"
                  r"union|macro|interface|callback|class|method)\b", title)
    if tn:
        rows.append((tn.group(1), "api"))
    else:
        stem = os.path.splitext(os.path.basename(path))[0]
        name = MD_NAME.match(stem)
        if name:
            rows.append((name.group(1), "api"))
    return title, rows


def symbol_title(h, name):
    """True when a page titled with a bare word really documents that name.

    Multimedia Viewer topics are titled with the bare API name
    ("AddFontResource", "BM_CLICK", "hostent"), but section headings are bare
    words too, so the page must also write the name like a symbol: a signature
    ("name("), a typedef ("} name"), or inside a <pre> block.
    """
    if ALL_CAPS_NAME.match(name) or CAMEL_NAME.match(name):
        return True
    body = re.sub(r"<head>.*?</head>", "", strip_scripts(h), flags=re.S | re.I)
    body = re.sub(r"<h1[^>]*>.*?</h1>", "", body, flags=re.S | re.I)
    pre = html.unescape(re.sub(r"<[^>]+>", " ", " ".join(
        re.findall(r"<pre[^>]*>(.*?)</pre>", body, flags=re.S))))
    flat = html.unescape(re.sub(r"<[^>]+>", " ", body))
    esc = re.escape(name)
    return bool(
        len(re.findall(r"\b" + esc + r"\b", flat)) >= 2
        or re.search(r"\b" + esc + r"\s*\(", flat)
        or re.search(r"}\s*" + esc + r"\b", flat)
        or re.search(r"\btypedef\b[^;]{0,200}\b" + esc + r"\b", flat)
        or re.search(r"\b" + esc + r"\b", pre))


def extract(path, page_id):
    """Return (title, [(name, kind), ...]) for one page file."""
    if path.endswith(".md"):
        return extract_markdown(path)
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
    elif BARE_NAME.match(title) and symbol_title(raw, title):
        rows.append((title, "title"))
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
      path TEXT PRIMARY KEY, page_id TEXT, section TEXT,
      title TEXT, size INTEGER);
    CREATE INDEX IF NOT EXISTS idx_pages_page_id ON pages(page_id);
    CREATE TABLE IF NOT EXISTS names(
      name TEXT, page_id TEXT, kind TEXT,
      PRIMARY KEY(name, page_id, kind));
    CREATE INDEX IF NOT EXISTS idx_names_name ON names(name);
    CREATE TABLE IF NOT EXISTS meta(key TEXT PRIMARY KEY, value TEXT);
    """)
    state = {}
    state_json = None
    if args.full:
        # --full rebuilds from scratch: drop any rows left over from a
        # previous layout of the corpus (paths and sections change when
        # the tree is reorganised).
        con.executescript("DELETE FROM pages; DELETE FROM names; "
                          "DELETE FROM meta;")
    else:
        row = con.execute(
            "SELECT value FROM meta WHERE key='state'").fetchone()
        if row:
            state = json.loads(row[0])
            state_json = row[0]
    files = sorted(
        f for pat in ("*.html", "*.md")
        for f in glob.glob(os.path.join(CORPUS, "**", pat), recursive=True)
        if os.path.basename(f) not in ("README.md", "PROVENANCE.md"))
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
        section = os.path.dirname(os.path.relpath(f, CORPUS)) \
            .replace(os.sep, "/")
        tx.execute(
            "INSERT OR REPLACE INTO pages VALUES(?,?,?,?,?)",
            (rel, page_id, section, title, st.st_size))
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
            tx.execute("DELETE FROM pages WHERE path=?", (rel,))
            del state[rel]
            removed += 1
    new_state_json = json.dumps(state)
    # Only touch the DB when something actually changed, so that a no-op
    # incremental run leaves the committed file byte-identical.
    if new_state_json != state_json:
        tx.execute("INSERT OR REPLACE INTO meta VALUES('state',?)",
                   (new_state_json,))
    con.commit()
    npages = con.execute("SELECT COUNT(*) FROM pages").fetchone()[0]
    nnames = con.execute("SELECT COUNT(*) FROM names").fetchone()[0]
    print(f"[index-sql] files={len(files)} updated={changed} "
          f"removed={removed} pages={npages} name-rows={nnames}")
    con.close()


if __name__ == "__main__":
    sys.exit(main())
