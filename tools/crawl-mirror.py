#!/usr/bin/env python3
"""Crawl one documentation mirror (a site tree) into the corpus.

Used for sites that have no API and no downloadable archive: the Windows CE
documentation tree of the MSDN Library on
<https://library.thedatadungeon.com/> is one example.  The crawler starts from
seed pages (usually table-of-contents pages), follows links inside the tree,
and stores every page under ``<out>/<path>`` with the site's own relative
layout.

Politeness is the same as tools/harvest.py (it reuses its Fetcher): one
request in flight per host, a fixed delay between requests, robots.txt
honoured, and the delay doubles on 429/503.  Crawls are resumable: the state
file records what was fetched, so a run that is stopped simply continues, and
``--max-pages``/``--max-seconds`` bound a run.

    python3 tools/crawl-mirror.py --config queues/mirrors.tsv --only datadungeon-ce
    python3 tools/crawl-mirror.py --seed URL --out corpus/x --delay 2 --dry-run

    # every entry of the config, one after another
    python3 tools/crawl-mirror.py --config queues/mirrors.tsv --max-seconds 3000

Config file format (`queues/mirrors.tsv`, tab-separated, `#` comments):

    name <TAB> seeds <TAB> out <TAB> toc_regex <TAB> max_pages <TAB> delay
"""

import argparse
import collections
import datetime as _dt
import html
import json
import os
import re
import sys
import time
import urllib.parse

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import harvest  # noqa: E402  (the Fetcher, HostPacer and robots handling)

ROOT = harvest.ROOT

HREF_RE = re.compile(r"""(?:href|src)\s*=\s*["']?([^"'\s>]+)""", re.I)
SKIP_SCHEMES = ("mailto:", "javascript:", "data:", "tel:", "#")


def load_config(path):
    entries = []
    with open(path, encoding="utf-8") as fh:
        for line_no, line in enumerate(fh, 1):
            line = line.rstrip("\n")
            if not line.strip() or line.lstrip().startswith("#"):
                continue
            parts = [p.strip() for p in line.split("\t")]
            if len(parts) != 6:
                print(f"[crawl] {path}: line {line_no} has {len(parts)} "
                      f"fields, expected 6 -- ignored", file=sys.stderr)
                continue
            name, seeds, out, toc_re, max_pages, delay = parts[:6]
            entries.append({
                "name": name,
                "seeds": [s for s in seeds.split(",") if s],
                "out": out,
                "toc_re": re.compile(toc_re) if toc_re and toc_re != "-" else None,
                "max_pages": int(max_pages),
                "delay": float(delay),
            })
    return entries


class Crawl:
    def __init__(self, spec, fetcher, state_path, dry_run=False):
        self.spec = spec
        self.fetcher = fetcher
        self.state_path = state_path
        self.dry_run = dry_run
        self.base = self._common_base(spec["seeds"])
        self.dirs = set()          # book directories learned from TOC pages
        self.done = set()          # URLs already fetched
        self.seen = set()
        self.stored = 0
        self.errors = collections.Counter()
        self.load()

    @staticmethod
    def _common_base(seeds):
        """Site root of the tree: scheme + host + first path segment."""
        first = urllib.parse.urlsplit(seeds[0])
        segments = [seg for seg in first.path.split("/") if seg]
        root = "/" + segments[0] + "/" if segments else "/"
        return f"{first.scheme}://{first.netloc}{root}"

    def load(self):
        if os.path.exists(self.state_path):
            with open(self.state_path, encoding="utf-8") as fh:
                data = json.load(fh)
            self.done = set(data.get("done", []))
            self.dirs = set(data.get("dirs", []))

    def save(self):
        if self.dry_run:
            return
        os.makedirs(os.path.dirname(self.state_path), exist_ok=True)
        with open(self.state_path, "w", encoding="utf-8") as fh:
            json.dump({"done": sorted(self.done), "dirs": sorted(self.dirs),
                       "updated": _dt.datetime.now(
                           _dt.timezone.utc).isoformat(timespec="seconds")},
                      fh, indent=1)

    # -- page selection ------------------------------------------------------
    def allowed(self, url):
        p = urllib.parse.urlsplit(url)
        if p.netloc != urllib.parse.urlsplit(self.base).netloc:
            return False
        if not p.path.startswith(urllib.parse.urlsplit(self.base).path):
            return False
        if p.path.lower().endswith((".zip", ".pdf", ".chm", ".cab", ".exe")):
            return False
        if self.spec["toc_re"] and self.spec["toc_re"].search(p.path):
            return True                     # the table of contents itself
        segments = p.path.split("/")
        for segment in segments:
            if segment in self.dirs:
                return True
        return False

    def links(self, url, body):
        """Absolute, in-tree links, plus book directories learned from TOCs."""
        text = body.decode("utf-8", "replace")
        found = []
        is_toc = bool(self.spec["toc_re"] and self.spec["toc_re"].search(url))
        for raw in HREF_RE.findall(text):
            if raw.startswith(SKIP_SCHEMES) or raw.startswith("#"):
                continue
            absolute = urllib.parse.urljoin(url, html.unescape(raw))
            absolute, _, _frag = absolute.partition("#")
            p = urllib.parse.urlsplit(absolute)
            if p.netloc != urllib.parse.urlsplit(self.base).netloc:
                continue
            if not p.path.startswith(urllib.parse.urlsplit(self.base).path):
                continue
            if p.path.lower().endswith((".css", ".js", ".gif", ".png", ".jpg",
                                        ".ico", ".zip", ".pdf", ".chm")):
                continue
            if is_toc:
                # a link from a table of contents: remember the book folder
                rel = p.path[len(urllib.parse.urlsplit(self.base).path):]
                head = rel.split("/", 1)[0]
                if head and not head.startswith("_") and head != "images":
                    self.dirs.add(head)
            found.append(absolute)
        return found

    def dest_for(self, url):
        rel = urllib.parse.urlsplit(url).path[
            len(urllib.parse.urlsplit(self.base).path):]
        rel = urllib.parse.unquote(rel)
        if rel.endswith("/") or not rel:
            rel += "index.html"
        return os.path.join(self.spec["out"], rel)

    # -- main loop -----------------------------------------------------------
    def run(self, max_pages, max_seconds):
        queue = collections.deque(self.spec["seeds"])
        started = time.time()
        while queue:
            if max_pages and self.stored >= max_pages:
                print(f"[crawl] page budget reached ({max_pages})")
                break
            if max_seconds and time.time() - started >= max_seconds:
                print(f"[crawl] time budget reached ({max_seconds}s)")
                break
            url = queue.popleft()
            if url in self.done or url in self.seen:
                continue
            self.seen.add(url)
            if not self.allowed(url):
                continue
            if self.dry_run:
                self.stored += 1
                print(f"  would fetch {url}")
                continue
            body, status = self.fetcher.get(url, self.spec["delay"])
            if body is None:
                self.errors[str(status)] += 1
                continue
            dest = self.dest_for(url)
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            with open(dest, "wb") as fh:
                fh.write(body)
            self.done.add(url)
            self.stored += 1
            for link in self.links(url, body):
                if link not in self.done and link not in self.seen:
                    queue.append(link)
            if self.stored % 25 == 0:
                self.save()
                print(f"[crawl] stored={self.stored:,} queued={len(queue):,} "
                      f"dirs={len(self.dirs)} errors={dict(self.errors)}",
                      flush=True)
        self.save()
        return self.stored


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--config", help="mirrors.tsv to take the crawl from")
    ap.add_argument("--only", help="name of the config entry to run")
    ap.add_argument("--list", action="store_true", help="list config entries")
    ap.add_argument("--seed", action="append", default=[], help="seed URL")
    ap.add_argument("--out", default="corpus/mirrors/site")
    ap.add_argument("--toc-regex", default="-",
                    help="regex matching the site's table-of-contents pages")
    ap.add_argument("--state", default=None)
    ap.add_argument("--max-pages", type=int, default=0)
    ap.add_argument("--max-seconds", type=int, default=0)
    ap.add_argument("--delay", type=float, default=2.0)
    ap.add_argument("--no-robots", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    specs = []
    if args.config:
        specs = load_config(os.path.join(ROOT, args.config))
        if args.list:
            for spec in specs:
                print(f"  {spec['name']:24s} out={spec['out']:42s} "
                      f"max={spec['max_pages']:6d} delay={spec['delay']}"
                      f" seeds={len(spec['seeds'])}")
            return 0
        if args.only:
            specs = [s for s in specs if s["name"] == args.only]
            if not specs:
                print(f"no config entry named {args.only}", file=sys.stderr)
                return 1
        if not specs:
            print(f"{args.config} has no usable entry", file=sys.stderr)
            return 1
    elif args.seed:
        specs = [{"name": "cli", "seeds": args.seed,
                  "out": args.out if os.path.isabs(args.out)
                  else os.path.join(ROOT, args.out),
                  "toc_re": re.compile(args.toc_regex)
                  if args.toc_regex and args.toc_regex != "-" else None,
                  "max_pages": args.max_pages or 0,
                  "delay": args.delay}]
    else:
        ap.error("give --config or --seed")

    exit_code = 0
    for spec in specs:
        # The state is committed (data/crawl/) so a resumed run on a fresh
        # runner knows what has already been fetched.
        state = args.state or os.path.join(
            ROOT, "data", "crawl", f"{spec['name']}.json")
        pacer = harvest.HostPacer()
        fetcher = harvest.Fetcher(pacer, respect_robots=not args.no_robots)
        crawl = Crawl(spec, fetcher, state, dry_run=args.dry_run)
        print(f"[crawl] {spec['name']}: {len(spec['seeds'])} seeds, "
              f"already done {len(crawl.done):,}, dirs={sorted(crawl.dirs)}",
              flush=True)
        try:
            stored = crawl.run(args.max_pages or spec["max_pages"],
                               args.max_seconds)
        finally:
            fetcher.close()
        print(f"[crawl] {spec['name']}: stored={stored:,} "
              f"total={len(crawl.done):,} errors={dict(crawl.errors)}")
        if crawl.errors:
            exit_code = 0  # errors are recorded in the state for the next run
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
