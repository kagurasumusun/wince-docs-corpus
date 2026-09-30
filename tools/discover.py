#!/usr/bin/env python3
"""discover.py -- widen the collection *scope* (builds URL queues; downloads no documents).

Commands (all driven by sources/sources.json):
  learn-toc      crawl Learn TOC JSON files -> queues/sources/learn-toc.txt + meta/catalogs/learn-<id>.tsv
  learn-links    scan harvested pages for links to not-yet-harvested Learn pages -> queues/sources/learn-links.txt
  wayback-cdx    Wayback CDX lookups for configured MSDN id ranges -> queues/sources/wayback-cdx.txt
  archive-org    archive.org search for CE/WM documentation media -> meta/harvest/archive-org-candidates.tsv
  pending        queues/pending/{learn,wayback}.txt = all source queues minus already harvested / known-404
  all            toc + cdx + archive-org + pending   (links needs a full checkout; run it explicitly)

Network access is required (GitHub Actions runner). Every source failure is reported, never fatal.
"""
import argparse
import concurrent.futures as cf
import datetime as dt
import json
import os
import re
import sys
import time
import urllib.error
import urllib.parse
import urllib.request

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common  # noqa: E402

UA = "wince-docs-corpus-discover/1.0 (personal archival index)"
REPORT = {"time": dt.datetime.now(dt.timezone.utc).isoformat(timespec="seconds"), "sources": {}}


def http_get(url, timeout=120, retries=3):
    last = None
    for i in range(retries):
        try:
            req = urllib.request.Request(url, headers={"User-Agent": UA, "Accept-Encoding": "identity"})
            with urllib.request.urlopen(req, timeout=timeout) as r:
                return r.read(), r.status
        except urllib.error.HTTPError as e:
            if e.code in (404, 410):
                return None, e.code
            last = e.code
        except Exception as e:  # noqa: BLE001
            last = str(e)[:100]
        time.sleep(3 * (i + 1))
    return None, last


def cfg():
    with open(common.abspath("sources/sources.json"), encoding="utf-8") as f:
        return json.load(f)


def write_lines(rel, lines):
    lines = sorted(set(lines))
    with open(common.abspath(rel), "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + ("\n" if lines else ""))
    return len(lines)


# ------------------------------------------------------------------ learn TOC
def walk_toc(items, base, path, out):
    for it in items or []:
        title = (it.get("toc_title") or "").strip()
        href = it.get("href")
        here = path + [title]
        if href and "(v=" in href:
            url = urllib.parse.urljoin(base, href)
            url = url.split("?")[0].split("#")[0]
            out.append((url, " :: ".join(here)))
        walk_toc(it.get("children"), base, here, out)


def cmd_learn_toc(c):
    allurls, total = [], 0
    for s in c["learn_toc"]:
        body, st = http_get(s["toc"])
        if body is None:
            REPORT["sources"][f"toc:{s['id']}"] = f"unavailable ({st})"
            print(f"[toc] {s['id']}: unavailable ({st})", flush=True)
            continue
        try:
            data = json.loads(body.decode("utf-8-sig"))
        except ValueError as e:
            REPORT["sources"][f"toc:{s['id']}"] = f"bad-json ({e})"
            continue
        out = []
        walk_toc(data.get("items", []), s["toc"], [], out)
        with open(common.abspath(f"meta/catalogs/learn-toc-{s['id']}.tsv"), "w", encoding="utf-8") as f:
            for url, path in sorted(set(out)):
                k, pid, ver = common.dest_for(url)
                f.write(f"{pid}(v={ver})\t{path}\n" if k else "")
        allurls += [u for u, _ in out]
        REPORT["sources"][f"toc:{s['id']}"] = len(set(u for u, _ in out))
        print(f"[toc] {s['id']}: {len(set(u for u, _ in out)):,} pages", flush=True)
    total = write_lines("queues/sources/learn-toc.txt", allurls)
    print(f"[toc] queue learn-toc.txt: {total:,}")


# ------------------------------------------------------------------ link closure
HREF = re.compile(r'href="([^"#]+)"')


def _scan(path):
    try:
        with open(path, encoding="utf-8", errors="replace") as f:
            return HREF.findall(f.read())
    except OSError:
        return []


def cmd_learn_links(c):
    lc = c["learn_link_crawl"]
    if not lc.get("enabled"):
        return
    prefixes = tuple(p.lower() for p in lc["url_prefixes"])
    files = [common.abspath(p) for p in common.list_tracked(common.LEARN_DIR)]
    found = set()
    with cf.ProcessPoolExecutor() as ex:
        for hrefs in ex.map(_scan, files, chunksize=200):
            for h in hrefs:
                if "(v=" not in h:
                    continue
                u = urllib.parse.urljoin("https://learn.microsoft.com/en-us/previous-versions/windows/embedded/", h)
                u = u.split("?")[0]
                if u.lower().startswith(prefixes):
                    found.add(u)
    n = write_lines("queues/sources/learn-links.txt", found)
    REPORT["sources"]["learn-links"] = n
    print(f"[links] scanned {len(files):,} pages -> {n:,} candidate URLs")


# ------------------------------------------------------------------ wayback CDX
def known_ids():
    ids = set()
    for d in ("meta/catalogs",):
        for fn in os.listdir(common.abspath(d)):
            with open(common.abspath(f"{d}/{fn}"), encoding="utf-8", errors="replace") as f:
                for line in f:
                    m = re.match(r"([A-Za-z0-9_]+)(?:\(v=[A-Za-z0-9.]+\))?\t", line)
                    if m:
                        ids.add(m.group(1).lower())
    for fn in os.listdir(common.abspath("queues/sources")):
        with open(common.abspath(f"queues/sources/{fn}"), encoding="utf-8", errors="replace") as f:
            for line in f:
                k, pid, _ = common.dest_for(line.strip())
                if k:
                    ids.add(pid)
    return ids


def cmd_wayback_cdx(c):
    wc = c["wayback_cdx"]
    if not wc.get("enabled"):
        return
    known = known_ids() if wc.get("restrict_to_known_ids") else None
    out, flag = [], "id_" if wc.get("use_id_flag") else ""
    for p in wc["prefixes"]:
        params = {"url": p["url"], "filter": ["statuscode:200", "mimetype:text/html"],
                  "collapse": "urlkey", "fl": "timestamp,original", "output": "txt"}
        if not p["url"].endswith("*"):
            params["matchType"] = "prefix"
        if wc.get("capture_not_before"):
            params["from"] = wc["capture_not_before"]
        if wc.get("capture_not_after"):
            params["to"] = wc["capture_not_after"]
        q = urllib.parse.urlencode(params, doseq=True)
        body, st = http_get("https://web.archive.org/cdx/search/cdx?" + q, timeout=300)
        if body is None:
            REPORT["sources"][f"cdx:{p['url']}"] = f"unavailable ({st})"
            print(f"[cdx] {p['url']}: unavailable ({st})", flush=True)
            time.sleep(5)
            continue
        n = 0
        for line in body.decode("utf-8", "replace").splitlines():
            try:
                ts, orig = line.split(" ", 1)
            except ValueError:
                continue
            m = re.search(r"/library/([A-Za-z0-9_.\-]+?)(?:\(v=[A-Za-z0-9.]+\))?(?:\.aspx)?$", orig.split("?")[0])
            if not m:
                continue
            pid = m.group(1).lower()
            if known is not None and pid not in known:
                continue
            u = orig.split("?")[0].replace("http://", "https://")
            if not u.endswith(".aspx") and "(v=" not in u:
                u += ".aspx"
            out.append(f"https://web.archive.org/web/{ts}{flag}/{u}")
            n += 1
        REPORT["sources"][f"cdx:{p['url']}"] = n
        print(f"[cdx] {p['url']}: {n:,} urls", flush=True)
        time.sleep(3)
    # one capture per id (keep the earliest within the window)
    best = {}
    for u in out:
        k, pid, _ = common.dest_for(u)
        if k and (pid not in best or u < best[pid]):
            best[pid] = u
    print(f"[cdx] queue wayback-cdx.txt: {write_lines('queues/sources/wayback-cdx.txt', best.values()):,}")


# ------------------------------------------------------------------ archive.org
def cmd_archive_org(c):
    ac = c["archive_org"]
    if not ac.get("enabled"):
        return
    rows = {}
    for q in ac["search_queries"]:
        url = "https://archive.org/advancedsearch.php?" + urllib.parse.urlencode(
            {"q": q, "fl[]": ["identifier", "title", "publicdate", "item_size"], "rows": 200, "output": "json"}, doseq=True)
        body, st = http_get(url)
        if body is None:
            REPORT["sources"][f"archive-org:{q}"] = f"unavailable ({st})"
            continue
        try:
            docs = json.loads(body)["response"]["docs"]
        except (ValueError, KeyError):
            continue
        for d in docs:
            rows[d["identifier"]] = (d.get("title", ""), d.get("publicdate", ""), d.get("item_size", ""))
        time.sleep(1.5)
    exts = tuple("." + e for e in ac["document_extensions"])
    lines = ["# identifier\ttitle\tpublicdate\titem_bytes\tdocument_files(name:bytes)\tknown"]
    for ident, (t, pd, sz) in sorted(rows.items()):
        body, st = http_get(f"https://archive.org/metadata/{ident}", timeout=60, retries=2)
        files = []
        if body:
            try:
                files = [f"{f['name']}:{f.get('size', '?')}" for f in json.loads(body).get("files", [])
                         if f.get("name", "").lower().endswith(exts)][:40]
            except ValueError:
                pass
        lines.append("\t".join([ident, t.replace("\t", " "), pd, str(sz), ";".join(files),
                                "yes" if ident in ac["known_items"] else "no"]))
        time.sleep(0.5)
    os.makedirs(common.abspath(common.HARVEST_META), exist_ok=True)
    with open(common.abspath(f"{common.HARVEST_META}/archive-org-candidates.tsv"), "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")
    REPORT["sources"]["archive-org"] = len(rows)
    print(f"[archive.org] {len(rows)} candidate items")


# ------------------------------------------------------------------ pending
def cmd_pending(_c):
    have = common.build_have_index()
    nf = set()
    for fn in os.listdir(common.abspath(common.HARVEST_META)) if os.path.isdir(common.abspath(common.HARVEST_META)) else []:
        if fn.startswith("notfound-"):
            with open(common.abspath(f"{common.HARVEST_META}/{fn}"), encoding="utf-8") as f:
                nf.update(x.strip() for x in f)
    buckets = {"learn": {}, "wayback": {}}
    for fn in sorted(os.listdir(common.abspath("queues/sources"))):
        with open(common.abspath(f"queues/sources/{fn}"), encoding="utf-8", errors="replace") as f:
            for line in f:
                u = line.strip()
                k, pid, _ = common.dest_for(u)
                if not k:
                    continue
                key = pid if k == "learn" else "wb:" + pid
                if key in have or u in nf:
                    continue
                buckets[k].setdefault(key, u)
    for k, d in buckets.items():
        n = write_lines(f"queues/pending/{k}.txt", d.values())
        REPORT["sources"][f"pending:{k}"] = n
        print(f"[pending] {k}: {n:,} URLs to harvest")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cmd", choices=["learn-toc", "learn-links", "wayback-cdx", "archive-org", "pending", "all"])
    a = ap.parse_args()
    c = cfg()
    steps = {"learn-toc": cmd_learn_toc, "learn-links": cmd_learn_links, "wayback-cdx": cmd_wayback_cdx,
             "archive-org": cmd_archive_org, "pending": cmd_pending}
    todo = ["learn-toc", "wayback-cdx", "archive-org", "pending"] if a.cmd == "all" else [a.cmd]
    os.makedirs(common.abspath(common.HARVEST_META), exist_ok=True)
    for s in todo:
        try:
            steps[s](c)
        except Exception as e:  # noqa: BLE001
            REPORT["sources"][s] = f"ERROR {type(e).__name__}: {e}"
            print(f"[{s}] ERROR {e}", flush=True)
    with open(common.abspath(f"{common.HARVEST_META}/discovery-report.json"), "w") as f:
        json.dump(REPORT, f, indent=1, ensure_ascii=False)
    print(json.dumps(REPORT["sources"], indent=1, ensure_ascii=False))


if __name__ == "__main__":
    main()
