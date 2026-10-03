# wince-docs-corpus

Offline, page-per-file copy of Microsoft's official Windows CE / Windows
Embedded documentation: Windows CE 1.0 – 6.0, Windows Embedded Compact 7, the
.NET Compact Framework, .NET Micro Framework, POS for .NET and Windows Mobile
6.5 topics that shipped in the same documentation namespace — **plus the Win32
documentation Windows CE shares**, so that an API question can be answered
without breaking the offline copy.

**138,572 pages** (2026-10-04 — the count moves while the crawl runs;
`data/index/INDEX.tsv` is live): 118,120 extracted/harvested/mirrored CE pages
and 20,452 Win32 pages
(markdown, from Microsoft's public `MicrosoftDocs` repositories). The
repository also carries the media the pages were extracted from, the URL
queues used to harvest them, the complete upstream snapshots, and the derived
catalogs, manifests and indexes.

## What is collected — and what is not

This is a **documentation archive**: documentation pages, reference material
and support articles, one page per file. Nothing else is imported.

* **Collected**: the product documentation and API reference of the releases
  above (as HTML pages or markdown), the KnowledgeBase articles, release notes,
  and the media those came from (kept verbatim under `sources/` as the source
  of the extraction).
* **Not collected**: source code. No `.c`, `.h`, `.cpp`, `.cs`, `.rc`, `.def`,
  `.dsp`, `.vbp` or similar files are imported into `corpus/`, and a medium is
  never unpacked *into* the corpus — `tools/import-media.py` classifies
  everything inside a CD image, keeps the documentation files and counts the
  rest (`bin/`, `samples/`, toolchains) as skipped. Code that a documentation
  page quotes as part of its own text is part of that page.
* **Media itself is not collected either.** A medium imported on a runner
  (`import-scratch` in `queues/media.tsv`) is fetched to a scratch directory,
  its documentation pages are copied out and the image is discarded; the pages
  carry the provenance (item, file, size, md5) instead. Only media that has no
  other home is kept under `sources/`.
* **Not collected**: another product's documentation that a CE page links to.
  The crawl of the MSDN Library April 2000 refuses the desktop Visual C++ trees
  (`vcmfc`, `vccore`, …) because that material is not CE documentation and the
  Win32-common subset the corpus wants is already collected from Microsoft's
  own `MicrosoftDocs` repositories.
* `tools/check-corpus.py` reports a `source_files` count, so a source file that
  ever reaches `corpus/` is visible in `data/reports/corpus-problems.tsv`.

## Repository layout

| Path | Contents |
|------|----------|
| `corpus/` | The documentation itself, one page per file (HTML, plus markdown for the Win32 trees). See `corpus/README.md`. |
| `corpus/learn/<set>/` | 68,704 pages harvested from `learn.microsoft.com/…/previous-versions/windows/embedded`. |
| `corpus/chm/windows-ce-5.0/` | 20,209 pages: the 98 component CHMs of the CE 5.0 CD1 — per-component guides and API reference, complementary to the Learn harvest (4 shared titles out of 20,141). |
| `corpus/chm/windows-ce-4.2/` | 566 pages: the emulator board and remote-tools reference of the CE .NET 4.2 Platform Builder Emulation Edition media. |
| `corpus/chm/windows-ce-3.0/` | 8,962 pages extracted from the official Windows CE 3.0 documentation CHM. |
| `corpus/mvb/windows-ce-1.0/` | 2,104 pages decoded from the CE 1.0 Books Online (Multimedia Viewer books + WinHelp release notes). |
| `corpus/mvb/windows-ce-2.0-sdk/` | 293 pages of the Windows CE Platform SDK (H/PC) 2.0 disc (02/98): the CE debugger reference (`windbg.hlp`) and the disc ReadMe. The disc's InfoViewer Books Online has no decoder yet; the SDK's headers, libraries and samples are deliberately not imported. |
| `corpus/msdn-library/techshelps/` | 5,165 pages of the MSDN Library's Windows CE 1.0/2.0 sets, from the techshelps mirror (CEGUIDE, WCEMFC, WCEATL, VBCE, WCEDDK, VCCE, DNEMBED). |
| `corpus/msdn-library/datadungeon-2000-04/` | The Windows CE documentation of the MSDN Library April 2000 (CE 2.12/3.0 era), crawled page by page from library.thedatadungeon.com — 4,659 pages so far, the crawl continues twice a day. |
| `corpus/msdn-library/wcedevcon-99/` | 7,437 pages from the Windows CE Developers Conference DevCon '99 CD (1999): the CE 3.0 SDK documentation in HTML (SDK Reference, Auto PC, DDK, SDK Guide, …), its component CHMs and the conference site. |
| `corpus/kb/` | 257 Windows CE KnowledgeBase articles (CE 1.0/2.0/2.1x era, the CE toolkits, H/PC, Palm-size PC, Pocket PC). |
| `corpus/win32/api/`, `corpus/win32/guide/` | 20,452 Win32 pages: 5,219 CE-shared API pages, 11,876 module-context pages, 3,357 subsystem guides (from `MicrosoftDocs/sdk-api` and `MicrosoftDocs/win32`, pinned by commit). `data/reports/win32-shared.tsv` maps the shared surface, `tools/find-api.py` looks a name up on both sides. |
| `corpus/msdn-library/2010-05/<set>/` | 161 Internet Archive copies of MSDN topics (May 2010), filed under the set they duplicate. |
| `corpus/msdn-library/windows-mobile-6.5/` | 34 Windows Mobile 6.5 topics in MSDN Library (MSHelp) format. |
| `sources/` | The verbatim official media the corpus was extracted from (CHMs, HLP/MVB books, documentation zips, the 41-page CE 2.0 site mirror) and the complete MicrosoftDocs snapshots (`sources/microsoftdocs/`), with a `PROVENANCE.md` per release. Reference material — not part of the corpus text. |
| `data/` | Derived datasets (catalogs, TOC trees, manifests, per-page API metadata, gap report) and the generated index. See `data/README.md`. |
| `queues/` | URL work queues consumed by the harvester (plus out-of-policy candidates that are deliberately not harvested). |
| `tools/` | `harvest.py` (queue → corpus), `fetch-upstream.py` (import the Win32 pages), `extract-mvb.py` (decode Books Online into pages), `extract-chm.py` (unpack documentation CHMs), `crawl-mirror.py` (crawl a documentation mirror) + `mark-crawl-covered.py` (take pages a medium already brought out of a crawl's frontier), `import-media.py` + `iso9660.py` (fetch a CD image from the Internet Archive and import its documentation), `import-techshelps.py` / `import-kbarchive.py` (third-party sources), `find-api.py` (look a name up across CE and Win32), `check-corpus.py` (integrity/duplicate check), the index builders, the gap-report and Win32-map generators. |
| `.github/workflows/` | `harvest.yml` (harvest a queue from `queues/`; runs on demand or whenever `queues/auto-harvest.txt` changes), `crawl-mirror.yml` (crawl the mirror sites in `queues/mirrors.tsv`, twice a day — this is the live collection), `extract-chm.yml` (unpack the documentation CHMs of a media set in `queues/chm-sets.tsv`), `import-media.yml` (fetch a CD image from the Internet Archive and import its documentation, `queues/media.tsv`) and `import-win32.yml` (re-import `corpus/win32/` from the pinned MicrosoftDocs commits). All are `workflow_dispatch` — run them from the Actions tab. |

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
* 2026-10 additions: `corpus/mvb/windows-ce-1.0/` (2,104 CE 1.0 pages), and
  `corpus/win32/` (20,452 Win32 pages from
  `MicrosoftDocs/sdk-api` + `MicrosoftDocs/win32`), `sources/microsoftdocs/`
  (full snapshots + provenance), `tools/fetch-upstream.py`,
  `corpus/msdn-library/2010-05/` (the wayback capture, filed by set instead of
  in its own top-level tree), and the harvest scheduler rewrite
  (keep-alive, per-host pacing, robots.txt, sqlite resume index, `--dry-run`,
  `--workers`).
