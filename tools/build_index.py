#!/usr/bin/env python3
"""build_index.py -- regenerate derived indexes from corpus/.

  meta/index/INDEX.tsv     id <TAB> section <TAB> path <TAB> title    (tracked in git)
  --sqlite PATH            full-text-ish name index (pages/names tables); NOT tracked in git,
                           published as a GitHub Release asset by .github/workflows/index.yml

Runs in parallel (all CPU cores). Needs a full checkout of corpus/.
"""
import argparse
import html
import json
import multiprocessing as mp
import os
import re
import sqlite3
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common  # noqa: E402
ROOT = common.ROOT

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




def section_of(rel):
    p = rel.split("/")
    if p[1] == "learn":
        return p[2]
    if p[1] == "wayback":
        return "wayback-" + p[2]
    if p[1] == "chm-extracted":
        return "chm-" + p[2]
    return "/".join(p[1:3])


def page_id_of(rel):
    base = os.path.basename(rel)[:-5]
    i = base.find("(v=")
    return base if i < 0 else base[:i] + "|" + base[i + 3:-1]


def work(rel):
    path = os.path.join(ROOT, rel)
    title, rows = extract(path, page_id_of(rel))
    try:
        size = os.path.getsize(path)
    except OSError:
        size = 0
    return rel, title, rows, size


def catalog_titles():
    t = {}
    d = common.abspath("meta/catalogs")
    for fn in sorted(os.listdir(d)):
        with open(os.path.join(d, fn), encoding="utf-8", errors="replace") as f:
            for line in f:
                m = re.match(r"([A-Za-z0-9_]+)(?:\(v=[a-z0-9.]+\))?\t(.*)$", line.rstrip("\n"))
                if m:
                    t.setdefault(m.group(1), m.group(2))
    return t


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sqlite", default="")
    ap.add_argument("--tsv", default=common.abspath("meta/index/INDEX.tsv"))
    a = ap.parse_args()
    files = sorted(p for p in common.list_tracked(common.LEARN_DIR, common.WAYBACK_DIR, common.CHM_DIR)
                   if p.endswith(".html"))
    cats = catalog_titles()
    con = None
    if a.sqlite:
        if os.path.exists(a.sqlite):
            os.remove(a.sqlite)
        con = sqlite3.connect(a.sqlite)
        con.executescript("""
        PRAGMA page_size=4096;
        CREATE TABLE pages(page_id TEXT, section TEXT, path TEXT PRIMARY KEY, title TEXT, size INTEGER);
        CREATE TABLE names(name TEXT, page_id TEXT, kind TEXT, PRIMARY KEY(name, page_id, kind));
        """)
    n = 0
    with mp.Pool() as pool, open(a.tsv, "w", encoding="utf-8") as out:
        out.write("# id\tbook\tpath\ttitle\n")
        for rel, title, rows, size in pool.imap(work, files, chunksize=64):
            pid = os.path.basename(rel)[:-5]
            t = common.clean_title(title) or cats.get(pid.split("(v=")[0], "")
            out.write("\t".join(x.replace("\t", " ") for x in (pid, section_of(rel), rel, t)) + "\n")
            if con:
                con.execute("INSERT OR REPLACE INTO pages VALUES(?,?,?,?,?)",
                            (page_id_of(rel), section_of(rel), rel, t, size))
                con.executemany("INSERT OR IGNORE INTO names VALUES(?,?,?)",
                                [(nm, page_id_of(rel), k) for nm, k in rows])
            n += 1
    if con:
        con.execute("CREATE INDEX idx_names_name ON names(name)")
        con.commit()
        con.execute("VACUUM")
        con.close()
    print(f"[index] {n:,} pages -> {a.tsv}" + (f" + {a.sqlite}" if a.sqlite else ""))


if __name__ == "__main__":
    main()
