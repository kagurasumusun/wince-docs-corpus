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

# The Data Dungeon mirror wraps every document in a little frameset (a header
# bar, the library's table of contents in one iframe, the document itself in
# another).  The document is `<name>.content.htm`; the wrapper carries the
# marker below and is navigation chrome, not documentation.
WRAPPER_MARKERS = (b"chmweb_content_frame", b"ddl_page_header")
# `_alts/` holds "other versions of this page" lists - links into the same
# document in the mirror's other library editions, not documentation.
ALT_PATH = "/_alts/"
CHARSET_RE = re.compile(rb"charset\s*=\s*[\"']?([A-Za-z0-9_.:-]+)", re.I)
CP1252 = {"windows-1252", "cp1252", "iso-8859-1", "latin-1", "iso8859-1"}
UTF8 = {"utf-8", "utf8", "ascii", "us-ascii"}


def normalize(url):
    """Percent-encode the parts of a link that are not ASCII.

    A few pages of the mirror carry raw typographic quotes in their hrefs;
    a request line must be ASCII, so those URLs have to be encoded before
    they can be fetched (the local file name decodes back to the same text).
    """
    parts = urllib.parse.urlsplit(url)
    if parts.path.isascii() and parts.query.isascii():
        return url
    path = urllib.parse.quote(parts.path, safe="/%:@&=+$,;~()!*'")
    query = urllib.parse.quote(parts.query, safe="=&%:;+,/?@!*'()~$")
    return urllib.parse.urlunsplit(
        (parts.scheme, parts.netloc, path, query, ""))


def to_utf8(body):
    """Decode a page the way its own meta tag says and re-encode as UTF-8.

    The mirror serves the MSDN documents as Windows-1252; the corpus keeps
    every page as UTF-8 (see corpus/README.md), so the bytes are converted
    while the markup itself is untouched.
    """
    match = CHARSET_RE.search(body[:2048])
    charset = match.group(1).decode("ascii", "replace").lower() if match else ""
    if charset in UTF8:
        return body
    if not charset:
        # No declaration: trust a clean UTF-8 decode, else it is the
        # Windows-1252 the mirror uses for everything else.
        try:
            body.decode("utf-8")
            return body
        except UnicodeDecodeError:
            codec = "cp1252"
    elif charset in CP1252:
        codec = "cp1252"
    else:
        codec = charset
    try:
        text = body.decode(codec)
    except (UnicodeDecodeError, LookupError):
        text = body.decode("cp1252", "replace")
    return text.encode("utf-8")


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
        self.pending = set()       # frontier: links found but not fetched yet
        self.seen = set()
        self.stored = 0
        self.errors = collections.Counter()
        self.skipped = collections.Counter()
        self.failures = []         # capped list of "Exception: text :: url"
        self.last_save = 0
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
            self.failures = list(data.get("failures", []))
            if "pending" in data:
                self.pending = set(data["pending"])
            else:
                # A state file from before the frontier was recorded: the
                # links of the stored pages are still on disk, so the queue
                # can be rebuilt instead of stopping early.
                self.pending = self.rebuild_frontier()

    def rebuild_frontier(self):
        """Links of the pages already stored that have not been fetched yet."""
        pending = set()
        for url in sorted(self.done):
            dest = self.dest_for(url)
            if not os.path.exists(dest):
                continue
            try:
                with open(dest, "rb") as fh:
                    body = fh.read()
            except OSError:
                continue
            for link in self.links(url, body):     # also learns book folders
                if link not in self.done:
                    pending.add(link)
        return pending

    def save(self):
        if self.dry_run:
            return
        os.makedirs(os.path.dirname(self.state_path), exist_ok=True)
        with open(self.state_path, "w", encoding="utf-8") as fh:
            json.dump({"done": sorted(self.done), "dirs": sorted(self.dirs),
                       "pending": sorted(self.pending),
                       "errors": dict(self.errors),
                       "skipped": dict(self.skipped),
                       "failures": self.failures[-20:],
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
        if "/_toc/" in p.path and self.spec["toc_re"]:
            # Another section's table of contents (the mirror's other
            # library sections sit next to ours under _toc/): following it
            # would walk out of the documentation set we came for.
            return False
        segments = p.path.split("/")
        for segment in segments:
            if segment in self.dirs:
                return True
        return False

    def content_url(self, url):
        """The document of a wrapped page: `X.htm` -> `X.content.htm`.

        Returns None when the URL is not a wrapper candidate.
        """
        parts = urllib.parse.urlsplit(url)
        path = parts.path
        if not path.endswith(".htm") or path.endswith(".content.htm"):
            return None
        if "/_toc/" in path or ALT_PATH in path:
            return None
        return url[: -len(".htm")] + ".content.htm"

    @staticmethod
    def wrapper_url(content_url):
        """`X.content.htm` -> `X.htm`: the page to fall back to."""
        return content_url[: -len(".content.htm")] + ".htm"

    def prefer_content(self, url):
        """Point a link at the document inside the wrapper, if it has one."""
        return self.content_url(url) or url

    def links(self, url, body):
        """Absolute, in-tree links, plus book directories learned from TOCs."""
        text = body.decode("utf-8", "replace")
        found = []
        is_toc = bool(self.spec["toc_re"] and self.spec["toc_re"].search(url)) \
            and "/_toc/" in url
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
            found.append(self.prefer_content(normalize(absolute)))
        return found

    def dest_for(self, url):
        rel = urllib.parse.urlsplit(url).path[
            len(urllib.parse.urlsplit(self.base).path):]
        rel = urllib.parse.unquote(rel)
        if rel.endswith("/") or not rel:
            rel += "index.html"
        return os.path.join(self.spec["out"], rel)

    # -- main loop -----------------------------------------------------------
    def visit(self, url, queue):
        """Fetch one URL: store it, skip it, or queue what it links to."""
        if not self.allowed(url):
            self.done.add(url)      # out of scope: do not queue it again
            return
        if ALT_PATH in urllib.parse.urlsplit(url).path:
            self.skipped["alt-page"] += 1
            self.done.add(url)
            return
        if self.dry_run:
            self.stored += 1
            print(f"  would fetch {url}")
            return
        body, status = self.fetcher.get(url, self.spec["delay"])
        if body is None and url.endswith(".content.htm"):
            # Not every page of the mirror has the `X.content.htm` form:
            # fall back to the plain page.  The rule is deterministic, so a
            # run that resumes from a saved frontier works the same way.
            original = self.wrapper_url(url)
            body, status = self.fetcher.get(original, self.spec["delay"])
            if body is None:
                self.errors[str(status)] += 1
                self.done.add(url)
                return
            self.skipped["no-content-page"] += 1
            self.done.add(url)
            url = original
        if body is None:
            self.errors[str(status)] += 1
            self.failures.append(f"{status}: {url}")
            return
        # Follow everything, store the documentation: the wrappers are
        # navigation chrome, their links are still worth walking.
        if any(mark in body for mark in WRAPPER_MARKERS):
            self.skipped["wrapper"] += 1
            self.done.add(url)
            for link in self.links(url, body):
                if link not in self.done and link not in self.seen:
                    queue.append(link)
            return
        body = to_utf8(body)
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
            print(f"[crawl] stored={self.stored:,} queued={len(queue):,} "
                  f"dirs={len(self.dirs)} errors={dict(self.errors)} "
                  f"skipped={dict(self.skipped)}", flush=True)

    def run(self, max_pages, max_seconds):
        queue = collections.deque(sorted(self.pending)
                                  or [self.prefer_content(u)
                                      for u in self.spec["seeds"]])
        if self.pending:
            print(f"[crawl] resuming with {len(self.pending):,} queued URLs")
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
            try:
                self.visit(url, queue)
            except Exception as exc:                      # noqa: BLE001
                # One unparsable URL, one unreadable path: record it and
                # keep going.  The state file carries the details, because a
                # runner's job log is not always reachable afterwards.
                self.errors[type(exc).__name__] += 1
                self.failures.append(f"{type(exc).__name__}: {exc} :: {url}")
                print(f"[crawl] FAILED {url}: {type(exc).__name__}: {exc}",
                      flush=True)
                self.done.add(url)
            if self.stored and self.stored % 25 == 0 \
                    and self.stored != self.last_save:
                self.last_save = self.stored
                self.pending = set(queue)
                self.save()
        self.pending = set(queue)
        self.save()
        return self.stored


def show_status():
    """One line per entry in queues/mirrors.tsv, from its saved state."""
    state_dir = os.path.join(ROOT, "data", "crawl")
    specs = load_config(os.path.join(ROOT, "queues", "mirrors.tsv"))
    if not os.path.isdir(state_dir):
        print("no crawl state yet (data/crawl/)")
        return 0
    for spec in specs:
        path = os.path.join(state_dir, f"{spec['name']}.json")
        if not os.path.exists(path):
            print(f"{spec['name']}: not started")
            continue
        with open(path, encoding="utf-8") as fh:
            data = json.load(fh)
        done, pending = len(data.get("done", [])), len(data.get("pending", []))
        on_disk = 0
        out = spec["out"] if os.path.isabs(spec["out"]) \
            else os.path.join(ROOT, spec["out"])
        for _dirpath, _dirnames, filenames in os.walk(out):
            on_disk += sum(1 for f in filenames if f != "README.md")
        page_budget = spec["max_pages"] or 0
        runs = "-"
        if page_budget:
            runs = f"~{max(1, -(-pending // page_budget))} more run(s)"
        print(f"{spec['name']}: {on_disk:,} pages on disk | queued {pending:,} | "
              f"fetched {done:,} | books {len(data.get('dirs', []))} | "
              f"errors {data.get('errors') or '{}'} | "
              f"skipped {data.get('skipped') or '{}'} | {runs}")
        print(f"    updated {data.get('updated', '?')} | "
              f"out {spec['out']}")
        for failure in data.get("failures", [])[-3:]:
            print(f"    failure: {failure[:120]}")
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--config", help="mirrors.tsv to take the crawl from")
    ap.add_argument("--only", help="name of the config entry to run")
    ap.add_argument("--list", action="store_true", help="list config entries")
    ap.add_argument("--status", action="store_true",
                    help="print what each saved crawl has collected")
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

    if args.status:
        return show_status()

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
              f"total={len(crawl.done):,} errors={dict(crawl.errors)} "
              f"skipped={dict(crawl.skipped)}")
        if crawl.errors:
            exit_code = 0  # errors are recorded in the state for the next run
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
