# wince-docs-corpus

Offline, page-per-file copy of Microsoft's official Windows CE / Windows
Embedded documentation: Windows CE 1.0 – 6.0, Windows Embedded Compact 7, the
.NET Compact Framework, .NET Micro Framework, POS for .NET and Windows Mobile
6.5 topics that shipped in the same documentation namespace — **plus the Win32
documentation Windows CE shares**, so that an API question can be answered
without breaking the offline copy.

**121,686 pages** (2026-10-04 — `data/index/INDEX.tsv` is the live count):
116,407 extracted/harvested/mirrored CE pages and 5,279 Win32 pages
(markdown, from Microsoft's public `MicrosoftDocs` repositories). The
repository also carries the media the pages were extracted from, the URL
queues used to harvest them, the upstream snapshot the Win32 pages come from,
and the derived catalogs, manifests and indexes.

What belongs in the corpus — and what is kept out — is written down once, in
[`docs/COLLECTION-POLICY.md`](docs/COLLECTION-POLICY.md), and enforced by
`tools/check-policy.py`, which every collection workflow runs.

## What is collected — and what is not

This is a **documentation archive**: documentation pages, reference material
and support articles, one page per file. Nothing else is imported.

* **Collected**: the product documentation and API reference of the releases
  above (as HTML pages or markdown), the KnowledgeBase articles, release notes,
  and the media those came from (kept verbatim under `sources/` as the source
  of the extraction).
* **Collected, as the Win32-common half**: a page of `MicrosoftDocs/sdk-api`
  **only when its API name is one Windows CE documents** — including the `A`/`W`
  variants of a shared base name (`CreateFileA`/`CreateFileW` because CE
  documents `CreateFile`). That is 5,279 pages for 5,068 shared names. The
  desktop-only context of those modules (the Shell, DirectX, WMI, WinRT,
  Windows Media, …) is **not** imported, and neither are the desktop Win32
  programming guides (`MicrosoftDocs/win32`).
* **Not collected**: source code. No `.c`, `.h`, `.cpp`, `.cs`, `.rc`, `.def`,
  `.dsp`, `.vbp` or similar files are imported into `corpus/`, and a medium is
  never unpacked *into* the corpus — `tools/import-media.py` classifies
  everything inside a CD image, keeps the documentation of the product and
  counts the rest (`bin/`, `samples/`, toolchains) as skipped. Code that a
  documentation page quotes as part of its own text is part of that page.
* **Not collected**: the parts of a medium that are not documentation of the
  product — a disc's sponsor/vendor pages, sample trees and their readme pages,
  a viewer's own help, FrontPage metadata directories (`_vti_cnf/`, `_vti_pvt/`,
  `_derived/`). `queues/media.tsv` refuses them per medium and
  `tools/import-media.py` refuses the metadata directories for every medium.
* **Not collected**: another product's documentation that a CE page links to.
  The crawl of the MSDN Library April 2000 refuses the desktop Visual C++ trees
  (`vcmfc`, `vccore`, …) because that material is not CE documentation and the
  Win32-common subset the corpus wants is already collected from Microsoft's
  own `MicrosoftDocs` repositories.
* `tools/check-corpus.py` reports a `source_files` count and
  `tools/check-policy.py` a `source or binary` count, so a source file that
  ever reaches `corpus/` is visible and fails the check.

## Repository layout

| Path | Contents |
|------|----------|
| `corpus/` | The documentation itself, one page per file (HTML, plus markdown for the Win32 pages). See `corpus/README.md`. |
| `corpus/learn/<set>/` | 68,703 pages harvested from `learn.microsoft.com/…/previous-versions/windows/embedded`. |
| `corpus/chm/windows-ce-5.0/` | 20,209 pages: the 98 component CHMs of the CE 5.0 CD1 — per-component guides and API reference, complementary to the Learn harvest (4 shared titles out of 20,141). |
| `corpus/chm/windows-ce-4.2/` | 566 pages: the emulator board and remote-tools reference of the CE .NET 4.2 Platform Builder Emulation Edition media. |
| `corpus/chm/windows-ce-3.0/` | 8,962 pages extracted from the official Windows CE 3.0 documentation CHM. |
| `corpus/mvb/windows-ce-1.0/` | 2,104 pages decoded from the CE 1.0 Books Online (Multimedia Viewer books + WinHelp release notes). |
| `corpus/mvb/windows-ce-2.0-sdk/` | 293 pages of the Windows CE Platform SDK (H/PC) 2.0 disc (02/98): the CE debugger reference (`windbg.hlp`) and the disc ReadMe. The disc's InfoViewer Books Online has no decoder yet; the SDK's headers, libraries and samples are deliberately not imported. |
| `corpus/msdn-library/techshelps/` | 5,165 pages of the MSDN Library's Windows CE 1.0/2.0 sets, from the techshelps mirror (CEGUIDE, WCEMFC, WCEATL, VBCE, WCEDDK, VCCE, DNEMBED). |
| `corpus/msdn-library/datadungeon-2000-04/` | The Windows CE documentation of the MSDN Library April 2000 (CE 2.12/3.0 era), crawled page by page from library.thedatadungeon.com — 3,571 pages so far, the crawl continues twice a day. |
| `corpus/msdn-library/wcedevcon-99/` | 6,382 pages of the Windows CE 2.11/2.12 SDK, DDK and Platform Builder documentation on the DevCon '99 conference disc. The disc's sponsor pages, sample trees, desktop Media Player 2 help and FrontPage metadata are refused (see `queues/media.tsv`). |
| `corpus/kb/` | 257 Windows CE KnowledgeBase articles (CE 1.0/2.0/2.1x era, the CE toolkits, H/PC, Palm-size PC, Pocket PC). |
| `corpus/win32/api/` | 5,279 Win32 pages for the 5,068 API names Windows CE documents (from `MicrosoftDocs/sdk-api`, pinned by commit). `data/reports/win32-shared.tsv` maps each name to its CE pages, `data/reports/win32-imported.tsv` records each page's CE evidence, and `tools/find-api.py` looks a name up on both sides. |
| `corpus/msdn-library/2010-05/<set>/` | 161 Internet Archive copies of MSDN topics (May 2010), filed under the set they duplicate. |
| `corpus/msdn-library/windows-mobile-6.5/` | 34 Windows Mobile 6.5 topics in MSDN Library (MSHelp) format. |
| `sources/` | The verbatim official media the corpus was extracted from (CHMs, HLP/MVB books, documentation zips, the 41-page CE 2.0 site mirror) and the sdk-api snapshot (`sources/microsoftdocs/`), with a `PROVENANCE.md` per release. Reference material — not part of the corpus text. |
| `data/` | Derived datasets (catalogs, TOC trees, manifests, per-page API metadata, gap report) and the generated index. See `data/README.md`. |
| `docs/` | `COLLECTION-POLICY.md` — what belongs in the corpus, the Win32-common rule, and the 2026-10 review that removed 16,228 pages that did not. |
| `queues/` | URL work queues consumed by the harvester (plus out-of-policy candidates that are deliberately not harvested). |
| `tools/` | `harvest.py` (queue → corpus), `fetch-upstream.py` (import the CE-shared Win32 pages), `ce_api_names.py` (the API names Windows CE documents), `check-policy.py` (the collection policy), `extract-mvb.py` (decode Books Online into pages), `extract-chm.py` (unpack documentation CHMs), `crawl-mirror.py` (crawl a documentation mirror), `import-media.py` + `iso9660.py` (fetch a CD image from the Internet Archive and import its documentation), `import-techshelps.py` / `import-kbarchive.py` (third-party sources), `find-api.py` (look a name up across CE and Win32), `check-corpus.py` (integrity/duplicate check), the index builders, the gap-report, the CE-name and Win32-map generators. |
| `.github/workflows/` | `harvest.yml` (harvest a queue from `queues/`; runs on demand or whenever `queues/auto-harvest.txt` changes), `crawl-mirror.yml` (crawl the mirror sites in `queues/mirrors.tsv`, twice a day — this is the live collection), `extract-chm.yml` (unpack the documentation CHMs of a media set in `queues/chm-sets.tsv`), `import-media.yml` (fetch a CD image from the Internet Archive and import its documentation, `queues/media.tsv`) and `import-win32.yml` (re-import `corpus/win32/` from the pinned sdk-api commit). All are `workflow_dispatch` — run them from the Actions tab — and all end with `tools/check-corpus.py` and `tools/check-policy.py`. |

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
  guessed into the wrong set — 413 pages, mostly CE 2.12/3.0-era native API
  topics; all of them come from the `previous-versions/windows/embedded`
  namespace.
* **Generated files** (`data/index/INDEX.tsv`, `data/index/corpus.sqlite3`,
  `data/reports/*.tsv`) are produced by the tools below — do not edit them by
  hand. `data/logs/` (harvest failure logs) is not committed.

## Working with the repository

```bash
python3 tools/check-policy.py          # is corpus/ still CE documentation only?
python3 tools/check-corpus.py --report # integrity, duplicates, source files
python3 tools/build-index.py           # data/index/INDEX.tsv  (id, set, path, title)
python3 tools/build-index-sql.py       # data/index/corpus.sqlite3 (incremental; --full to rebuild)
python3 tools/build-gap-report.py      # data/reports/missing-pages.tsv (catalog vs corpus)
python3 tools/build-ce-api-names.py    # data/reports/ce-api-names.tsv (the CE API names)
python3 tools/fetch-upstream.py list   # what the Win32 import would take
python3 tools/fetch-upstream.py subset --source sdk-api   # corpus/win32/api (pinned commit)
python3 tools/build-win32-map.py       # data/reports/win32-{shared,imported}.tsv
python3 tools/find-api.py CreateFile   # look a name up across CE + Win32

# The desktop Win32 programming guides, as an offline extra outside the corpus
python3 tools/fetch-upstream.py guides --out .cache/win32-guides

# Harvest more pages (the same commands the harvest.yml workflow runs)
python3 tools/harvest.py --queue queues/to-fetch-mslearn.txt --limit 1000
python3 tools/harvest.py --queue queues/to-fetch-mslearn.txt --batch 500 --push
```

The SQLite index holds `pages(page_id, section, path, title, size)` and
`names(name, page_id, kind)` where `kind` is one of `title`, `api`, `const`,
`proto`, `struct`, `enum`; `section` is the corpus-relative directory
(`learn/windows-ce-5.0`). It is committed so that lookups (and the harvester's
resume check) don't have to rescan ~120k files.

## Collection policy

* Official Microsoft public documentation only — no third-party mirrors
  (see `queues/rejected-third-party-sources.txt`); the accepted mirrors for the
  CE 1.0/2.0 era are listed in `queues/third-party-sources.md`.
* Polite fetching: **one in-flight request per host, always** (hosts may be
  parallelised with `--workers`, a single host never is). Fixed delay between
  requests to the same host — 0.4 s for `learn.microsoft.com`, 1.5 s for
  `web.archive.org` — plus jitter, `robots.txt` honoured, keep-alive
  connections reused, adaptive back-off (×2 per 5 consecutive 429/503, capped
  at ×20) with `Retry-After` support.
* The Win32 pages are not crawled at all: they come from a pinned commit of
  Microsoft's public `sdk-api` repository (one HTTPS request), see
  `sources/microsoftdocs/PROVENANCE.md`.
* Documents only — no shared source, no sample code, no compiler binaries,
  no OS images. `tools/check-policy.py` enforces it.
* Failed fetches are recorded in `data/logs/fail-<queue>.log` and retried
  once at double delay.

## Provenance and history

* Per-release provenance: `sources/*/PROVENANCE.md` (source item, archive
  URL, what was and was not extracted) and
  `corpus/msdn-library/windows-mobile-6.5/PROVENANCE.md`.
* 2026-10 review: [`docs/COLLECTION-POLICY.md`](docs/COLLECTION-POLICY.md).
  `corpus/win32/` was cut from 20,452 to 5,279 pages (the 11,819 sdk-api pages
  that were only there as "module context" and the 3,357 desktop programming
  guides are gone; the rule is
  now "Windows CE documents the name"), the DevCon '99 import lost its
  sponsors/samples/FrontPage leftovers (7,433 → 6,382 pages), one Commerce
  Server page was removed from `learn/unclassified/`, four more Win32 pages
  whose name documents another product (Windows Contacts, the desktop Task
  Scheduler, the shim `TAG` macro, the dbghelp `ADDRESS` structure) and their
  modules were refused after reading the CE side of every imported page, and
  `data/win32-exclude.tsv`, `tools/ce_api_names.py`,
  `data/reports/ce-api-names.tsv` and `tools/check-policy.py` were added so the
  same drift cannot happen silently again.
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
* 2026-10 additions: `corpus/mvb/windows-ce-1.0/` (2,104 CE 1.0 pages),
  `corpus/win32/` (the CE-shared Win32 pages from
  `MicrosoftDocs/sdk-api` + the sdk-api snapshot), `tools/fetch-upstream.py`,
  `corpus/msdn-library/2010-05/` (the wayback capture, filed by set instead of
  in its own top-level tree), the DevCon '99 CE 2.11/2.12 SDK documentation,
  and the harvest scheduler rewrite (keep-alive, per-host pacing, robots.txt,
  sqlite resume index, `--dry-run`, `--workers`).
