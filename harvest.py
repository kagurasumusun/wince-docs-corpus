#!/usr/bin/env python3
"""
Windows CE Documentation Harvester (harvest.py)

Reads URLs from urls.txt, fetches raw pages, and saves them under top-level directories based on host:
  - learn.microsoft.com -> MSLearn/
  - msdn.microsoft.com -> MSDN/
  - www.microsoft.com / microsoft.com -> Microsoft/
  - web.archive.org -> Wayback/
  - Other domains -> Other/

Preserves URL structure for directories and saves raw HTML files alongside JSON metadata (.meta.json).
Handles skipping existing valid files, re-fetching incomplete files, sequential delay, and error logging.
"""

import argparse
import hashlib
import json
import os
import re
import sys
import time
import urllib.parse
import urllib.request
from datetime import datetime, timezone


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
    Example:
      https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ee498596(v=winembedded.60)
      -> MSLearn/en-us/previous-versions/windows/embedded/ee498596(v=winembedded.60).html
    """
    parsed = urllib.parse.urlparse(url)
    category = get_domain_category(parsed)

    path = parsed.path
    if not path or path.endswith("/"):
        path += "index.html"

    # Remove leading slash
    path = path.lstrip("/")

    base_dir, filename = os.path.split(path)
    if not os.path.splitext(filename)[1]:
        filename += ".html"

    # If query parameters exist, append a short hash to filename to prevent collision
    if parsed.query:
        query_hash = hashlib.md5(parsed.query.encode("utf-8")).hexdigest()[:8]
        name, ext = os.path.splitext(filename)
        filename = f"{name}_{query_hash}{ext}"

    # Sanitize invalid filename characters while remaining recognizable
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


def fetch_url(url, timeout=15, user_agent=None):
    """
    Fetches raw content from public target URL.
    NOTE: Secret tokens (e.g. GITHUB_PAT) are NOT sent to external servers.
    """
    headers = {
        "User-Agent": user_agent or "Mozilla/5.0 (Windows CE Documentation Harvester)"
    }

    req = urllib.request.Request(url, headers=headers)
    start_time = datetime.now(timezone.utc).isoformat()
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
        try:
            content = e.read()
        except Exception:
            content = b""
        return {
            "url": url,
            "status_code": e.code,
            "headers": dict(e.headers) if e.headers else {},
            "start_time": start_time,
            "end_time": end_time,
            "content": content,
            "error": str(e)
        }
    except Exception as e:
        end_time = datetime.now(timezone.utc).isoformat()
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
    parser.add_argument("--delay", type=float, default=0.5, help="Delay in seconds between requests (default: 0.5)")
    parser.add_argument("--limit", type=int, default=0, help="Limit maximum number of URLs to process (0 = no limit)")
    parser.add_argument("--force", action="store_true", help="Force re-fetching existing valid files")
    args = parser.parse_args()

    urls = load_urls(args.urls_file)
    if not urls:
        print("No URLs found to harvest.")
        return

    if args.limit > 0:
        urls = urls[:args.limit]

    print(f"Starting harvest for {len(urls)} URLs...")
    success_count = 0
    skip_count = 0
    fail_count = 0

    for i, url in enumerate(urls, start=1):
        filepath, meta_path = url_to_filepath(url)

        if not args.force and is_valid_file(filepath, meta_path):
            print(f"[{i}/{len(urls)}] SKIPPED (already fetched): {url}")
            skip_count += 1
            continue

        print(f"[{i}/{len(urls)}] Fetching: {url}")
        res = fetch_url(url)

        save_fetched_data(filepath, meta_path, res)

        if res["status_code"] == 200:
            print(f"  -> SUCCESS (200 OK) -> Saved to {filepath}")
            success_count += 1
        else:
            print(f"  -> FAILED/HTTP {res['status_code']}: {res['error']} -> Saved metadata to {meta_path}")
            fail_count += 1

        if i < len(urls) and args.delay > 0:
            time.sleep(args.delay)

    print("\nHarvest Summary:")
    print(f"  Total processed: {len(urls)}")
    print(f"  Skipped: {skip_count}")
    print(f"  Successfully fetched: {success_count}")
    print(f"  Failed / HTTP Errors: {fail_count}")


if __name__ == "__main__":
    main()
