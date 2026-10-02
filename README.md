# wince-docs-corpus

Offline, page-per-file copy of Microsoft's official Windows CE / Windows
Embedded documentation: Windows CE 1.0 – 6.0, Windows Embedded Compact 7, the
.NET Compact Framework, .NET Micro Framework, POS for .NET and Windows Mobile
6.5 topics that shipped in the same documentation namespace — **plus the Win32
documentation Windows CE shares**, so that an API question can be answered
without breaking the offline copy.

**98,405 pages**: 77,953 harvested/extracted CE pages (HTML) and 20,452 Win32
pages (markdown, from Microsoft's public `MicrosoftDocs` repositories). The
repository also carries the original media the pages were extracted from, the
URL queues used to harvest them, the complete upstream snapshots, and the
derived catalogs, manifests and indexes.

## Repository layout

| Path | Contents |
|------|----------|
| `corpus/` | The documentation itself, one page per file (HTML, plus markdown for the Win32 trees). See `corpus/README.md`. |
| `corpus/learn/<set>/` | 68,704 pages harvested from `learn.microsoft.com/…/previous-versions/windows/embedded`. |
| `corpus/chm/windows-ce-3.0/` | 8,962 pages extracted from the official Windows CE 3.0 documentation CHM. |
| `corpus/win32/api/`, `corpus/win32/guide/` | 20,452 Win32 pages: 5,219 CE-shared API pages, 11,876 module-context pages, 3,357 subsystem guides (from `MicrosoftDocs/sdk-api` and `MicrosoftDocs/win32`, pinned by commit). `data/reports/win32-shared.tsv` maps the shared surface, `tools/find-api.py` looks a name up on both sides. |
| `corpus/msdn-library/2010-05/<set>/` | 253 Internet Archive copies of MSDN topics (May 2010), filed under the set they duplicate. |
| `corpus/msdn-library/windows-mobile-6.5/` | 34 Windows Mobile 6.5 topics in MSDN Library (MSHelp) format. |
| `sources/` | The verbatim official media the corpus was extracted from (CHMs, HLP/MVB books, documentation zips, the 41-page CE 2.0 site mirror) and the complete MicrosoftDocs snapshots (`sources/microsoftdocs/`), with a `PROVENANCE.md` per release. Reference material — not part of the corpus text. |
| `data/` | Derived datasets (catalogs, TOC trees, manifests, per-page API metadata, gap report) and the generated index. See `data/README.md`. |
| `queues/` | URL work queues consumed by the harvester (plus out-of-policy candidates that are deliberately not harvested). |
| `tools/` | `harvest.py` (queue → corpus), `fetch-upstream.py` (import the Win32 pages), `find-api.py` (look a name up across CE and Win32), the index builders, the gap-report and Win32-map generators. |
| `.github/workflows/` | `harvest.yml` (run the harvester for a queue in `queues/`, refresh indexes/reports) and `import-win32.yml` (re-import `corpus/win32/` from the pinned MicrosoftDocs commits). Both are `workflow_dispatch` — run them from the Actions tab. |

## Corpus conventions

* **One page = one file.** The file name is the page id:
  * Learn pages: the last segment of the page's canonical URL, version tag
    included — `aa450192(v=msdn.10).html`. File names therefore join directly
    with `data/catalogs/*.tsv`, `data/manifests/*` and
    `data/reports/missing-pages.tsv`.
    A topic is never stored twice: the harvest first fetched `aa450192.html`
    and later `aa450192(v=msdn.10).html`; only the canonical-name file is kept
    (17,622 such duplicates were removed, 670 MB of redundant HTML).
  * CE 3.0: the CHM topic file name (`_wcepb_ASSERT.html`).
  * Wayback snapshot: the original MSDN topic id (`01c3x0ze.html`).
* **Set directories** (`windows-ce-5.0`, `windows-ce-net-4x`,
  `windows-embedded-ce-6.0`, …) are shared by the corpus, the catalogs, the
  TOC trees and the manifests.
* The harvester picks the set from the page title (`BOOK_RULES` in
  `tools/harvest.py`, mirrored in `corpus/README.md`). Pages whose set cannot
  be determined are kept under `corpus/learn/unclassified/` rather than
  guessed into the wrong set — 414 pages, mostly CE 2.12/3.0-era native API
  topics and a handful of non-CE pages caught by the namespace crawl.
* **Generated files** (`data/index/INDEX.tsv`, `data/index/corpus.sqlite3`,
  `data/reports/missing-pages.tsv`) are produced by the tools below — do not
  edit them by hand.
  `data/logs/` (harvest failure logs) is not committed.

## Working with the repository

```bash
python3 tools/build-index.py          # data/index/INDEX.tsv  (id, set, path, title)
python3 tools/build-index-sql.py      # data/index/corpus.sqlite3 (incremental; --full to rebuild)
python3 tools/build-gap-report.py     # data/reports/missing-pages.tsv (catalog vs corpus)
python3 tools/fetch-upstream.py list                    # what the Win32 import would take
python3 tools/fetch-upstream.py subset --source sdk-api # corpus/win32/api (pinned commit)
python3 tools/build-win32-map.py      # data/reports/win32-{shared,imported}.tsv
python3 tools/find-api.py CreateFile  # look a name up across CE + Win32

# Harvest more pages (the same commands the harvest.yml workflow runs)
python3 tools/harvest.py --queue queues/to-fetch-mslearn.txt --limit 1000
python3 tools/harvest.py --queue queues/to-fetch-mslearn.txt --batch 500 --push
```

The SQLite index holds `pages(page_id, section, path, title, size)` and
`names(name, page_id, kind)` where `kind` is one of `title`, `const`, `proto`,
`struct`, `enum`; `section` is the corpus-relative directory
(`learn/windows-ce-5.0`). It is committed so that lookups (and the
harvester's resume check) don't have to rescan ~78k files.

## Collection policy

* Official Microsoft public documentation only — no third-party mirrors
  (see `queues/rejected-third-party-sources.txt`).
* Polite fetching: **one in-flight request per host, always** (hosts may be
  parallelised with `--workers`, a single host never is). Fixed delay between
  requests to the same host — 0.4 s for `learn.microsoft.com`, 1.5 s for
  `web.archive.org` — plus jitter, `robots.txt` honoured, keep-alive
  connections reused, adaptive back-off (×2 per 5 consecutive 429/503, capped
  at ×20) with `Retry-After` support.
* The Win32 pages are not crawled at all: they come from pinned commits of
  Microsoft's public documentation repositories (one HTTPS request per
  repository), see `sources/microsoftdocs/PROVENANCE.md`.
* Documents only — no shared source, no sample code, no compiler binaries,
  no OS images.
* Failed fetches are recorded in `data/logs/fail-<queue>.log` and retried
  once at double delay.

## Provenance and history

* Per-release provenance: `sources/*/PROVENANCE.md` (source item, archive
  URL, what was and was not extracted) and
  `corpus/msdn-library/windows-mobile-6.5/PROVENANCE.md`.
* 2026-10 re-organisation: `docs/mslearn/…` → `corpus/learn/…`,
  `docs/chm/…` → `corpus/chm/…`, `docs/wayback-msdn/…` →
  `corpus/wayback-msdn/…`, `supplementary/…` → `corpus/msdn-library/…`,
  `archives/` → `sources/`, `urls/` → `queues/`,
  `data/rows/rows*.json` → `data/metadata/api-*.json`,
  `data/catalogs/books-*.tsv` → `data/toc/*.tsv`,
  `data/manifests/full-*.manifest` → `data/manifests/<set>.manifest`,
  `pagesgap/INDEX.tsv` → `data/reports/missing-pages.tsv`,
  `tools/make-index.py` → `tools/build-index.py`.
  Pages were deduplicated and renamed to their canonical page ids at the
  same time.
* 2026-10 additions: `corpus/win32/` (20,452 Win32 pages from
  `MicrosoftDocs/sdk-api` + `MicrosoftDocs/win32`), `sources/microsoftdocs/`
  (full snapshots + provenance), `tools/fetch-upstream.py`,
  `corpus/msdn-library/2010-05/` (the wayback capture, filed by set instead of
  in its own top-level tree), and the harvest scheduler rewrite
  (keep-alive, per-host pacing, robots.txt, sqlite resume index, `--dry-run`,
  `--workers`).
