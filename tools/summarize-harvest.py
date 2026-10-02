#!/usr/bin/env python3
"""Turn a ``tools/harvest.py --summary`` file into a run history row.

    python3 tools/summarize-harvest.py                    # uses the defaults
    python3 tools/summarize-harvest.py --summary X.json --history data/reports/harvest-history.tsv

Prints a one-line result and appends a row to the history TSV, so
``data/reports/harvest-history.tsv`` becomes the record of what each Actions
run (or local run) harvested.  The workflow calls this after every run.
"""

import argparse
import json
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SUMMARY = "data/reports/harvest-last.json"
HISTORY = "data/reports/harvest-history.tsv"

COLUMNS = ("finished", "queue", "lines", "stored", "skipped", "covered",
           "not_archived", "failed", "invalid", "robots", "interstitial",
           "requests", "elapsed_seconds")
# counters in data/reports/harvest-last.json are hyphenated
COUNTER_KEY = {"covered": "covered", "not_archived": "not-archived"}


def migrate_header(path):
    """Rewrite an older history file so every row has today's columns."""
    with open(path, encoding="utf-8") as fh:
        lines = fh.read().splitlines()
    if not lines:
        return
    header = lines[0].split("\t")
    if header == list(COLUMNS):
        return
    rows = []
    for line in lines[1:]:
        record = dict(zip(header, line.split("\t")))
        rows.append("\t".join(record.get(col, "0" if col in COLUMNS
                                          and col not in ("finished", "queue")
                                          else "")
                              for col in COLUMNS))
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("\t".join(COLUMNS) + "\n")
        for row in rows:
            fh.write(row + "\n")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--summary", default=SUMMARY)
    ap.add_argument("--history", default=HISTORY)
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    summary_path = args.summary if os.path.isabs(args.summary) \
        else os.path.join(ROOT, args.summary)
    if not os.path.exists(summary_path):
        print(f"no summary at {args.summary} (run never started?)")
        return 0

    with open(summary_path, encoding="utf-8") as fh:
        data = json.load(fh)
    counters = data.get("counters", {})
    row = {key: counters.get(COUNTER_KEY.get(key, key), 0) for key in COLUMNS}
    for key in COLUMNS:
        if key in data:                  # queue, lines, requests, elapsed, ...
            row[key] = data[key]
        elif key in counters:
            row[key] = counters[key]

    history_path = args.history if os.path.isabs(args.history) \
        else os.path.join(ROOT, args.history)
    os.makedirs(os.path.dirname(history_path), exist_ok=True)
    new = not os.path.exists(history_path)
    if not new:
        migrate_header(history_path)
    with open(history_path, "a", encoding="utf-8") as fh:
        if new:
            fh.write("\t".join(COLUMNS) + "\n")
        fh.write("\t".join(str(row.get(col, "")) for col in COLUMNS) + "\n")

    if not args.quiet:
        fails = data.get("fail_log", {}).get("statuses") or {}
        print(f"{data.get('queue')}: stored={row['stored']} "
              f"skipped={row['skipped']} covered={row['covered']} "
              f"not-archived={row['not_archived']} failed={row['failed']} "
              f"interstitial={row['interstitial']} "
              f"requests={row['requests']} "
              f"elapsed={row['elapsed_seconds']}s")
        if fails:
            print("failure reasons: " + ", ".join(
                f"{k}={v}" for k, v in sorted(fails.items())))
        if not row["stored"] and row["skipped"]:
            print("note: nothing new -- the queue may be exhausted")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
