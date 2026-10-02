# queues/

URL lists consumed by `tools/harvest.py` (`--queue queues/<file>`). One URL per
line; blank lines and lines that don't match a supported URL shape are counted
as `invalid` and skipped.

| File | Lines | Target |
|------|------:|--------|
| `to-fetch-mslearn.txt` | 31,635 | `learn.microsoft.com/en-us/previous-versions/windows/embedded/<id>(v=…)` — the current harvest queue. |
| `mslearn-embedded.txt` | 38,726 | The original full enumeration of the same namespace (superset; first line is the namespace root). |
| `wayback-msdn-2010.txt` | 31,388 | `web.archive.org/web/20100501000000/https://msdn.microsoft.com/en-us/library/<id>.aspx` — the May 2010 MSDN Library snapshot. |
| `auto-harvest.txt` | 1 | Not a URL queue: the budget the daily automatic run reads (`<queue> <pages per run> [batch]`, or `off`). See below. |
| `rejected-third-party-sources.txt` | 4 | Candidate sources that are **not** harvested: the collection policy is official Microsoft documentation only. Kept as a record of what was deliberately left out (a GitHub mirror, two vendor/community sites and one blog post). |

## Automatic run (`queues/auto-harvest.txt`)

`.github/workflows/harvest.yml` also runs on a schedule: every day at 18:00 UTC
(03:00 JST) it harvests the queue named in `queues/auto-harvest.txt`, up to the
page budget on that line, then refreshes the indexes and commits. The same run
starts whenever that file changes, which makes editing it the quickest way to
start one — and `off` stops the automatic runs.

What each run did is committed as well: `data/reports/harvest-last.json` (the
raw counters) and `data/reports/harvest-history.tsv` (one row per run, so the
harvesting rate and the remaining backlog stay visible).

## Running a queue

`tools/harvest.py` talks to `learn.microsoft.com` / `web.archive.org`; the
editing sandbox has no route to either, so queues are run on a GitHub runner by
`.github/workflows/harvest.yml`:

1. **Actions → Windows CE Documentation Harvester → Run workflow**
2. *Use workflow from*: the branch that holds the reorganized tree
   (`arena/01a0fa05-wince-docs-corpus` until it is merged into `master`).
3. `queue` = the file name, `limit` = `0` for all (or a cap, see below),
   `batch` = 500, `dry_run` unchecked.

Start with `dry_run: true` to see what a queue would still fetch — it makes no
requests at all. (For the automatic run, the equivalent is a comment-only
`queues/auto-harvest.txt`: it does nothing at all.) The harvester resumes from `data/index/corpus.sqlite3`, so a
queue can be re-run safely and a job that hits the 6-hour runner limit simply
continues on the next run. `wayback-msdn-2010` is the big one: 31,135 topics
left at ~1.5 s each, i.e. ~13 h and roughly 0.8 GB of HTML, so cap each run
(`limit: 8000`) instead of trying to do it in one go.

Notes:

* The harvester stores pages under `corpus/learn/<set>/<id>(v=…).html` (see
  `corpus/README.md`); already-stored ids are skipped, so a queue can be re-run
  safely.
* Rate limits: 0.4 s between `learn.microsoft.com` requests, 1.5 s for
  `web.archive.org`, with adaptive back-off on 429/503. Queue names ending in
  `wayback-msdn-2010` pick the archive delay automatically.
* Failures are logged to `data/logs/fail-<queue>.log`. Entries with status
  `wayback-interstitial` are URLs the Internet Archive can only replay as its
  "JavaScript required" notice; the harvester tries other capture dates and
  never stores that notice (92 such captures had slipped into the 2010-05 set
  and were removed).
* The Win32 documentation is **not** in these queues: it is not crawled but
  imported from pinned commits of MicrosoftDocs/sdk-api and MicrosoftDocs/win32
  with `tools/fetch-upstream.py` (see `../corpus/win32/README.md`).
