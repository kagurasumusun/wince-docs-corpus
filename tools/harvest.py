#!/usr/bin/env python3
"""harvest.py -- fast, polite, resumable Windows CE documentation harvester.

  learn.microsoft.com/.../<id>(v=tag)        -> corpus/learn/<product>/<id>.html
  web.archive.org/web/<ts>[id_]/msdn...<id>  -> corpus/wayback/msdn-<yyyy>-<mm>/<id>.html

What changed vs. the old sequential harvester (why it is much faster):
  * Bounded concurrency per host (token-bucket rate limit shared by all threads),
    keep-alive connections, gzip. Adaptive back-off on 429/503 (never speeds up
    beyond the configured rate).
  * "Already have it" is answered from `git ls-tree` -> the workflow needs only a
    sparse/blobless checkout, not the 3.4 GB working tree.
  * Permanent 404s are remembered (meta/harvest/notfound-*.txt) and never re-fetched.
  * Commits add only the batch's new files (git add --pathspec-from-file) instead of
    scanning the whole tree; commit/push runs in the background while fetching continues.
  * --max-minutes stops cleanly before the Actions 6h limit (exit code 10 = queue not
    finished, so the workflow can re-dispatch itself); --shard i/n for parallel jobs.

Usage:
  python3 tools/harvest.py --queue queues/pending-learn.txt [--limit N] [--workers W]
      [--rps R] [--batch 1000] [--max-minutes M] [--shard 0/2] [--push] [--retry-404]
"""
import argparse
import concurrent.futures as cf
import datetime as dt
import gzip
import http.client
import json
import os
import random
import subprocess
import sys
import threading
import time
import urllib.parse
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common  # noqa: E402

ROOT = common.ROOT
UA = ("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) "
      "Chrome/124 Safari/537.36 wince-docs-corpus-harvester/3.0 (personal archival copy)")

# host -> (workers, requests/second). Conservative defaults; override with flags.
HOST_DEFAULTS = {
    "learn.microsoft.com": (6, 6.0),
    "web.archive.org": (2, 1.0),
}
EXIT_MORE_WORK = 10


class Throttle:
    """Global token bucket + adaptive slowdown factor for one host."""

    def __init__(self, rps):
        self.base = 1.0 / rps
        self.factor = 1.0
        self.next = 0.0
        self.lock = threading.Lock()
        self.consec = 0
        self.ok = 0

    def wait(self):
        with self.lock:
            now = time.monotonic()
            slot = max(now, self.next)
            self.next = slot + self.base * self.factor
        delay = slot - now
        if delay > 0:
            time.sleep(delay)

    def throttled(self):
        with self.lock:
            self.consec += 1
            self.ok = 0
            if self.consec % 3 == 0:
                self.factor = min(self.factor * 2, 30.0)
                print(f"[throttle] x{self.factor:.0f} slower", flush=True)

    def good(self):
        with self.lock:
            self.consec = 0
            self.ok += 1
            if self.ok >= 50 and self.factor > 1.0:
                self.factor = max(1.0, self.factor / 2)
                self.ok = 0


_local = threading.local()


def _conn(host):
    pool = getattr(_local, "pool", None)
    if pool is None:
        pool = _local.pool = {}
    c = pool.get(host)
    if c is None:
        c = pool[host] = http.client.HTTPSConnection(host, timeout=60)
    return c


def _drop(host):
    c = getattr(_local, "pool", {}).pop(host, None)
    if c:
        try:
            c.close()
        except OSError:
            pass


def fetch(url, throttles, max_attempts=5):
    """GET url following redirects. Returns (body|None, status|error-string)."""
    last = "fetch-failed"
    for attempt in range(max_attempts):
        cur, hops = url, 0
        try:
            while True:
                p = urllib.parse.urlparse(cur)
                th = throttles.get(p.netloc)
                if th:
                    th.wait()
                path = p.path + (("?" + p.query) if p.query else "")
                c = _conn(p.netloc)
                c.request("GET", path, headers={
                    "User-Agent": UA, "Accept-Encoding": "gzip, deflate",
                    "Accept": "text/html,*/*;q=0.8"})
                r = c.getresponse()
                body = r.read()
                st = r.status
                if st in (301, 302, 303, 307, 308) and hops < 6:
                    cur = urllib.parse.urljoin(cur, r.getheader("Location", ""))
                    hops += 1
                    continue
                break
            enc = (r.getheader("Content-Encoding") or "").lower()
            if enc == "gzip":
                body = gzip.decompress(body)
            elif enc == "deflate":
                body = zlib.decompress(body)
            th = throttles.get(urllib.parse.urlparse(url).netloc)
            if st == 200:
                th and th.good()
                return body, 200
            if st in (404, 410):
                return None, 404
            if st in (429, 503):
                th and th.throttled()
                ra = r.getheader("Retry-After") or ""
                time.sleep(min(int(ra) if ra.isdigit() else 20 * (attempt + 1), 300))
                continue
            last = f"http-{st}"
        except Exception as exc:  # noqa: BLE001
            last = f"{type(exc).__name__}: {exc}"[:120]
            _drop(urllib.parse.urlparse(url).netloc)
        time.sleep(min(2 * (attempt + 1) + random.random(), 20))
    return None, last


class Git:
    def __init__(self):
        self.lock = threading.Lock()

    def run(self, *a, inp=None, check=False):
        return subprocess.run(["git", "-C", ROOT, "--literal-pathspecs", *a], input=inp,
                              capture_output=True, text=True, check=check)

    def commit_push(self, paths, extra_paths, note, push):
        with self.lock:
            ad = self.run("add", "--sparse", "--pathspec-from-file=-", "--pathspec-file-nul",
                          inp="\0".join(paths + extra_paths))
            if ad.returncode:
                print("[git] add failed:", ad.stderr.strip()[:300], flush=True)
                return
            if self.run("diff", "--staged", "--quiet").returncode == 0:
                return
            ts = dt.datetime.now(dt.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")
            c = self.run("commit", "-q", "-m", f"corpus: harvest +{len(paths)} pages {note} ({ts})")
            if c.returncode:
                print("[git] commit failed:", c.stderr.strip()[:200], flush=True)
                return
            if not push:
                return
            for i in range(6):
                branch = self.run("rev-parse", "--abbrev-ref", "HEAD").stdout.strip()
                self.run("fetch", "-q", "origin", branch)
                rb = self.run("rebase", "-q", f"origin/{branch}")
                if rb.returncode:
                    self.run("rebase", "--abort")
                    print("[git] rebase failed:", rb.stderr.strip()[:200], flush=True)
                if self.run("push", "-q", "origin", f"HEAD:{branch}").returncode == 0:
                    print(f"[git] pushed +{len(paths)}", flush=True)
                    return
                time.sleep(3 + random.random() * 7 * (i + 1))
            print("[git] PUSH FAILED (commits kept locally)", flush=True)


def store(kind, pid, extra, content):
    head = content[:16000].decode("utf-8", "replace")
    m = common.TITLE_RE.search(head)
    title = m.group(1).strip() if m else ""
    if kind == "learn":
        d = f"{common.LEARN_DIR}/{common.classify(title, head)}"
    else:
        d = f"{common.WAYBACK_DIR}/msdn-{extra}"
    os.makedirs(common.abspath(d), exist_ok=True)
    rel = f"{d}/{pid}.html"
    final = common.abspath(rel)
    tmp = final + ".part"
    with open(tmp, "wb") as fh:
        fh.write(content)
    os.replace(tmp, final)
    return rel


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--queue", required=True)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--workers", type=int, default=0, help="override workers per host")
    ap.add_argument("--rps", type=float, default=0.0, help="override requests/sec per host")
    ap.add_argument("--batch", type=int, default=1000)
    ap.add_argument("--max-minutes", type=float, default=0)
    ap.add_argument("--shard", default="", help="i/n")
    ap.add_argument("--push", action="store_true")
    ap.add_argument("--retry-404", action="store_true")
    a = ap.parse_args()

    qpath = a.queue if os.path.isabs(a.queue) else common.abspath(a.queue)
    qname = os.path.basename(qpath).rsplit(".", 1)[0]
    shard_i, shard_n = (map(int, a.shard.split("/")) if a.shard else (0, 1))
    deadline = time.monotonic() + a.max_minutes * 60 if a.max_minutes else None

    os.makedirs(common.abspath(common.HARVEST_META), exist_ok=True)
    nf_path = common.abspath(f"{common.HARVEST_META}/notfound-{qname}.txt")
    notfound = set()
    if os.path.exists(nf_path) and not a.retry_404:
        notfound = {x.strip() for x in open(nf_path, encoding="utf-8") if x.strip()}

    t0 = time.time()
    have = common.build_have_index()
    print(f"[{qname}] have={len(have):,} notfound={len(notfound):,} "
          f"index={time.time() - t0:.1f}s shard={shard_i}/{shard_n}", flush=True)

    throttles = {}
    for host, (w, r) in HOST_DEFAULTS.items():
        throttles[host] = Throttle(a.rps or r)
    host_workers = {h: (a.workers or w) for h, (w, _) in HOST_DEFAULTS.items()}

    stats = dict(lines=0, skipped=0, invalid=0, known404=0, stored=0, notfound=0, failed=0, deferred=0)
    fails, new404 = [], []
    seen = set()

    def pending():
        with open(qpath, encoding="utf-8", errors="replace", buffering=1 << 20) as fh:
            for line in fh:
                url = line.strip()
                if not url or url.startswith("#"):
                    continue
                stats["lines"] += 1
                kind, pid, extra = common.dest_for(url)
                if kind is None:
                    stats["invalid"] += 1
                    continue
                if shard_n > 1 and zlib.crc32(url.encode()) % shard_n != shard_i:
                    continue
                key = pid if kind == "learn" else "wb:" + pid
                if key in have or key in seen:
                    stats["skipped"] += 1
                    continue
                if url in notfound:
                    stats["known404"] += 1
                    continue
                seen.add(key)
                yield url, kind, pid, extra, key

    def work(item):
        url, kind, pid, extra, key = item
        if deadline and time.monotonic() > deadline:
            return "deferred", url, None
        body, st = fetch(url, throttles)
        if body is None:
            return ("notfound" if st == 404 else "failed"), url, st
        if len(body) < 400:
            return "failed", url, "tiny-body"
        return "stored", url, store(kind, pid, extra, body), key

    git = Git()
    bg = cf.ThreadPoolExecutor(1)
    bg_fut = None
    batch_paths = []
    nworkers = max(host_workers.values())

    def flush_batch(final=False):
        nonlocal bg_fut, batch_paths
        if not batch_paths and not final:
            return
        paths, batch_paths = batch_paths, []
        if bg_fut:
            bg_fut.result()
        if a.push or paths:
            bg_fut = bg.submit(git.commit_push, paths, [], qname, a.push)

    import itertools
    it = pending()
    done_all = True
    with cf.ThreadPoolExecutor(nworkers) as pool:
        while True:
            n = min(a.batch, (a.limit - stats["stored"] - stats["notfound"] - stats["failed"])
                    if a.limit else a.batch)
            if n <= 0:
                break
            window = list(itertools.islice(it, n))
            if not window:
                break
            for res in pool.map(work, window):
                s = res[0]
                if s == "stored":
                    stats["stored"] += 1
                    batch_paths.append(res[2])
                    have.add(res[3])
                elif s == "notfound":
                    stats["notfound"] += 1
                    new404.append(res[1])
                elif s == "failed":
                    stats["failed"] += 1
                    fails.append(f"{res[2]}\t{res[1]}")
                else:
                    stats["deferred"] += 1
            el = max(time.time() - t0, 1)
            print(f"[{qname}] stored={stats['stored']:,} 404={stats['notfound']:,} "
                  f"failed={stats['failed']:,} skipped={stats['skipped']:,} "
                  f"rate={stats['stored'] / el:.1f}/s", flush=True)
            flush_batch()
            if deadline and time.monotonic() > deadline:
                done_all = False
                break

    if new404:
        with open(nf_path, "a", encoding="utf-8") as fh:
            fh.write("\n".join(new404) + "\n")
    summary = dict(queue=qname, finished=done_all and stats["deferred"] == 0,
                   time=dt.datetime.now(dt.timezone.utc).isoformat(timespec="seconds"),
                   seconds=round(time.time() - t0), **stats)
    with open(common.abspath(f"{common.HARVEST_META}/last-run-{qname}.json"), "w") as fh:
        json.dump(summary, fh, indent=1)
    if fails:
        with open(common.abspath(f"{common.HARVEST_META}/failed-{qname}.tsv"), "w") as fh:
            fh.write("\n".join(fails) + "\n")
    if bg_fut:
        bg_fut.result()
    flush_batch(final=True)
    bg.shutdown(wait=True)
    # last commit: logs/summary only
    meta_paths = [f"{common.HARVEST_META}/last-run-{qname}.json"] + (
        [f"{common.HARVEST_META}/notfound-{qname}.txt"] if new404 or os.path.exists(nf_path) else [])
    git.commit_push([], meta_paths, f"({qname} run summary)", a.push)
    print(f"[{qname}] DONE {json.dumps(summary)}", flush=True)
    return EXIT_MORE_WORK if (deadline and not summary["finished"]) else 0


if __name__ == "__main__":
    sys.exit(main())
