#!/usr/bin/env python3
"""
Windows CE Documentation Harvester (harvest.py)

Reads URLs from urls.txt, fetches raw pages, and saves them under top-level directories based on host:
  - learn.microsoft.com -> MSLearn/
  - msdn.microsoft.com -> MSDN/
  - www.microsoft.com / microsoft.com -> Microsoft/
  - web.archive.org -> Wayback/
  - Other domains -> Other/

Features:
  - Domain-level concurrency: Independent target site categories (MSLearn, MSDN, Wayback, Microsoft) are processed in parallel threads.
  - Per-domain strict rate limits:
      - Wayback Machine (Internet Archive): 1.5s delay per request (prevents 429 rate limit triggers).
      - MS Learn & MSDN: 0.3s delay per request.
      - Microsoft main: 0.5s delay per request.
  - Batch commit & push: Periodically commits and pushes fetched data every N pages (default: 1000 pages)
    to prevent memory overflow, workflow timeouts, and GitHub payload/push size limit issues.
  - Automatic Exponential Backoff & Retry-After handling on HTTP 429 (Too Many Requests) or HTTP 503 errors.
  - Preserves URL directory structures, raw HTML, and metadata (.meta.json).
"""

import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
import threading
import time
import urllib.parse
import urllib.request
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime, timezone


# Investigated & documented domain-specific crawling delays (seconds)
DOMAIN_DELAYS = {
    "Wayback": 1.5,     # Internet Archive / Wayback Machine rate limit protection
    "MSLearn": 0.3,     # Microsoft Learn
    "MSDN": 0.3,        # MSDN
    "Microsoft": 0.5,   # Microsoft main site / downloads
    "Other": 0.5
}


def get_domain_category(url_parts):
    netloc = url_parts.netloc.lower()
    if "learn.microsoft.com" in netloc:
        return "MSLearn"
    elif "msdn.microsoft.com" in netloc:
        return "MSDN"
    elif "web.archive.org" in netloc:
        return "Wayback"
    elif "microsoft.com" in netloc:
        return "Microsoft"
    else:
        return "Other"


def url_to_filepath(url):
    """
    Map a full URL to a safe relative filepath under top-level directory.
    Includes query parameter hash if present to avoid filename collisions.
    """
    parsed = urllib.parse.urlparse(url)
    category = get_domain_category(parsed)

    path = parsed.path
    if not path or path.endswith("/"):
        path += "index.html"

    path = path.lstrip("/")

    base_dir, filename = os.path.split(path)
    if not os.path.splitext(filename)[1]:
        filename += ".html"

    if parsed.query:
        query_hash = hashlib.md5(parsed.query.encode("utf-8")).hexdigest()[:8]
        name, ext = os.path.splitext(filename)
        filename = f"{name}_{query_hash}{ext}"

    safe_filename = re.sub(r'[\\:*?"<>|]', '_', filename)
    safe_dir = re.sub(r'[\\:*?"<>|]', '_', base_dir)

    filepath = os.path.join(category, safe_dir, safe_filename)
    meta_path = filepath + ".meta.json"
    return filepath, meta_path


def is_valid_file(filepath, meta_path):
    """
    Check if the fetched data file exists and is valid (not empty / broken).
    """
    if not os.path.exists(filepath) or not os.path.exists(meta_path):
        return False

    if os.path.getsize(filepath) == 0 or os.path.getsize(meta_path) == 0:
        return False

    try:
        with open(meta_path, "r", encoding="utf-8") as f:
            meta = json.load(f)
            if meta.get("status_code") == 200 and os.path.exists(filepath):
                return True
    except Exception:
        return False

    return False


def fetch_url_with_retry(url, max_retries=3, timeout=15, user_agent=None):
    """
    Fetches raw content from public target URL with automatic Retry-After and exponential backoff for HTTP 429/503 errors.
    NOTE: Secret tokens (e.g. GITHUB_PAT) are NOT sent to external servers.
    """
    headers = {
        "User-Agent": user_agent or "Mozilla/5.0 (Windows CE Documentation Harvester)"
    }

    start_time = datetime.now(timezone.utc).isoformat()
    attempt = 0

    while attempt <= max_retries:
        attempt += 1
        req = urllib.request.Request(url, headers=headers)
        try:
            with urllib.request.urlopen(req, timeout=timeout) as resp:
                content = resp.read()
                status_code = resp.status
                headers_dict = dict(resp.headers)
                end_time = datetime.now(timezone.utc).isoformat()
                return {
                    "url": url,
                    "status_code": status_code,
                    "headers": headers_dict,
                    "start_time": start_time,
                    "end_time": end_time,
                    "content": content,
                    "error": None
                }
        except urllib.error.HTTPError as e:
            end_time = datetime.now(timezone.utc).isoformat()
            headers_dict = dict(e.headers) if e.headers else {}

            # Handle HTTP 429 (Too Many Requests) or HTTP 503 with Retry-After backoff
            if e.code in (429, 503) and attempt <= max_retries:
                retry_after = headers_dict.get("Retry-After")
                if retry_after and retry_after.isdigit():
                    wait_time = int(retry_after)
                else:
                    wait_time = 2 ** attempt * 2  # Exponential backoff: 4s, 8s, 16s...

                print(f"  [HTTP {e.code} Rate Limit] Retrying {url} in {wait_time}s (Attempt {attempt}/{max_retries})...")
                time.sleep(wait_time)
                continue

            try:
                content = e.read()
            except Exception:
                content = b""

            return {
                "url": url,
                "status_code": e.code,
                "headers": headers_dict,
                "start_time": start_time,
                "end_time": end_time,
                "content": content,
                "error": str(e)
            }
        except Exception as e:
            end_time = datetime.now(timezone.utc).isoformat()
            if attempt <= max_retries:
                time.sleep(2 * attempt)
                continue
            return {
                "url": url,
                "status_code": None,
                "headers": {},
                "start_time": start_time,
                "end_time": end_time,
                "content": b"",
                "error": str(e)
            }


def save_fetched_data(filepath, meta_path, res):
    os.makedirs(os.path.dirname(filepath), exist_ok=True)

    with open(filepath, "wb") as f:
        f.write(res["content"])

    meta = {
        "url": res["url"],
        "status_code": res["status_code"],
        "start_time": res["start_time"],
        "end_time": res["end_time"],
        "content_length": len(res["content"]),
        "error": res["error"],
        "headers": res["headers"]
    }
    with open(meta_path, "w", encoding="utf-8") as f:
        json.dump(meta, f, indent=2, ensure_ascii=False)


class BatchCommitManager:
    """
    Thread-safe manager that tracks fetched page counts across workers and performs
    git commit and git push every commit_interval pages to prevent GitHub payload size limits.
    """
    def __init__(self, commit_interval=1000, auto_push=False):
        self.commit_interval = commit_interval
        self.auto_push = auto_push
        self.counter = 0
        self.lock = threading.Lock()

    def record_page_fetched(self):
        if self.commit_interval <= 0:
            return

        with self.lock:
            self.counter += 1
            if self.counter >= self.commit_interval:
                self.counter = 0
                self.do_commit_and_push()

    def do_commit_and_push(self):
        print(f"\n[BatchCommitManager] Reached {self.commit_interval} pages batch milestone. Committing changes...")
        try:
            subprocess.run(["git", "config", "--global", "user.name", "github-actions[bot]"], check=False)
            subprocess.run(["git", "config", "--global", "user.email", "github-actions[bot]@users.noreply.github.com"], check=False)

            # Add harvested directories
            subprocess.run(["git", "add", "MSLearn/", "MSDN/", "Microsoft/", "Wayback/", "Other/"], check=False)

            # Check if there are staged changes
            diff_res = subprocess.run(["git", "diff", "--staged", "--quiet"])
            if diff_res.returncode != 0:
                commit_msg = f"chore: batch harvest snapshot ({datetime.now(timezone.utc).strftime('%Y-%m-%d %H:%M:%S UTC')})"
                subprocess.run(["git", "commit", "-m", commit_msg], check=True)
                print(f"[BatchCommitManager] Committed batch successfully.")

                if self.auto_push:
                    print("[BatchCommitManager] Pushing batch commit to GitHub repository...")
                    push_res = subprocess.run(["git", "push"])
                    if push_res.returncode == 0:
                        print("[BatchCommitManager] Batch push succeeded.")
                        # Pull with rebase if needed
                        subprocess.run(["git", "pull", "--rebase"], check=False)
                    else:
                        print("[BatchCommitManager] Batch push warning: failed to push batch commit.")
            else:
                print("[BatchCommitManager] No staged changes found for batch commit.")
        except Exception as e:
            print(f"[BatchCommitManager] Error during batch commit/push: {e}")


def harvest_domain_queue(category, domain_urls, delay, force, batch_manager):
    """
    Worker function to harvest URLs for a specific domain category sequentially with rate limiting.
    """
    print(f"[{category}] Worker started for {len(domain_urls)} URLs (domain rate limit delay={delay}s)...")
    success_count = 0
    skip_count = 0
    fail_count = 0

    total = len(domain_urls)
    for i, url in enumerate(domain_urls, start=1):
        filepath, meta_path = url_to_filepath(url)

        if not force and is_valid_file(filepath, meta_path):
            print(f"[{category}] [{i}/{total}] SKIPPED: {url}")
            skip_count += 1
            continue

        print(f"[{category}] [{i}/{total}] Fetching: {url}")
        res = fetch_url_with_retry(url)
        save_fetched_data(filepath, meta_path, res)

        if res["status_code"] == 200:
            print(f"[{category}] [{i}/{total}] -> SUCCESS (200 OK)")
            success_count += 1
        else:
            print(f"[{category}] [{i}/{total}] -> FAILED/HTTP {res['status_code']}: {res['error']}")
            fail_count += 1

        if batch_manager:
            batch_manager.record_page_fetched()

        if i < total and delay > 0:
            time.sleep(delay)

    print(f"[{category}] Worker completed. (Total: {total}, Skipped: {skip_count}, Success: {success_count}, Failed: {fail_count})")
    return {
        "category": category,
        "total": total,
        "skipped": skip_count,
        "success": success_count,
        "failed": fail_count
    }


def load_urls(urls_file):
    if not os.path.exists(urls_file):
        print(f"Error: {urls_file} does not exist.", file=sys.stderr)
        return []

    urls = []
    with open(urls_file, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith("#"):
                urls.append(line)
    return urls


def main():
    parser = argparse.ArgumentParser(description="Harvest Windows CE documentation pages.")
    parser.add_argument("--urls-file", default="urls.txt", help="Path to URL list file (default: urls.txt)")
    parser.add_argument("--delay", type=float, default=None, help="Override default delay in seconds between requests per domain")
    parser.add_argument("--limit", type=int, default=0, help="Limit maximum number of URLs to process (0 = no limit)")
    parser.add_argument("--force", action="store_true", help="Force re-fetching existing valid files")
    parser.add_argument("--commit-interval", type=int, default=1000, help="Number of pages per batch git commit & push (default: 1000, 0 = disable)")
    parser.add_argument("--auto-push", action="store_true", help="Automatically git push after each batch commit")
    args = parser.parse_args()

    urls = load_urls(args.urls_file)
    if not urls:
        print("No URLs found to harvest.")
        return

    if args.limit > 0:
        urls = urls[:args.limit]

    # Group URLs by domain category
    domain_queues = {}
    for url in urls:
        parsed = urllib.parse.urlparse(url)
        cat = get_domain_category(parsed)
        domain_queues.setdefault(cat, []).append(url)

    print(f"Starting domain-parallel harvest for {len(urls)} total URLs across {len(domain_queues)} domain categories...")
    for cat, q in domain_queues.items():
        delay = args.delay if args.delay is not None else DOMAIN_DELAYS.get(cat, 0.5)
        print(f"  - Category '{cat}': {len(q)} URLs (Delay: {delay}s)")

    batch_manager = BatchCommitManager(commit_interval=args.commit_interval, auto_push=args.auto_push)

    # Execute domain workers concurrently
    results = []
    with ThreadPoolExecutor(max_workers=len(domain_queues)) as executor:
        futures = []
        for cat, q in domain_queues.items():
            delay = args.delay if args.delay is not None else DOMAIN_DELAYS.get(cat, 0.5)
            futures.append(executor.submit(harvest_domain_queue, cat, q, delay, args.force, batch_manager))

        for future in futures:
            results.append(future.result())

    # Final commit for remaining items
    if args.commit_interval > 0:
        print("\nPerforming final batch commit/push for remaining pages...")
        batch_manager.do_commit_and_push()

    print("\nHarvest Summary Across All Domains:")
    total_processed = sum(r["total"] for r in results)
    total_skipped = sum(r["skipped"] for r in results)
    total_success = sum(r["success"] for r in results)
    total_failed = sum(r["failed"] for r in results)

    print(f"  Total processed: {total_processed}")
    print(f"  Skipped: {total_skipped}")
    print(f"  Successfully fetched: {total_success}")
    print(f"  Failed / HTTP Errors: {total_failed}")


if __name__ == "__main__":
    main()
