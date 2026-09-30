#!/usr/bin/env python3
"""tools/harvest.py -- rate-limited Windows CE documentation harvester.

Fetches pages from a URL queue file into the corpus hierarchy:

  learn.microsoft.com/.../previous-versions/windows/embedded/<id>(v=tag)
        -> docs/mslearn/<book>/<id>.html

  web.archive.org/web/20100501000000/https://msdn.microsoft.com/en-us/library/<id>.aspx
        -> docs/wayback-msdn/2010-05/<id>.html

Policy (repo AGENTS.md):
  * Polite sequential fetching only -- one in-flight request per target
    site, fixed delay between requests
    (learn: 0.4 s, archive.org: 1.5 s).
  * Only official Microsoft public documentation is collected.
  * Resume-safe: pages already stored are skipped.
  * Batch commit & push every --batch pages (default 500) when --push.

Performance:
  * Queue TXT is processed in chunks of 1000 lines.
  * The entire URL queue is never loaded into memory.
  * Existing document IDs are indexed once at startup.
  * os.scandir() is used for faster filesystem traversal.
  * Failure count is tracked incrementally instead of rereading the log.

Usage:
  python3 tools/harvest.py --queue urls/to-fetch-mslearn.txt [--limit N]
      [--delay S] [--batch 500] [--push] [--queue-name NAME]
"""

import argparse
import datetime as _dt
import os
import random
import re
import subprocess
import time
import urllib.error
import urllib.parse
import urllib.request


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

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
    best = "uncategorized"
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


# Adaptive rate-limit state: consecutive 429/503 responses multiply
# the inter-request delay (never below the configured base delay, so
# total access volume only ever goes DOWN, never up).
_THROTTLE = {"consec": 0, "ok": 0, "factor": 1.0}


def throttle_sleep_seconds(base_delay):
    """Delay to sleep after one processed URL."""
    return base_delay * _THROTTLE["factor"] + random.uniform(0, base_delay / 2.0)


def note_throttled():
    _THROTTLE["consec"] += 1
    _THROTTLE["ok"] = 0
    if _THROTTLE["consec"] % 5 == 0:
        _THROTTLE["factor"] = min(_THROTTLE["factor"] * 2.0, 20.0)
        print(
            f"[throttle] consecutive rate-limit hits: "
            f"{_THROTTLE['consec']} -> delay factor "
            f"{_THROTTLE['factor']:.1f}x",
            flush=True,
        )


def note_ok():
    _THROTTLE["consec"] = 0
    _THROTTLE["ok"] += 1
    if _THROTTLE["ok"] >= 20 and _THROTTLE["factor"] > 1.0:
        _THROTTLE["factor"] = max(1.0, _THROTTLE["factor"] / 2.0)
        _THROTTLE["ok"] = 0


def fetch(url, timeout=60, max_attempts=5):
    """Fetch one URL with retry handling."""

    last_err = None

    for attempt in range(max_attempts):
        req = urllib.request.Request(
            url,
            headers={"User-Agent": UA},
        )

        try:
            with urllib.request.urlopen(req, timeout=timeout) as resp:
                body = resp.read()
                note_ok()
                return body, resp.status

        except urllib.error.HTTPError as exc:
            if exc.code == 404:
                return None, 404

            if exc.code in (429, 503):
                note_throttled()
                retry_after = exc.headers.get("Retry-After")

                if (retry_after or "").isdigit():
                    wait = int(retry_after)
                else:
                    wait = 30 * (attempt + 1)

                # Respect the server's backoff request; only cap very
                # long values so a single URL cannot eat the runner.
                time.sleep(min(wait, 300))
                continue

            last_err = str(exc)

        except Exception as exc:  # noqa: BLE001
            last_err = str(exc)

        time.sleep(3 * (attempt + 1))

    return None, last_err or "fetch-failed"


def git(*args, check=True):
    """Run git inside repository root."""

    return subprocess.run(
        ["git", "-C", ROOT, *args],
        check=check,
        capture_output=True,
        text=True,
    )


def commit_push(batch):
    """Commit and push the current batch."""

    git(
        "config",
        "user.name",
        "wince-docs-corpus harvester",
        check=False,
    )

    git(
        "config",
        "user.email",
        "wince-corpus-harvester@users.noreply.github.com",
        check=False,
    )

    git(
        "add",
        "docs/",
        "data/index/",
        "data/harvest/",
        check=False,
    )

    if git(
        "diff",
        "--staged",
        "--quiet",
        check=False,
    ).returncode == 0:
        return

    timestamp = _dt.datetime.now(
        _dt.timezone.utc
    ).strftime("%Y-%m-%d %H:%M UTC")

    commit = git(
        "commit",
        "-m",
        f"corpus: harvest batch +{batch} pages ({timestamp})",
        check=False,
    )

    if commit.returncode != 0:
        print(
            f"[push] commit failed: "
            f"{commit.stderr.strip()[:200]}",
            flush=True,
        )
        return

    git(
        "pull",
        "--rebase",
        check=False,
    )

    result = git(
        "push",
        check=False,
    )

    if result.returncode == 0:
        print(
            f"[push] ok (+{batch})",
            flush=True,
        )
    else:
        print(
            f"[push] FAILED: "
            f"{result.stderr.strip()[:200]}",
            flush=True,
        )


def build_have_index():
    """Build an index of already harvested document IDs.

    Returns:
        set[str]: Existing IDs.
    """

    have_ids = set()

    # ------------------------------------------------------------------
    # Microsoft Learn
    # ------------------------------------------------------------------

    ms_root = os.path.join(
        ROOT,
        "docs",
        "mslearn",
    )

    if os.path.isdir(ms_root):
        try:
            with os.scandir(ms_root) as books:
                for book_entry in books:
                    if not book_entry.is_dir():
                        continue

                    try:
                        with os.scandir(book_entry.path) as files:
                            for file_entry in files:
                                if not file_entry.is_file():
                                    continue

                                name = file_entry.name

                                if not name.endswith(".html"):
                                    continue

                                base = name[:-5]
                                have_ids.add(base)

                                # Versioned filename:
                                #
                                # aa450192(v=msdn.10).html
                                #
                                # Queue ID:
                                #
                                # aa450192
                                #
                                paren = base.find("(v=")

                                if paren > 0:
                                    have_ids.add(base[:paren])

                    except OSError:
                        continue

        except OSError:
            pass

    # ------------------------------------------------------------------
    # Wayback MSDN
    # ------------------------------------------------------------------

    wb_dir = os.path.join(
        ROOT,
        "docs",
        "wayback-msdn",
        "2010-05",
    )

    if os.path.isdir(wb_dir):
        try:
            with os.scandir(wb_dir) as files:
                for file_entry in files:
                    if not file_entry.is_file():
                        continue

                    name = file_entry.name

                    if name.endswith(".html"):
                        have_ids.add(
                            "wb:" + name[:-5]
                        )

        except OSError:
            pass

    return have_ids


def process_url(
    url,
    have_ids,
    faillog,
    delay,
):
    """Process one URL.

    Returns:
        "stored"
        "skipped"
        "failed"
        "invalid"
    """

    kind, pid = dest_for(url)

    if kind is None:
        return "invalid"

    if kind == "learn":
        if pid in have_ids:
            return "skipped"

    else:
        wb_id = "wb:" + pid

        if wb_id in have_ids:
            return "skipped"

    content, status = fetch(url)

    if content is None:
        with open(
            faillog,
            "a",
            encoding="utf-8",
        ) as fh:
            fh.write(
                f"{status}\t{url}\n"
            )

        return "failed"

    # Only decode a small part of the response.
    head = content[:8000].decode(
        "utf-8",
        "replace",
    )

    match = TITLE.search(head)

    title = (
        match.group(1).strip()
        if match
        else ""
    )

    if kind == "learn":
        book = classify(
            title,
            head,
        )

        directory = os.path.join(
            ROOT,
            "docs",
            "mslearn",
            book,
        )

        stored_id = pid

    else:
        directory = os.path.join(
            ROOT,
            "docs",
            "wayback-msdn",
            "2010-05",
        )

        stored_id = "wb:" + pid

    os.makedirs(
        directory,
        exist_ok=True,
    )

    final = os.path.join(
        directory,
        pid + ".html",
    )

    temporary = final + ".part"

    try:
        with open(
            temporary,
            "wb",
        ) as fh:
            fh.write(content)

        # Atomic replacement.
        os.replace(
            temporary,
            final,
        )

    except Exception:
        # Do not leave .part files behind if possible.
        try:
            if os.path.exists(temporary):
                os.remove(temporary)
        except OSError:
            pass

        raise

    have_ids.add(stored_id)

    time.sleep(throttle_sleep_seconds(delay))

    return "stored"


def iter_chunks(file_handle, chunk_size):
    """Yield non-empty queue lines in chunks.

    The queue file itself is never loaded entirely into memory.
    """

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


def main():
    ap = argparse.ArgumentParser()

    ap.add_argument(
        "--queue",
        required=True,
    )

    ap.add_argument(
        "--queue-name",
        default=None,
    )

    ap.add_argument(
        "--limit",
        type=int,
        default=0,
    )

    ap.add_argument(
        "--delay",
        type=float,
        default=0.0,
    )

    ap.add_argument(
        "--batch",
        type=int,
        default=500,
    )

    ap.add_argument(
        "--push",
        action="store_true",
    )

    args = ap.parse_args()

    qpath = (
        args.queue
        if os.path.isabs(args.queue)
        else os.path.join(
            ROOT,
            args.queue,
        )
    )

    qname = (
        args.queue_name
        or os.path.basename(qpath).replace(
            ".txt",
            "",
        )
    )

    default_delay = {
        "wayback-msdn-2010": 1.5,
    }.get(
        qname,
        0.4,
    )

    delay = (
        args.delay
        if args.delay > 0
        else default_delay
    )

    logdir = os.path.join(
        ROOT,
        "data",
        "harvest",
    )

    os.makedirs(
        logdir,
        exist_ok=True,
    )

    faillog = os.path.join(
        logdir,
        f"fail-{qname}.log",
    )

    # --------------------------------------------------------------
    # Build resume index once.
    # --------------------------------------------------------------

    print(
        f"[{qname}] indexing existing documents...",
        flush=True,
    )

    index_start = time.time()

    have_ids = build_have_index()

    index_time = time.time() - index_start

    print(
        f"[{qname}] existing IDs={len(have_ids):,} "
        f"index_time={index_time:.2f}s",
        flush=True,
    )

    # --------------------------------------------------------------
    # Counters
    # --------------------------------------------------------------

    lines = 0
    stored = 0
    skipped = 0
    failed = 0
    invalid = 0

    since_batch = 0

    t0 = time.time()

    # --------------------------------------------------------------
    # Process queue in 1000-line chunks.
    # --------------------------------------------------------------

    try:
        queue_file = open(
            qpath,
            "r",
            encoding="utf-8",
            errors="replace",
            buffering=1024 * 1024,
        )
    except OSError as exc:
        print(
            f"[{qname}] queue open failed: {exc}",
            flush=True,
        )
        return 1

    with queue_file as fh:
        for chunk in iter_chunks(
            fh,
            CHUNK_SIZE,
        ):
            # Respect --limit without reading more chunks.
            if args.limit:
                remaining = args.limit - lines

                if remaining <= 0:
                    break

                if len(chunk) > remaining:
                    chunk = chunk[:remaining]

            # ------------------------------------------------------
            # Process this 1000-line chunk.
            # ------------------------------------------------------

            for url in chunk:
                lines += 1

                result = process_url(
                    url,
                    have_ids,
                    faillog,
                    delay,
                )

                if result == "stored":
                    stored += 1
                    since_batch += 1

                elif result == "skipped":
                    skipped += 1

                elif result == "failed":
                    failed += 1

                else:
                    invalid += 1

                # Progress output.
                #
                # Avoid printing every single URL because stdout itself
                # can become a noticeable bottleneck.
                if lines % 200 == 0:
                    elapsed = max(
                        time.time() - t0,
                        1,
                    )

                    rate = stored / elapsed

                    print(
                        f"[{qname}] "
                        f"lines={lines:,} "
                        f"stored={stored:,} "
                        f"skipped={skipped:,} "
                        f"failed={failed:,} "
                        f"rate={rate:.2f} pages/s",
                        flush=True,
                    )

                # --------------------------------------------------
                # Batch commit/push.
                # --------------------------------------------------

                if (
                    args.push
                    and since_batch >= args.batch
                ):
                    commit_push(
                        since_batch,
                    )

                    since_batch = 0

            # Release the chunk before reading the next 1000 lines.
            chunk.clear()

            # ------------------------------------------------------
            # Chunk progress.
            # ------------------------------------------------------

            elapsed = max(
                time.time() - t0,
                1,
            )

            rate = stored / elapsed

            print(
                f"[{qname}] chunk done "
                f"lines={lines:,} "
                f"stored={stored:,} "
                f"skipped={skipped:,} "
                f"failed={failed:,} "
                f"rate={rate:.2f} pages/s",
                flush=True,
            )

            if (
                args.limit
                and lines >= args.limit
            ):
                break

    # --------------------------------------------------------------
    # Retry pass: failures that were not hard 404s get one more
    # attempt at double delay (sequential; no extra concurrency).
    # --------------------------------------------------------------

    if failed and os.path.exists(faillog):
        pending = []
        keep = []
        with open(faillog, "r", encoding="utf-8") as fh:
            for ln in fh:
                parts = ln.rstrip("\n").split("\t", 1)
                if len(parts) == 2 and parts[0] != "404":
                    pending.append(parts[1])
                else:
                    keep.append(ln)
        if pending:
            print(
                f"[{qname}] retry pass: {len(pending)} URLs "
                f"at {delay * 2:.1f}s delay",
                flush=True,
            )
            still = []
            for url in pending:
                result = process_url(
                    url,
                    have_ids,
                    os.devnull,
                    delay * 2,
                )
                if result == "stored":
                    stored += 1
                    since_batch += 1
                    failed -= 1
                else:
                    still.append(url)
                time.sleep(throttle_sleep_seconds(delay * 2))
            with open(faillog, "w", encoding="utf-8") as fh:
                fh.writelines(keep)
                for url in still:
                    fh.write(f"retry-failed\t{url}\n")

    # --------------------------------------------------------------
    # Final batch.
    # --------------------------------------------------------------

    if args.push and since_batch:
        commit_push(
            since_batch,
        )

    elapsed = max(
        time.time() - t0,
        1,
    )

    rate = stored / elapsed

    print(
        f"[{qname}] DONE "
        f"lines={lines:,} "
        f"stored={stored:,} "
        f"skipped={skipped:,} "
        f"fails={failed:,} "
        f"invalid={invalid:,} "
        f"rate={rate:.2f} pages/s",
        flush=True,
    )

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
