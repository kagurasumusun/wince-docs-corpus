#!/usr/bin/env python3
"""tools/harvest.py -- rate-limited Windows CE documentation harvester.

Fetches pages from a URL queue file into the corpus hierarchy:

  learn.microsoft.com/.../previous-versions/windows/embedded/<id>(v=tag)
        -> corpus/learn/<set>/<id>(v=tag).html

  web.archive.org/web/20100501000000/https://msdn.microsoft.com/en-us/library/<id>.aspx
        -> corpus/msdn-library/2010-05/<set>/<id>.html

`<set>` is the book/edition the page belongs to (see BOOK_RULES below and
corpus/README.md); the file name is the last segment of the page's
canonical URL (Web-archive pages are grouped by the set of the same topic id
when the page is known from the Corpus index, else under `unclassified`).

Scheduling / politeness (this is the important part)
----------------------------------------------------
  * One in-flight request per host, always.  Requests to a host are never
    parallelised (`--workers` only parallelises *different* hosts), so a
    single target site sees exactly the same sequential access pattern it
    would see from a single-threaded crawler.
  * Fixed delay between requests to the same host (learn: 0.4 s, archive.org:
    1.5 s), applied *before* the request from a per-host timer, plus jitter
    of up to half the delay.  Time spent writing files or running git counts
    towards the delay, which is why this is faster than sleeping after every
    response.
  * `robots.txt` of every host is fetched once per run and its `Disallow`
    rules are honoured (`--no-robots` to override, not recommended).
    learn.microsoft.com/robots.txt only disallows answer/search/api paths;
    the documentation namespace we harvest is allowed.
  * HTTP keep-alive connections are reused per host (no TLS handshake per
    page) -- this, the token-bucket pacing and the incremental index are what
    make a run fast; the request *rate* is unchanged.
  * On HTTP 429/503 the delay factor doubles every 5 consecutive hits (up to
    20x) and `Retry-After` is respected; it halves again after 20 clean
    responses.  Access volume only ever goes down, never up.

Resume
------
  * Pages already in the corpus are skipped using, in order of preference:
      1. `data/index/corpus.sqlite3` (fast, no tree walk),
      2. a filesystem scan (fallback, used when the DB is missing/stale).
  * Failed URLs are appended to `data/logs/fail-<queue>.log` and retried once
    at the end of the run at double delay.

Other flags
-----------
  --dry-run        report what would be fetched, touch nothing
  --limit N        stop after N queue lines
  --push           commit+push every --batch stored pages
  --workers N      parallel hosts (default 1 = strictly sequential)
  --respect-robots / --no-robots (default: respect)

Usage:
  python3 tools/harvest.py --queue queues/to-fetch-mslearn.txt [--limit N]
      [--delay S] [--batch 500] [--push] [--queue-name NAME]
"""

import argparse
import collections
import contextlib
import datetime as _dt
import gzip
import http.client
import json
import os
import random
import re
import socket
import subprocess
import threading
import time
import urllib.error
import urllib.parse
import urllib.request
import urllib.robotparser


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CORPUS = os.path.join(ROOT, "corpus")
LEARN_DIR = os.path.join(CORPUS, "learn")
WAYBACK_DIR = os.path.join(CORPUS, "msdn-library", "2010-05")
INDEX_DB = os.path.join(ROOT, "data", "index", "corpus.sqlite3")

UA = (
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
    "(KHTML, like Gecko) Chrome/124 Safari/537.36 "
    "wince-docs-corpus-harvester/2.0 (personal archival copy)"
)

# Number of queue lines loaded into memory at once.
CHUNK_SIZE = 1000

TITLE = re.compile(r"<title>(.*?)</title>", re.S)

BOOK_RULES = (
    (r"\(Windows CE \.NET[^)]*\)", "windows-ce-net-4x"),
    (r"\(Windows CE 5\.0\)", "windows-ce-5.0"),
    (r"\(Windows CE 4\.[12]\)", "windows-ce-net-4x"),
    (r"\(Windows CE 4\.0\)", "windows-ce-net-4x"),
    (r"\(Windows Embedded CE 6\.0[^)]*\)", "windows-embedded-ce-6.0"),
    (r"\(Windows CE 3\.0[^)]*\)", "windows-ce-3.0"),
    (r"\(Windows Mobile[^)]*\)", None),
    (r"\(Handheld PC[^)]*\)", "handheld-pc"),
    (r"\(Palm-size PC[^)]*\)", "palm-size-pc"),
    (r"\(Microsoft\.PointOfService[^)]*\)", "pos-for-net"),
    (
        r"\((?:Microsoft\.SPOT|Microsoft\.Web\.Services|"
        r"Microsoft\.NetMicroFramework|Ws|Dpws|System\.Ext)[^)]*\)",
        "dotnet-micro-framework",
    ),
    (r"\(Microsoft\.RemoteToolSdk[^)]*\)", "windows-embedded-ce-6.0"),
    (r"\(Compact 7\)", "windows-embedded-compact-7"),
    (
        r"\((System|Microsoft)(\.[A-Za-z0-9_.]+)?\)$",
        "dotnet-compact-framework",
    ),
    (
        r"\((?:[A-Za-z0-9_.]+ "
        r"(?:Method|Property|Constructor|Field|Event|Class|"
        r"Structure|Interface|Enumeration|Delegate))$",
        "dotnet-compact-framework",
    ),
)


def classify(title_text, body_head):
    """Map a learn previous-versions page to a book directory."""

    title_text = re.sub(
        r"\s*\|\s*Microsoft Learn\s*$",
        "",
        title_text,
    )

    for pattern, bucket in BOOK_RULES:
        match = re.search(pattern, title_text)

        if not match:
            continue

        if bucket is not None:
            return bucket

        wm = re.search(
            r"\(Windows Mobile ([0-9.]+)[^)]*\)",
            title_text,
        )

        if wm:
            return "windows-mobile-" + wm.group(1)

        return "windows-mobile"

    # Titles without a book marker:
    # fall back to body markers and use the earliest hit.
    best = "unclassified"
    best_index = 1 << 60

    for bucket, marker in (
        ("windows-ce-5.0", "Windows CE 5.0"),
        ("windows-embedded-ce-6.0", "Windows Embedded CE 6.0"),
        ("windows-ce-net-4x", "Windows CE .NET"),
    ):
        index = body_head.find(marker)

        if 0 <= index < best_index:
            best = bucket
            best_index = index

    return best


def dest_for(url):
    """Return (kind, page_id) for a queue URL."""

    p = urllib.parse.urlparse(url)

    if "learn.microsoft.com" in p.netloc:
        last = p.path.rstrip("/").split("/")[-1]

        match = re.match(
            r"([a-z0-9]+)\(v=([a-z0-9.]+)\)$",
            last,
        )

        if not match:
            return None, None

        return "learn", match.group(1)

    if "web.archive.org" in p.netloc:
        match = re.match(
            r"/web/(\d+)/https?://msdn\.microsoft\.com/en-us/library/"
            r"([a-z0-9]+)\.aspx$",
            p.path,
        )

        if not match:
            return None, None

        return "wayback", match.group(2)

    return None, None


# ---------------------------------------------------------------------------
# politeness: per-host pacing + robots.txt
# ---------------------------------------------------------------------------
class HostPacer:
    """One in-flight request per host, `delay` seconds apart.

    `slot()` is held for the whole request (not just the delay), which is
    what guarantees that a host never sees two concurrent requests even
    when `--workers` runs several hosts at once.  The delay is measured
    from the *start* of the previous request to this host, so the pace is
    `1/delay` requests per second per host regardless of how long the
    responses take.
    """

    def __init__(self):
        self._lock = threading.Lock()
        self._last = {}
        self._locks = collections.defaultdict(threading.Lock)

    def _host_lock(self, host):
        with self._lock:
            return self._locks[host]

    @contextlib.contextmanager
    def slot(self, host, delay):
        lock = self._host_lock(host)
        lock.acquire()
        try:
            while True:
                with self._lock:
                    now = time.monotonic()
                    last = self._last.get(host, 0.0)
                    wait = (delay + random.uniform(0, delay / 2.0)
                            - (now - last))
                    if wait <= 0:
                        self._last[host] = now
                        break
                time.sleep(min(wait, 1.0))
            yield
        finally:
            lock.release()


class Response:
    __slots__ = ("body", "status", "headers", "url")

    def __init__(self, body, status, headers, url):
        self.body = body
        self.status = status
        self.headers = headers
        self.url = url


class Fetcher:
    """Keep-alive HTTP(S) client with retry/back-off handling."""

    RETRY_STATUS = (429, 500, 502, 503, 504)
    REDIRECT_STATUS = (301, 302, 303, 307, 308)
    MAX_REDIRECTS = 5

    def __init__(self, pacer, respect_robots=True, timeout=60,
                 max_attempts=5, verbose=True):
        self.pacer = pacer
        self.respect_robots = respect_robots
        self.timeout = timeout
        self.max_attempts = max_attempts
        self.verbose = verbose
        self._conns = {}
        self._conn_lock = threading.Lock()
        self._robots = {}
        self._robots_lock = threading.Lock()
        self._throttle = {"consec": 0, "ok": 0, "factor": 1.0}
        self._throttle_lock = threading.Lock()
        self.stats = collections.Counter()
        self.stats_lock = threading.Lock()

    # -- connection handling ------------------------------------------------
    def _conn(self, scheme, host):
        key = (scheme, host)
        with self._conn_lock:
            conn = self._conns.get(key)
            if conn is None:
                if scheme == "https":
                    conn = http.client.HTTPSConnection(
                        host, timeout=self.timeout)
                else:
                    conn = http.client.HTTPConnection(
                        host, timeout=self.timeout)
                self._conns[key] = conn
            return conn

    def _drop(self, scheme, host):
        with self._conn_lock:
            conn = self._conns.pop((scheme, host), None)
        if conn is not None:
            try:
                conn.close()
            except Exception:  # noqa: BLE001
                pass

    def close(self):
        with self._conn_lock:
            conns, self._conns = self._conns, {}
        for conn in conns.values():
            try:
                conn.close()
            except Exception:  # noqa: BLE001
                pass

    # -- pacing -------------------------------------------------------------
    def delay_factor(self):
        with self._throttle_lock:
            return self._throttle["factor"]

    def _note_throttled(self):
        with self._throttle_lock:
            self._throttle["consec"] += 1
            self._throttle["ok"] = 0
            if self._throttle["consec"] % 5 == 0:
                self._throttle["factor"] = min(
                    self._throttle["factor"] * 2.0, 20.0)
                if self.verbose:
                    print(f"[throttle] consecutive rate-limit hits: "
                          f"{self._throttle['consec']} -> delay factor "
                          f"{self._throttle['factor']:.1f}x", flush=True)

    def _note_ok(self):
        with self._throttle_lock:
            self._throttle["consec"] = 0
            self._throttle["ok"] += 1
            if self._throttle["ok"] >= 20 and self._throttle["factor"] > 1.0:
                self._throttle["factor"] = max(
                    1.0, self._throttle["factor"] / 2.0)
                self._throttle["ok"] = 0

    # -- robots -------------------------------------------------------------
    def _robots_for(self, scheme, host):
        key = (scheme, host)
        with self._robots_lock:
            if key in self._robots:
                return self._robots[key]
        parser = urllib.robotparser.RobotFileParser()
        url = f"{scheme}://{host}/robots.txt"
        try:
            with self.pacer.slot(host, 0.0):
                resp = self._request(scheme, host, url, extra_headers=None)
            text = resp.body.decode("utf-8", "replace")
            parser.parse(text.splitlines())
        except Exception:  # noqa: BLE001
            parser = None                      # no robots.txt -> allowed
        with self._robots_lock:
            self._robots[key] = parser
        if self.verbose and parser is not None:
            print(f"[robots] {url}: loaded", flush=True)
        return parser

    def allowed(self, url):
        if not self.respect_robots:
            return True
        p = urllib.parse.urlparse(url)
        parser = self._robots_for(p.scheme, p.netloc)
        if parser is None:
            return True
        return parser.can_fetch(UA, url)

    # -- requests -----------------------------------------------------------
    def _request(self, scheme, host, url, extra_headers=None):
        path = urllib.parse.urlsplit(url).path or "/"
        query = urllib.parse.urlsplit(url).query
        if query:
            path += "?" + query
        headers = {
            "User-Agent": UA,
            "Accept": "text/html,application/xhtml+xml,application/xml;"
                      "q=0.9,*/*;q=0.8",
            "Accept-Encoding": "gzip",
            "Connection": "keep-alive",
        }
        if extra_headers:
            headers.update(extra_headers)
        conn = self._conn(scheme, host)
        try:
            conn.request("GET", path, headers=headers)
            resp = conn.getresponse()
        except (http.client.HTTPException, OSError):
            # stale keep-alive connection: reconnect once
            self._drop(scheme, host)
            conn = self._conn(scheme, host)
            conn.request("GET", path, headers=headers)
            resp = conn.getresponse()
        body = resp.read()
        if resp.getheader("Content-Encoding") == "gzip":
            body = gzip.decompress(body)
        if resp.will_close:
            self._drop(scheme, host)
        return Response(body, resp.status, dict(resp.getheaders()), url)

    def get(self, url, delay):
        """Fetch one URL. Returns (body|None, status_or_error)."""
        p = urllib.parse.urlparse(url)
        host = p.netloc
        last_err = None

        if not self.allowed(url):
            return None, "robots-disallow"

        hops = 0
        while True:
            # A redirect is not content: follow it (same host only, so the
            # per-host pacing and robots.txt still apply) instead of storing
            # the empty body the redirect carries.
            if not self.allowed(url):
                return None, "robots-disallow"
            p = urllib.parse.urlparse(url)
            host = p.netloc
            resp = None

            for attempt in range(self.max_attempts):
                with self.pacer.slot(host, delay * self.delay_factor()):
                    try:
                        resp = self._request(p.scheme, host, url)
                    except urllib.error.HTTPError as exc:  # pragma: no cover
                        last_err = str(exc)
                        resp = None
                    except Exception as exc:  # noqa: BLE001
                        last_err = str(exc)
                        resp = None

                if resp is not None:
                    break
                self._drop(p.scheme, host)
                time.sleep(3 * (attempt + 1))

            if resp is None:
                return None, last_err or "fetch-failed"

            with self.stats_lock:
                self.stats["requests"] += 1

            if resp.status in self.REDIRECT_STATUS:
                location = resp.headers.get("Location")
                hops += 1
                if not location:
                    return None, "redirect-without-location"
                if hops > self.MAX_REDIRECTS:
                    return None, "too-many-redirects"
                target = urllib.parse.urljoin(url, location)
                if urllib.parse.urlparse(target).netloc != host:
                    return None, "redirect-offsite"
                url = target
                continue

            if resp.status == 404:
                return None, 404
            if resp.status in self.RETRY_STATUS:
                self._note_throttled()
                retry_after = resp.headers.get("Retry-After")
                wait = int(retry_after) if (retry_after or "").isdigit() \
                    else 30 * (attempt + 1)
                time.sleep(min(wait, 300))
                continue
            if resp.status >= 400:
                last_err = f"HTTP {resp.status}"
                time.sleep(3 * (attempt + 1))
                continue

            with self.stats_lock:
                self.stats[f"status-{resp.status}"] += 1
            self._note_ok()
            if not resp.body.strip():
                # HTTP 200 with nothing in it: never store an empty page.
                return None, "empty-response"
            return resp.body, resp.status


# ---------------------------------------------------------------------------
# resume index
# ---------------------------------------------------------------------------
def load_index_ids(db_path):
    """Existing page ids from data/index/corpus.sqlite3, or None."""

    if not os.path.exists(db_path):
        return None
    try:
        import sqlite3

        con = sqlite3.connect(f"file:{db_path}?mode=ro", uri=True)
        ids = set()
        for (path,) in con.execute("SELECT path FROM pages"):
            fn = os.path.basename(path)
            stem = os.path.splitext(fn)[0]
            ids.add(stem)
            paren = stem.find("(v=")
            if paren > 0:
                ids.add(stem[:paren])
        con.close()
        return ids
    except Exception as exc:  # noqa: BLE001
        print(f"[index] sqlite index unusable ({exc}); falling back to scan")
        return None


def build_have_index(db_path=INDEX_DB, use_sqlite=True):
    """Set of page ids (and `wb:<id>` marks) already in the corpus."""

    have_ids = set()
    if use_sqlite:
        ids = load_index_ids(db_path)
        if ids is not None:
            have_ids |= ids
            # wayback pages carry the same page ids but a `wb:` marker is
            # only needed when they are stored under msdn-library/2010-05
            base = os.path.join(CORPUS, "msdn-library", "2010-05")
            if os.path.isdir(base):
                for dirpath, _dirnames, filenames in os.walk(base):
                    for fn in filenames:
                        if fn.endswith(".html"):
                            have_ids.add("wb:" + os.path.splitext(fn)[0])
            return have_ids

    for root, _dirs, files in ((LEARN_DIR, None, None),
                               (WAYBACK_DIR, None, None)):
        if not os.path.isdir(root):
            continue
        for dirpath, _dirnames, filenames in os.walk(root):
            for fn in filenames:
                if not fn.endswith(".html"):
                    continue
                base = fn[:-5]
                have_ids.add(base)
                paren = base.find("(v=")
                if paren > 0:
                    have_ids.add(base[:paren])
                if "msdn-library" in dirpath:
                    have_ids.add("wb:" + base)
    return have_ids


# ---------------------------------------------------------------------------
# git
# ---------------------------------------------------------------------------
def git(*args, check=True):
    return subprocess.run(
        ["git", "-C", ROOT, *args],
        check=check,
        capture_output=True,
        text=True,
    )


class GitBatcher:
    """Stage only the files a run wrote -- `git add corpus/` on a 170k-file
    worktree costs seconds per batch, `git add -- <paths>` costs millis."""

    def __init__(self, enabled, batch_size):
        self.enabled = enabled
        self.batch_size = batch_size
        self.pending = []
        self._lock = threading.Lock()

    def add(self, paths):
        if not self.enabled or not paths:
            return
        with self._lock:
            self.pending.extend(paths)

    def maybe_flush(self, force=False):
        if not self.enabled:
            return
        with self._lock:
            if not force and len(self.pending) < self.batch_size:
                return
        self.flush()

    def flush(self):
        if not self.pending:
            return
        paths, self.pending = self.pending, []
        git("config", "user.name", "wince-docs-corpus harvester", check=False)
        git("config", "user.email",
            "wince-corpus-harvester@users.noreply.github.com", check=False)
        for i in range(0, len(paths), 200):
            git("add", "--", *paths[i:i + 200], check=False)
        if git("diff", "--staged", "--quiet", check=False).returncode == 0:
            return
        timestamp = _dt.datetime.now(_dt.timezone.utc).strftime(
            "%Y-%m-%d %H:%M UTC")
        commit = git("commit", "-m",
                     f"corpus: harvest batch +{len(paths)} pages ({timestamp})",
                     check=False)
        if commit.returncode != 0:
            print(f"[push] commit failed: {commit.stderr.strip()[:200]}",
                  flush=True)
            return
        git("pull", "--rebase", check=False)
        result = git("push", check=False)
        if result.returncode == 0:
            print(f"[push] ok (+{len(paths)})", flush=True)
        else:
            print(f"[push] FAILED: {result.stderr.strip()[:200]}", flush=True)


# ---------------------------------------------------------------------------
# processing
# ---------------------------------------------------------------------------
# web.archive.org answers with an interstitial instead of the capture when the
# replay needs JavaScript ("Impatient? The Wayback Machine requires your
# browser to support JavaScript") or when the URL was never archived ("Hrm.
# The Wayback Machine has not archived that URL.").  Neither is documentation,
# so it is never stored; the harvester walks a few other capture dates first,
# because a page that replays as an interstitial at one timestamp often
# replays fine at another.
WAYBACK_BAD_MARKERS = (
    b"requires your browser to support JavaScript",
    b"Impatient? The Wayback Machine",
    b"has not archived that URL",
)
WAYBACK_FALLBACK_TIMESTAMPS = (
    "20050101000000", "20080101000000", "20110101000000", "20130101000000",
)


def wayback_bad(content):
    return any(marker in content for marker in WAYBACK_BAD_MARKERS)


AVAILABILITY_API = "https://archive.org/wayback/available"
WAYBACK_WRAPPER = re.compile(r"^https?://web\.archive\.org/web/[0-9]{14}[a-z_]*/")


def wayback_target(url):
    """https://web.archive.org/web/<ts>/<url> -> <url> (None if not wrapped)."""
    m = WAYBACK_WRAPPER.match(url)
    return url[m.end():] if m else None


def kind_is_wayback(queue_path):
    """True when the queue is a wayback-*.txt queue (its lines are captures)."""
    base = os.path.basename(queue_path)
    if base.startswith("wayback"):
        return True
    try:
        with open(queue_path, encoding="utf-8", errors="replace") as fh:
            for i, line in enumerate(fh):
                if i > 20:
                    break
                line = line.strip()
                if line.startswith("http"):
                    return "web.archive.org/web/" in line
    except OSError:
        return False
    return False


def known_wayback_answers():
    """What earlier runs learned, from data/reports/wayback-status.tsv.

    The file is committed, so a fresh runner starts with the answers from
    every run before it: a topic that the Internet Archive never captured is
    skipped without a single request, and a topic whose capture it does have
    is fetched from that capture instead of from the pinned URL.
    """
    dead, snapshots = set(), {}
    path = os.path.join(ROOT, "data", "reports", "wayback-status.tsv")
    if not os.path.exists(path):
        return dead, snapshots
    with open(path, encoding="utf-8") as fh:
        for line in fh:
            parts = line.rstrip("\n").split("\t")
            if len(parts) < 4 or parts[0] == "page_id":
                continue
            if parts[1] == "not-archived":
                dead.add(parts[0])
            elif parts[1] == "resolved" and parts[3]:
                snapshots[parts[0]] = parts[3]
    return dead, snapshots


def wayback_snapshot(fetcher, target, timestamp, cache):
    """Ask the availability API which snapshot of `target` really exists.

    The pinned form in the queue (`/web/20100501000000/<url>`) only works when
    the archive can redirect it to a capture; for a large part of the CE
    namespace the capture is stored under another scheme or date and the
    pinned request simply 404s.  The availability API answers with the exact
    capture URL (or nothing, which means the page was never archived).
    """
    key = (target, timestamp[:4])
    if key in cache:
        return cache[key]
    query = f"{AVAILABILITY_API}?url={urllib.parse.quote(target, safe='')}"
    if timestamp:
        query += f"&timestamp={timestamp}"
    body, status = fetcher.get(query, fetcher.base_delay)
    snapshot = None
    if body:
        try:
            data = json.loads(body.decode("utf-8", "replace"))
        except ValueError:
            data = {}
        closest = (data.get("archived_snapshots") or {}).get("closest") or {}
        if closest.get("available") and closest.get("url"):
            snapshot = closest["url"].replace("http://", "https://", 1)
    cache[key] = snapshot
    return snapshot


def wayback_retimestamp(url, timestamp):
    return re.sub(r"(/web/)\d{14}(/)", r"\g<1>" + timestamp + r"\g<2>",
                  url, count=1)


def store_page(content, path, page_id):
    final = os.path.join(path, page_id + ".html")
    temporary = final + ".part"
    os.makedirs(path, exist_ok=True)
    try:
        with open(temporary, "wb") as fh:
            fh.write(content)
        os.replace(temporary, final)
    except Exception:
        try:
            if os.path.exists(temporary):
                os.remove(temporary)
        except OSError:
            pass
        raise
    return final


def process_url(url, have_ids, faillog, fetcher, index_by_id, dry_run=False,
                wayback_retries=2, snapshot_cache=None, status_log=None,
                known_dead=None, known_snapshots=None, wayback_all=False):
    """Fetch and store one URL. Returns (result, written_path, detail)."""

    kind, pid = dest_for(url)

    if kind is None:
        return "invalid", None, "unrecognised-url"

    if kind == "learn":
        if pid in have_ids:
            return "skipped", None, ""
    else:
        if "wb:" + pid in have_ids:
            return "skipped", None, ""

    if kind == "wayback" and not wayback_all and pid in have_ids:
        # The topic is already in the corpus.  The 2010 MSDN Library topics
        # and the learn.microsoft.com "previous versions" pages are the same
        # documents id for id, so fetching the archive.org rendering would
        # store a duplicate (with the Wayback banner around it).  Skipping
        # here costs one set lookup instead of two requests.
        if status_log is not None:
            status_log.append((pid, "covered", ""))
        return "covered", None, "already-in-corpus"

    if dry_run:
        # No network access at all: report what would be fetched.
        return "would-fetch", None, ""

    if kind == "wayback" and known_dead and pid in known_dead:
        # An earlier run asked the availability API: no capture exists.
        return "not-archived", None, "known"

    fetch_url = url
    if kind == "wayback" and known_snapshots and pid in known_snapshots:
        fetch_url = known_snapshots[pid]

    content, status = fetcher.get(fetch_url, fetcher.base_delay)

    if content is None and kind == "wayback" and fetch_url == url:
        # The pinned capture date did not work.  Ask the availability API
        # where this topic really is, and fetch that capture instead.
        target = wayback_target(url)
        stamp = ""
        m = re.search(r"/web/(\d{14})/", url)
        if m:
            stamp = m.group(1)
        if target and snapshot_cache is not None:
            snapshot = wayback_snapshot(fetcher, target, stamp, snapshot_cache)
            if snapshot:
                content, status = fetcher.get(snapshot, fetcher.base_delay)
                if content is not None and wayback_bad(content):
                    content = None
                if content is not None and status_log is not None:
                    status_log.append((pid, "resolved", snapshot))
            else:
                if status_log is not None:
                    status_log.append((pid, "not-archived", ""))
                if faillog:
                    with open(faillog, "a", encoding="utf-8") as fh:
                        fh.write(f"not-archived\t{url}\n")
                return "not-archived", None, "not-archived"

    if content is None:
        if status == "robots-disallow":
            return "robots", None, status
        if faillog:
            with open(faillog, "a", encoding="utf-8") as fh:
                fh.write(f"{status}\t{url}\n")
        return "failed", None, str(status)

    if kind == "wayback" and wayback_bad(content):
        for timestamp in WAYBACK_FALLBACK_TIMESTAMPS[:wayback_retries]:
            other, _ = fetcher.get(wayback_retimestamp(url, timestamp),
                                   fetcher.base_delay)
            if other is not None and not wayback_bad(other):
                content = other
                break
        if wayback_bad(content):
            if faillog:
                with open(faillog, "a", encoding="utf-8") as fh:
                    fh.write(f"wayback-interstitial\t{url}\n")
            return "interstitial", None, "wayback-interstitial"

    head = content[:8000].decode("utf-8", "replace")
    match = TITLE.search(head)
    title = match.group(1).strip() if match else ""

    if kind == "learn":
        directory = os.path.join(LEARN_DIR, classify(title, head))
        stored_id = pid
    else:
        book = index_by_id.get(pid, "unclassified")
        directory = os.path.join(WAYBACK_DIR, book)
        stored_id = "wb:" + pid

    written = store_page(content, directory, pid)
    have_ids.add(stored_id)
    if kind == "wayback" and status_log is not None:
        status_log.append((pid, "stored", url))
    return "stored", written, ""


def iter_chunks(file_handle, chunk_size):
    chunk = []
    for line in file_handle:
        url = line.strip()
        if not url:
            continue
        chunk.append(url)
        if len(chunk) >= chunk_size:
            yield chunk
            chunk = []
    if chunk:
        yield chunk


def index_sets_by_id():
    """page id -> set directory, from the flat learn corpus."""

    index = {}
    for dirpath, _dirnames, filenames in os.walk(LEARN_DIR):
        book = os.path.basename(dirpath)
        for fn in filenames:
            if fn.endswith(".html"):
                index.setdefault(fn[:-5], book)
    return index


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--queue", required=True)
    ap.add_argument("--queue-name", default=None)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--delay", type=float, default=0.0)
    ap.add_argument("--batch", type=int, default=500)
    ap.add_argument("--push", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--workers", type=int, default=1,
                    help="parallel hosts (never parallelises one host)")
    ap.add_argument("--index-db", default=INDEX_DB)
    ap.add_argument("--no-index", action="store_true",
                    help="ignore data/index/corpus.sqlite3 and scan the tree")
    ap.add_argument("--no-robots", action="store_true",
                    help="do not consult robots.txt (not recommended)")
    ap.add_argument("--max-seconds", type=int, default=0, metavar="SECONDS",
                    help="stop fetching after this many seconds and finish "
                         "the run cleanly (0 = no budget); the queue resumes "
                         "where it stopped on the next run")
    ap.add_argument("--summary", metavar="FILE",
                    help="write a JSON run summary (counters, rate, delay) "
                         "here; used by the Actions workflow to report what "
                         "a run actually did")
    ap.add_argument("--wayback-all", action="store_true",
                    help="fetch every wayback topic, even ones the corpus "
                         "already covers")
    ap.add_argument("--wayback-retries", type=int, default=3,
                    help="other capture dates to try when archive.org "
                         "answers with an interstitial (default 3)")
    args = ap.parse_args()

    qpath = args.queue if os.path.isabs(args.queue) \
        else os.path.join(ROOT, args.queue)
    qname = args.queue_name or os.path.basename(qpath).replace(".txt", "")

    default_delay = {"wayback-msdn-2010": 1.5}.get(qname, 0.4)
    delay = args.delay if args.delay > 0 else default_delay

    logdir = os.path.join(ROOT, "data", "logs")
    os.makedirs(logdir, exist_ok=True)
    faillog = os.path.join(logdir, f"fail-{qname}.log")
    if args.dry_run:
        faillog = None

    started = _dt.datetime.now(_dt.timezone.utc)
    print(f"[{qname}] indexing existing documents...", flush=True)
    index_start = time.time()
    have_ids = build_have_index(args.index_db,
                                use_sqlite=not args.no_index)
    print(f"[{qname}] existing IDs={len(have_ids):,} "
          f"index_time={time.time() - index_start:.2f}s "
          f"(source={'sqlite' if not args.no_index else 'scan'})",
          flush=True)
    index_by_id = index_sets_by_id()

    pacer = HostPacer()
    fetcher = Fetcher(pacer, respect_robots=not args.no_robots)
    fetcher.base_delay = delay
    gitbatcher = GitBatcher(enabled=args.push and not args.dry_run,
                            batch_size=args.batch)

    counters = collections.Counter()
    counters_lock = threading.Lock()
    lines = 0
    t0 = time.time()
    stopped_early = False
    run_failures = []          # (status, url) for this run, capped below
    FAILURE_SAMPLE = 40
    snapshot_cache = {}
    status_log = []            # (page_id, status, snapshot_url) for wayback
    known_dead, known_snapshots = known_wayback_answers()
    if kind_is_wayback(qpath):
        print(f"[{qname}] wayback answers on file: "
              f"{len(known_dead):,} topics never archived, "
              f"{len(known_snapshots):,} resolved captures", flush=True)

    try:
        queue_file = open(qpath, "r", encoding="utf-8", errors="replace",
                          buffering=1024 * 1024)
    except OSError as exc:
        print(f"[{qname}] queue open failed: {exc}", flush=True)
        return 1

    def work(url):
        nonlocal lines
        result, written, detail = process_url(
            url, have_ids, faillog, fetcher, index_by_id,
            dry_run=args.dry_run, wayback_retries=args.wayback_retries,
            snapshot_cache=snapshot_cache, status_log=status_log,
            known_dead=known_dead, known_snapshots=known_snapshots,
            wayback_all=args.wayback_all)
        with counters_lock:
            counters[result] += 1
            lines += 1
            if detail and result in ("failed", "interstitial") \
                    and len(run_failures) < FAILURE_SAMPLE:
                run_failures.append({"status": detail, "url": url})
            if written:
                gitbatcher.add([written])
                gitbatcher.maybe_flush()
            if lines % 200 == 0 or result in ("stored", "would-fetch"):
                elapsed = max(time.time() - t0, 1)
                rate = (counters["stored"] or counters["would-fetch"]) \
                    / elapsed
                print(
                    f"[{qname}] lines={lines:,} "
                    f"stored={counters['stored']:,} "
                    f"would-fetch={counters['would-fetch']:,} "
                    f"skipped={counters['skipped']:,} "
                    f"failed={counters['failed']:,} "
                    f"fetched={fetched():,} "
                    f"rate={rate:.2f} pages/s", flush=True)

    def fetched():
        """Pages that cost a request (or would in --dry-run).

        `--limit` counts these, not queue lines: lines whose page is already
        stored are free, so successive runs walk forward through the queue
        instead of re-reading the same prefix.
        """
        return (counters["stored"] + counters["would-fetch"]
                + counters["failed"] + counters["interstitial"]
                + counters["not-archived"])

    def urls():
        nonlocal stopped_early
        with queue_file as fh:
            for chunk in iter_chunks(fh, CHUNK_SIZE):
                for url in chunk:
                    if args.limit and fetched() >= args.limit:
                        return
                    if args.max_seconds and time.time() - t0 >= args.max_seconds:
                        stopped_early = True
                        print(f"[{qname}] time budget of "
                              f"{args.max_seconds}s reached after "
                              f"{fetched():,} pages -- stopping cleanly",
                              flush=True)
                        return
                    yield url
                chunk.clear()

    if args.workers > 1:
        import concurrent.futures as cf

        print(f"[{qname}] {args.workers} workers "
              f"(one in-flight request per host, always)", flush=True)
        with cf.ThreadPoolExecutor(max_workers=args.workers) as pool:
            for _ in pool.map(work, urls(), chunksize=8):
                pass
    else:
        for url in urls():
            work(url)

    def write_wayback_status():
        """Append what this run learned about the queue's topics."""
        if not status_log or args.dry_run:
            return
        path = os.path.join(ROOT, "data", "reports", "wayback-status.tsv")
        os.makedirs(os.path.dirname(path), exist_ok=True)
        rows = {}
        if os.path.exists(path):
            with open(path, encoding="utf-8") as fh:
                for line in fh:
                    parts = line.rstrip("\n").split("\t")
                    if len(parts) >= 4 and parts[0] != "page_id":
                        rows[parts[0]] = parts
        now = _dt.datetime.now(_dt.timezone.utc).strftime("%Y-%m-%d %H:%M")
        for pid, status, snapshot in status_log:
            rows[pid] = [pid, status, now, snapshot]
        with open(path, "w", encoding="utf-8") as fh:
            fh.write("page_id\tstatus\tchecked\tsnapshot\n")
            for pid in sorted(rows):
                fh.write("\t".join(rows[pid]) + "\n")
        counts = collections.Counter(r[1] for r in rows.values())
        print(f"[{qname}] wayback-status.tsv: " + ", ".join(
            f"{k}={v:,}" for k, v in sorted(counts.items())), flush=True)

    def write_summary(elapsed=None):
        if not args.summary:
            return
        elapsed = elapsed if elapsed is not None else max(time.time() - t0, 1)
        summary = {
            "queue": os.path.relpath(qpath, ROOT),
            "queue_name": qname,
            "started": started.isoformat(timespec="seconds"),
            "finished": _dt.datetime.now(
                _dt.timezone.utc).isoformat(timespec="seconds"),
            "limit": args.limit,
            "delay_seconds": delay,
            "batch": args.batch,
            "push": bool(args.push),
            "dry_run": bool(args.dry_run),
            "lines": lines,
            "counters": dict(sorted(counters.items())),
            "requests": fetcher.stats["requests"],
            "stopped_early": stopped_early,
            "max_seconds": args.max_seconds,
            "failures": run_failures,
            "wayback_status": dict(sorted(collections.Counter(
                status for _pid, status, _snap in status_log).items())),
            "elapsed_seconds": round(elapsed, 1),
            "pages_per_second": round(counters["stored"] / elapsed, 3),
        }
        if faillog and os.path.exists(faillog):
            statuses = collections.Counter()
            with open(faillog, encoding="utf-8", errors="replace") as fh:
                for line in fh:
                    status = line.split("\t", 1)[0].strip()
                    if status:
                        statuses[status] += 1
            summary["fail_log"] = {
                "path": os.path.relpath(faillog, ROOT),
                "statuses": dict(sorted(statuses.items())),
            }
        path = args.summary if os.path.isabs(args.summary) \
            else os.path.join(ROOT, args.summary)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w", encoding="utf-8") as fh:
            json.dump(summary, fh, indent=2, sort_keys=False)
            fh.write("\n")
        print(f"[{qname}] summary -> {os.path.relpath(path, ROOT)} "
              f"(stored={counters['stored']:,})", flush=True)

    if args.dry_run:
        print(f"[{qname}] DRY RUN lines={lines:,} "
              f"would-fetch={counters['would-fetch']:,} "
              f"already-have={counters['skipped']:,} "
              f"covered={counters['covered']:,} "
              f"invalid={counters['invalid']:,}", flush=True)
        write_summary()
        return 0

    # ---- retry pass: everything that was not a hard 404 ------------------
    if counters["failed"] and faillog and os.path.exists(faillog):
        pending, keep = [], []
        with open(faillog, "r", encoding="utf-8") as fh:
            for ln in fh:
                parts = ln.rstrip("\n").split("\t", 1)
                if len(parts) == 2 and parts[0] not in (
                        "404", "wayback-interstitial", "not-archived"):
                    pending.append(parts[1])
                else:
                    keep.append(ln)
        if pending:
            print(f"[{qname}] retry pass: {len(pending)} URLs "
                  f"at {delay * 2:.1f}s delay", flush=True)
            still = []
            fetcher.base_delay = delay * 2
            for url in pending:
                if known_dead and dest_for(url)[1] in known_dead:
                    counters["not-archived"] += 1     # dead, no request spent
                    continue
                result, written, _detail = process_url(
                    url, have_ids, None, fetcher, index_by_id,
                    wayback_retries=args.wayback_retries,
                    snapshot_cache=snapshot_cache, status_log=status_log,
                    known_dead=known_dead, known_snapshots=known_snapshots,
                    wayback_all=args.wayback_all)
                if result == "stored":
                    counters["stored"] += 1
                    counters["failed"] -= 1
                    gitbatcher.add([written])
                else:
                    still.append(url)
            with open(faillog, "w", encoding="utf-8") as fh:
                fh.writelines(keep)
                for url in still:
                    fh.write(f"retry-failed\t{url}\n")

    gitbatcher.flush()
    fetcher.close()

    elapsed = max(time.time() - t0, 1)
    write_wayback_status()
    write_summary(elapsed)
    print(
        f"[{qname}] DONE lines={lines:,} stored={counters['stored']:,} "
        f"not-archived={counters['not-archived']:,} "
        f"covered={counters['covered']:,} "
        f"skipped={counters['skipped']:,} fails={counters['failed']:,} "
        f"invalid={counters['invalid']:,} robots={counters['robots']:,} "
        f"rate={counters['stored'] / elapsed:.2f} pages/s "
        f"requests={fetcher.stats['requests']:,}", flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
