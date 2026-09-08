#!/usr/bin/env python3
"""mega-fetch.py -- parallel full-catalog harvest from the Learn archive.

Fetches every page of the CE 5.0 (v=msdn.10) and CE 6.0
(v=winembedded.60) catalogs into pages5/ and pages6/ (the CE .NET /
winn5 catalog is deliberately excluded per the owner's instruction).
Existing files are skipped; transient failures are retried with backoff.
"""
import os
import re
import sys
import time
import urllib.request
import urllib.error
from concurrent.futures import ThreadPoolExecutor, as_completed

ROOT = os.path.dirname(os.path.abspath(__file__))
BASE = "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{}"
UA = ("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/120 Safari/537.36")
WORKERS = int(os.environ.get("MEGA_WORKERS", "8"))
LOG = os.path.join(ROOT, "mega-fetch.log")
FAILLOG = os.path.join(ROOT, "mega-fetch-fail.log")

def split_id(pid):
    m = re.search(r'\((v=[a-z0-9.]+)\)$', pid)
    if m:
        return pid[:m.start()], m.group(1)[2:]
    return pid, "msdn.10"

def fetch_one(pid, destdir, stats):
    root, tag = split_id(pid)
    path = os.path.join(destdir, root + ".html")
    if os.path.exists(path) and os.path.getsize(path) > 20000:
        return "have"
    url = BASE.format(root + "(" + tag + ")")
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    for attempt in range(5):
        try:
            with urllib.request.urlopen(req, timeout=60) as resp:
                data = resp.read()
            break
        except urllib.error.HTTPError as exc:
            if exc.code == 404:
                with open(FAILLOG, "a") as fh:
                    fh.write(f"404\t{pid}\n")
                return "404"
            if exc.code in (429, 503):
                time.sleep(10 * (attempt + 1))
                continue
            if attempt == 4:
                with open(FAILLOG, "a") as fh:
                    fh.write(f"{exc.code}\t{pid}\n")
                return "fail"
            time.sleep(3 * (attempt + 1))
        except Exception:
            if attempt == 4:
                with open(FAILLOG, "a") as fh:
                    fh.write(f"exc\t{pid}\n")
                return "fail"
            time.sleep(3 * (attempt + 1))
    else:
        with open(FAILLOG, "a") as fh:
            fh.write(f"timeout\t{pid}\n")
        return "fail"
    if len(data) < 20000:
        with open(FAILLOG, "a") as fh:
            fh.write(f"small\t{pid}\t{len(data)}\n")
        return "small"
    tmp = path + ".tmp"
    with open(tmp, "wb") as fh:
        fh.write(data)
    os.replace(tmp, path)
    return "ok"

def main():
    for spec in (("full-ce50.manifest", "pages5"),
                 ("full-ce60.manifest", "pages6")):
        man, destdir = spec
        rows = []
        for l in open(os.path.join(ROOT, man), encoding="utf-8"):
            l = l.rstrip("\n")
            if l:
                rows.append(l.split("\t")[0])
        todo = [p for p in rows
                if not (os.path.exists(os.path.join(
                    destdir, re.sub(r"\(v=[a-z0-9.]+\)$", "", p) + ".html"))
                    and os.path.getsize(os.path.join(
                        destdir, re.sub(r"\(v=[a-z0-9.]+\)$", "", p) + ".html")) > 20000)]
        print(f"[mega] {man}: {len(rows)} catalog, {len(todo)} to fetch", flush=True)
        stats = {"ok": 0, "have": 0, "404": 0, "fail": 0, "small": 0}
        t0 = time.time()
        with ThreadPoolExecutor(max_workers=WORKERS) as ex:
            futs = {ex.submit(fetch_one, p, os.path.join(ROOT, destdir), stats): p
                    for p in todo}
            for i, fut in enumerate(as_completed(futs), 1):
                r = fut.result()
                stats[r] += 1
                if i % 200 == 0 or i == len(futs):
                    dt = time.time() - t0
                    rate = i / dt if dt else 0
                    eta = (len(futs) - i) / rate if rate else 0
                    with open(LOG, "a") as fh:
                        fh.write(f"{man} {i}/{len(futs)} "
                                 f"ok={stats['ok']} 404={stats['404']} "
                                 f"fail={stats['fail']} {rate:.1f}/s "
                                 f"eta={eta/60:.0f}m\n")
        print(f"[mega] {man} done: {stats} in {time.time()-t0:.0f}s", flush=True)
    print("[mega] ALL DONE", flush=True)

if __name__ == "__main__":
    main()
