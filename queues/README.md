# queues/

URL lists consumed by `tools/harvest.py` (`--queue queues/<file>`). One URL per
line; blank lines and lines that don't match a supported URL shape are counted
as `invalid` and skipped.

| File | Lines | Target |
|------|------:|--------|
| `to-fetch-mslearn.txt` | 31,635 | `learn.microsoft.com/en-us/previous-versions/windows/embedded/<id>(v=…)` — the current harvest queue. |
| `mslearn-embedded.txt` | 38,726 | The original full enumeration of the same namespace (superset; first line is the namespace root). |
| `wayback-msdn-2010.txt` | 31,388 | `web.archive.org/web/20100501000000/https://msdn.microsoft.com/en-us/library/<id>.aspx` — the May 2010 MSDN Library snapshot. |
| `rejected-third-party-sources.txt` | 4 | Candidate sources that are **not** harvested: the collection policy is official Microsoft documentation only. Kept as a record of what was deliberately left out (a GitHub mirror, two vendor/community sites and one blog post). |

Notes:

* The harvester stores pages under `corpus/learn/<set>/<id>(v=…).html` (see
  `corpus/README.md`); already-stored ids are skipped, so a queue can be re-run
  safely.
* Rate limits: 0.4 s between `learn.microsoft.com` requests, 1.5 s for
  `web.archive.org`, with adaptive back-off on 429/503. Queue names ending in
  `wayback-msdn-2010` pick the archive delay automatically.
* Failures are logged to `data/logs/fail-<queue>.log`.
* The Win32 documentation is **not** in these queues: it is not crawled but
  imported from pinned commits of MicrosoftDocs/sdk-api and MicrosoftDocs/win32
  with `tools/fetch-upstream.py` (see `../corpus/win32/README.md`).
