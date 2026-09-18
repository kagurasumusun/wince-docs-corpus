#!/usr/bin/env python3
"""tools/harvest.py -- rate-limited Windows CE documentation harvester.

Fetches pages from a URL queue file into the corpus hierarchy:

  learn.microsoft.com/.../previous-versions/windows/embedded/<id>(v=tag)
        -> docs/mslearn/<book>/<id>.html        (book from page title/catalog)
  web.archive.org/web/20100501000000/https://msdn.microsoft.com/en-us/library/<id>.aspx
        -> docs/wayback-msdn/2010-05/<id>.html

Policy (repo AGENTS.md):
  * Polite sequential fetching only -- one in-flight request per target
    site, fixed delay between requests (learn: 0.4 s, archive.org: 1.5 s).
  * Only official Microsoft public documentation is collected.
  * Resume-safe: pages already stored are skipped.
  * Batch commit & push every --batch pages (default 500) when --push.

Usage:
  python3 tools/harvest.py --queue urls/to-fetch-mslearn.txt [--limit N]
      [--delay S] [--batch 500] [--push] [--queue-name NAME]
"""
import argparse
import datetime as _dt
import json
import os
import re
import subprocess
import sys
import time
import urllib.error
import urllib.parse
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
UA = ("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/124 Safari/537.36 "
      "wince-docs-corpus-harvester/2.0 (personal archival copy)")

TITLE = re.compile(r"<title>(.*?)</title>", re.S)

BOOK_RULES = (
    (r"\(Windows CE \.NET[^)]*\)", "windows-ce-net-4x"),
    (r"\(Windows CE 5\.0\)", "windows-ce-5.0"),
    (r"\(Windows CE 4\.[12]\)", "windows-ce-net-4x"),
    (r"\(Windows CE 4\.0\)", "windows-ce-net-4x"),
    (r"\(Windows Embedded CE 6\.0[^)]*\)", "windows-embedded-ce-6.0"),
    (r"\(Windows CE 3\.0[^)]*\)", "windows-ce-3.0"),
    (r"\(Windows Mobile[^)]*\)", None),   # resolved dynamically below
    (r"\(Handheld PC[^)]*\)", "handheld-pc"),
    (r"\(Palm-size PC[^)]*\)", "palm-size-pc"),
    (r"\(Microsoft\.RemoteToolSdk[^)]*\)", "windows-embedded-ce-6.0"),
    (r"\(Compact 7\)", "windows-embedded-compact-7"),
    (r"\((System|Microsoft)(\.[A-Za-z0-9_.]+)?\)$", "dotnet-compact-framework"),
    (r"\((?:[A-Za-z0-9_.]+ (?:Method|Property|Constructor|Field|Event|Class|"
     r"Structure|Interface|Enumeration|Delegate))$", "dotnet-compact-framework"),
)


def classify(title_text, body_head):
    """Map a learn 'previous-versions/windows/embedded' page to a book dir."""
    # learn.microsoft.com appends a site suffix to <title>; the
    # $-anchored .NET CF rules must see the bare book marker
    title_text = re.sub(r"\s*\|\s*Microsoft Learn\s*$", "", title_text)
    for pat, bucket in BOOK_RULES:
        m = re.search(pat, title_text)
        if m:
            if bucket is not None:
                return bucket
            wm = re.search(r"\(Windows Mobile ([0-9.]+)[^)]*\)", title_text)
            if wm:
                return "windows-mobile-" + wm.group(1)
            return "windows-mobile"
    # titles without a book marker: fall back to body markers (earliest hit)
    best, bi = "uncategorized", 1 << 60
    for bucket, s in (("windows-ce-5.0", "Windows CE 5.0"),
                      ("windows-embedded-ce-6.0", "Windows Embedded CE 6.0"),
                      ("windows-ce-net-4x", "Windows CE .NET")):
        i = body_head.find(s)
        if 0 <= i < bi:
            best, bi = bucket, i
    return best


def dest_for(url):
    """Return (relative dest path or None, page id) for a queue URL."""
    p = urllib.parse.urlparse(url)
    if "learn.microsoft.com" in p.netloc:
        last = p.path.rstrip("/").split("/")[-1]
        m = re.match(r"([a-z0-9]+)\(v=([a-z0-9.]+)\)$", last)
        if not m:
            return None, None
        return ("learn", m.group(1))
    if "web.archive.org" in p.netloc:
        m = re.match(r"/web/(\d+)/https?://msdn\.microsoft\.com/en-us/library/"
                     r"([a-z0-9]+)\.aspx$", p.path)
        if not m:
            return None, None
        return ("wayback", m.group(2))
    return None, None


def fetch(url, timeout=60, max_attempts=5):
    last_err = None
    for attempt in range(max_attempts):
        req = urllib.request.Request(url, headers={"User-Agent": UA})
        try:
            with urllib.request.urlopen(req, timeout=timeout) as resp:
                return resp.read(), resp.status
        except urllib.error.HTTPError as exc:
            if exc.code == 404:
                return None, 404
            if exc.code in (429, 503):
                wait = exc.headers.get("Retry-After")
                wait = int(wait) if (wait or "").isdigit() else 10 * (attempt + 1)
                time.sleep(min(wait, 120))
                continue
            last_err = str(exc)
        except Exception as exc:  # noqa: BLE001
            last_err = str(exc)
        time.sleep(3 * (attempt + 1))
    return None, last_err or "fetch-failed"


def git(*args, check=True):
    return subprocess.run(["git", "-C", ROOT, *args], check=check,
                          capture_output=True, text=True)


def commit_push(batch, pushed):
    git("config", "user.name", "wince-docs-corpus harvester", check=False)
    git("config", "user.email", "wince-corpus-harvester@users.noreply.github.com",
        check=False)
    git("add", "docs/", "data/index/", check=False)
    if git("diff", "--staged", "--quiet", check=False).returncode == 0:
        return pushed
    ts = _dt.datetime.now(_dt.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")
    c = git("commit", "-m", f"corpus: harvest batch +{batch} pages ({ts})",
            check=False)
    if c.returncode != 0:
        print(f"[push] commit failed: {c.stderr.strip()[:200]}", flush=True)
        return pushed
    git("pull", "--rebase", check=False)
    r = git("push", check=False)
    if r.returncode == 0:
        print(f"[push] ok (+{batch})", flush=True)
    else:
        print(f"[push] FAILED: {r.stderr.strip()[:200]}", flush=True)
    return pushed + batch


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--queue", required=True)
    ap.add_argument("--queue-name", default=None)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--delay", type=float, default=0.0)
    ap.add_argument("--batch", type=int, default=500)
    ap.add_argument("--push", action="store_true")
    args = ap.parse_args()

    qpath = args.queue if os.path.isabs(args.queue) else os.path.join(ROOT, args.queue)
    qname = args.queue_name or os.path.basename(qpath).replace(".txt", "")
    with open(qpath) as f:
        urls = [l.strip() for l in f if l.strip()]
    if args.limit:
        urls = urls[: args.limit]

    default_delay = {"wayback-msdn-2010": 1.5}.get(qname, 0.4)
    delay = args.delay or default_delay
    logdir = os.path.join(ROOT, "data", "harvest")
    os.makedirs(logdir, exist_ok=True)
    faillog = os.path.join(logdir, f"fail-{qname}.log")

    # resume index: ids already stored anywhere under docs/mslearn
    ms_root = os.path.join(ROOT, "docs/mslearn")
    have_ids = set()
    if os.path.isdir(ms_root):
        for b in os.listdir(ms_root):
            bd = os.path.join(ms_root, b)
            if os.path.isdir(bd):
                for fn in os.listdir(bd):
                    if fn.endswith(".html"):
                        have_ids.add(fn[:-5])
    wb_dir = os.path.join(ROOT, "docs/wayback-msdn/2010-05")
    if os.path.isdir(wb_dir):
        have_ids |= {"wb:" + fn[:-5] for fn in os.listdir(wb_dir)
                     if fn.endswith(".html")}

    have = skip = 0
    since_batch = 0
    t0 = time.time()
    for n, url in enumerate(urls, 1):
        kind, pid = dest_for(url)
        if kind is None:
            continue
        if kind == "learn":
            if pid in have_ids:
                skip += 1
                continue
        else:
            if "wb:" + pid in have_ids:
                skip += 1
                continue
        content, status = fetch(url)
        if content is None:
            with open(faillog, "a") as fh:
                fh.write(f"{status}\t{url}\n")
        else:
            head = content[:8000].decode("utf-8", "replace")
            m = TITLE.search(head)
            title = m.group(1).strip() if m else ""
            if kind == "learn":
                book = classify(title, head)
                d = os.path.join(ROOT, "docs/mslearn", book)
            else:
                d = os.path.join(ROOT, "docs/wayback-msdn/2010-05")
            os.makedirs(d, exist_ok=True)
            final = os.path.join(d, pid + ".html")
            tmp = final + ".part"
            with open(tmp, "wb") as fh:
                fh.write(content)
            os.replace(tmp, final)   # atomic: batch commits never see partials
            have_ids.add(pid if kind == "learn" else "wb:" + pid)
            have += 1
            since_batch += 1
        if have and have % 200 == 0:
            rate = have / max(time.time() - t0, 1)
            print(f"[{qname}] {n}/{len(urls)} stored={have} skipped={skip} "
                  f"{rate:.2f} pages/s", flush=True)
        if args.push and since_batch >= args.batch:
            commit_push(since_batch, 0)
            since_batch = 0
        time.sleep(delay)
    if args.push and since_batch:
        commit_push(since_batch, 0)
    print(f"[{qname}] DONE stored={have} skipped={skip} "
          f"fails={sum(1 for _ in open(faillog)) if os.path.exists(faillog) else 0}",
          flush=True)


if __name__ == "__main__":
    main()
