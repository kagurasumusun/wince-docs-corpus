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

COLUMNS = ("finished", "queue", "lines", "stored", "skipped", "failed",
           "invalid", "robots", "interstitial", "requests", "elapsed_seconds")


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
    row = {key: counters.get(key, 0) for key in COLUMNS}
    row.update({key: data.get(key, "") for key in COLUMNS})

    history_path = args.history if os.path.isabs(args.history) \
        else os.path.join(ROOT, args.history)
    os.makedirs(os.path.dirname(history_path), exist_ok=True)
    new = not os.path.exists(history_path)
    with open(history_path, "a", encoding="utf-8") as fh:
        if new:
            fh.write("\t".join(COLUMNS) + "\n")
        fh.write("\t".join(str(row.get(col, "")) for col in COLUMNS) + "\n")

    if not args.quiet:
        print(f"{data.get('queue')}: stored={row['stored']} "
              f"skipped={row['skipped']} failed={row['failed']} "
              f"interstitial={row['interstitial']} "
              f"requests={row['requests']} "
              f"elapsed={row['elapsed_seconds']}s")
        if not row["stored"] and row["skipped"]:
            print("note: nothing new -- the queue may be exhausted")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
