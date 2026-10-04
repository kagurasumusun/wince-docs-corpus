# wince-docs-corpus

Offline, page-per-file copy of Microsoft's official Windows CE / Windows
Embedded documentation: Windows CE 1.0 – 6.0, Windows Embedded Compact 7 and
Windows Mobile 6.5 — **plus the Win32 documentation Windows CE shares**, so
that an API question can be answered without breaking the offline copy.

The boundary matters: **Windows CE is not the whole of Win32.**  It is the
CE-specific surface plus the part of Win32 the CE documentation shares, and the
corpus is collected that way — a Win32 page is taken only when a Windows CE
document uses its API name (`docs/COLLECTION-POLICY.md`).  The knowledge base
states the same boundary per name (`surface`, `knowledge/reports/surface.tsv`:
18,931 CE-specific names, 4,353 shared with Win32, 1,155 Win32 spelling pages
for CE names, 3 catalog-only leads, 0 unclaimed Win32 pages).
The .NET families that shipped in the same documentation namespace
(.NET Compact Framework, .NET Micro Framework, POS for .NET) are kept as a
**separate tree**, `corpus/dotnet/`: they document a layer on top of Windows CE,
not the operating system its include/def files describe.

**121,039 pages** (2026-10-04 — `data/index/INDEX.tsv` is the live count):
105,103 CE pages, 10,657 .NET pages and 5,279 Win32 pages (markdown, from
Microsoft's public `MicrosoftDocs` repositories). The repository also carries
the media the pages were extracted from, the URL queues used to harvest them,
the upstream snapshot the Win32 pages come from, and the derived catalogs,
manifests, indexes — and `knowledge/`, the machine-readable knowledge base
built from the pages.

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
  documents `CreateFile`). That is 5,279 pages for 5,068 shared names, and the
  knowledge base folds the variant spellings back onto the base name the CE
  reader knows (`CreateSemaphoreW` -> `CreateSemaphore`, 893 names, on the
  evidence of the page's own "Unicode and ANSI" statement). The
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

The top level separates the four kinds of material the project needs —
**media** (`sources/`, the origin), **documents** (`corpus/`, the material),
**knowledge** (`knowledge/`, the machine-readable statements extracted from the
documents) and **working data** (`data/`, `queues/`, `docs/`, `tools/`, about
the collection rather than part of it).

| Path | Contents |
|------|----------|
| `corpus/` | The documentation itself, one page per file (HTML, plus markdown for the Win32 pages). See `corpus/README.md`. |
| `corpus/learn/<set>/` | 58,046 pages harvested from `learn.microsoft.com/…/previous-versions/windows/embedded`: CE 5.0 (24,694), Embedded CE 6.0 (23,714), CE .NET 4.x (8,969), Compact 7 (256) and 413 unclassified CE 2.12/3.0-era topics. |
| `corpus/chm/windows-ce-5.0/` | 20,179 pages: the 98 component CHMs of the CE 5.0 CD1 — per-component guides and API reference, complementary to the Learn harvest. |
| `corpus/chm/windows-ce-4.2/` | 566 pages: the emulator board and remote-tools reference of the CE .NET 4.2 Platform Builder Emulation Edition media. |
| `corpus/chm/windows-ce-3.0/` | 8,962 pages extracted from the official Windows CE 3.0 documentation CHM. |
| `corpus/mvb/windows-ce-1.0/` | 2,103 pages decoded from the CE 1.0 Books Online (Multimedia Viewer books + WinHelp release notes). |
| `corpus/mvb/windows-ce-2.0-sdk/` | 292 pages of the Windows CE Platform SDK (H/PC) 2.0 disc (02/98): the CE debugger reference (`windbg.hlp`) and the disc ReadMe. The disc's InfoViewer Books Online has no decoder yet; the SDK's headers, libraries and samples are deliberately not imported. |
| `corpus/msdn-library/techshelps/` | 5,165 pages of the MSDN Library's Windows CE 1.0/2.0 sets, from the techshelps mirror (CEGUIDE, WCEMFC, WCEATL, VBCE, WCEDDK, VCCE, DNEMBED). |
| `corpus/msdn-library/datadungeon-2000-04/` | The Windows CE documentation of the MSDN Library April 2000 (CE 2.12/3.0 era), crawled page by page from library.thedatadungeon.com — 2,931 pages collected so far, the crawl continues twice a day. |
| `corpus/msdn-library/wcedevcon-99/` | 6,382 pages of the Windows CE 2.11/2.12 SDK, DDK and Platform Builder documentation on the DevCon '99 conference disc. The disc's sponsor pages, sample trees, desktop Media Player 2 help and FrontPage metadata are refused (see `queues/media.tsv`). |
| `corpus/kb/` | 257 Windows CE KnowledgeBase articles (CE 1.0/2.0/2.1x era, the CE toolkits, H/PC, Palm-size PC, Pocket PC). |
| `corpus/site/` | 44 pages imported from the CE-era web sites that came with the media (`sources/windows-ce-2.0/developer/` — the CE 2.0 developer site including w32model, comm_mod, porting and mgdi — plus the CE 4.2/5.0/6.0 pages that were still outside the corpus). |
| `corpus/dotnet/<set>/` | 10,657 .NET pages, kept apart from the CE trees: POS for .NET (5,793), .NET Micro Framework (4,012), .NET Compact Framework (852). See `corpus/dotnet/README.md`. |
| `corpus/win32/api/` | 5,279 Win32 pages for the 5,068 API names Windows CE documents (from `MicrosoftDocs/sdk-api`, pinned by commit). `data/reports/win32-shared.tsv` maps each name to its CE pages, `data/reports/win32-imported.tsv` records each page's CE evidence, `data/reports/win32-coverage.tsv` is the review worklist of that rule, and `tools/find-api.py` looks a name up on both sides. |
| `corpus/msdn-library/2010-05/<set>/` | 161 Internet Archive copies of MSDN topics (May 2010), filed under the set they duplicate. |
| `corpus/msdn-library/windows-mobile-6.5/` | 34 Windows Mobile 6.5 topics in MSDN Library (MSHelp) format. |
| `knowledge/` | The machine-readable knowledge base built from `corpus/` by `tools/build-kb.py`: 24,442 API entities with their `surface` (**where each name sits in the Windows CE / Win32 split** — 18,931 CE-only, 4,353 shared, 1,155 Win32 spellings of CE names, 3 catalog-only, 0 unclaimed Win32 pages), header/library/DLL/module statements, relations (including the Unicode/ANSI variant links and the `ce-name-lead` records of what the CE page actually prints, each with the evidence it rests on) and generation use, 801 structures whose pages document their members without printing a declaration body (5,204 member rows in `knowledge/kb/struct-fields.tsv` — names and documented order, **no offsets**, they are stated nowhere), 78,444 C/C++ declaration quotes (plus 31,326 managed-code signatures in the separated .NET file), 156,514 requirements, 3,239 CE constraint sentences and 964 quoted ABI statements (`kind: "abi-note"`), an **ABI view per name** (`knowledge/reports/abi.tsv`: the calling convention each declaration prints — never guessed — its member types, bitfields, packing/alignment flags), and the scope of the licence each record's page carries (`license`, from `data/license-scopes.tsv`). Every record names its page. See `knowledge/README.md`. |
| `sources/` | The verbatim official media the corpus was extracted from (CHMs, HLP/MVB books, documentation zips, the 41-page CE 2.0 site mirror) and the sdk-api snapshot (`sources/microsoftdocs/`), with a `PROVENANCE.md` per release. Reference material — not part of the corpus text. |
| `data/` | Derived datasets (catalogs, TOC trees, manifests, per-page API metadata, gap report) and the generated index. See `data/README.md`. |
| `docs/` | `COLLECTION-POLICY.md` — what belongs in the corpus, the Win32-common rule and the .NET split; `LICENSING.md` — the per-item rights registry, the statements it rests on and the finding that most of the collection is not licensed for redistribution; `clean-room.md` — the clean-room definition, the cases, and the invariants `tools/check-cleanroom.py` verifies; `review-2026-10.ja.md` — the 2026-10 review (Japanese), including the round that removed 16,228 pages, the .NET split, the knowledge layer, the rights finding and the ABI layer. |
| `queues/` | URL work queues consumed by the harvester (plus out-of-policy candidates that are deliberately not harvested). |
| `tools/` | Collection: `harvest.py` (queue → corpus), `fetch-upstream.py` (import the CE-shared Win32 pages), `extract-mvb.py`, `extract-chm.py`, `crawl-mirror.py`, `import-media.py` + `iso9660.py`, `import-techshelps.py` / `import-kbarchive.py` / `import-site.py`. Checks and indexes: `check-policy.py` (the collection policy), `check-corpus.py` (integrity/duplicate/source-file check), `dedupe-corpus.py` + `alias_index.py` (resolve duplicates and keep the page ids traceable), `build-index.py`, `build-index-sql.py`, `build-gap-report.py`, `build-ce-api-names.py` + `ce_api_names.py`, `build-win32-map.py`, `build-win32-coverage.py` (the shared-surface review worklist, built from the knowledge base), `find-api.py`, `audit-sources.py` (every artifact under `sources/` against where it ended up), `build-chm-inventory.py` (every CHM/HLP/MVB under `sources/` against the queue entry that extracts it) and `build-topic-coverage.py` (how much of a subject area, e.g. Platform Builder, the official catalogs cover and the corpus holds). Knowledge: `page_parse.py` (the page-format readers, including the ABI readers and the implementation-code test) + `build-kb.py` (writes `knowledge/`) + `check-kb.py` (validates it) + `license_scopes.py` (the rights registry) + `check-licenses.py` (registry coverage, verbatim statements, publication audit) + `check-cleanroom.py` (the six clean-room invariants) + `gen-include-def.py` (the first consumer: writes include/def material into a git-ignored `build/`, refusing to read `corpus/`). |
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
python3 tools/dedupe-corpus.py --check # duplicates/aliases still in place
python3 tools/build-index.py           # data/index/INDEX.tsv  (id, set, path, title)
python3 tools/build-index-sql.py       # data/index/corpus.sqlite3 (incremental; --full to rebuild)
python3 tools/build-gap-report.py      # data/reports/missing-pages.tsv (catalog vs corpus)
python3 tools/build-ce-api-names.py    # data/reports/ce-api-names.tsv (the CE API names)
python3 tools/fetch-upstream.py list   # what the Win32 import would take
python3 tools/fetch-upstream.py subset --source sdk-api   # corpus/win32/api (pinned commit)
python3 tools/build-win32-map.py       # data/reports/win32-{shared,imported}.tsv
python3 tools/build-win32-coverage.py  # data/reports/win32-coverage.tsv (review worklist)
python3 tools/find-api.py CreateFile   # look a name up across CE + Win32
python3 tools/audit-sources.py         # sources/ artifact -> corpus receipt, or a worklist
python3 tools/build-chm-inventory.py   # every CHM under sources/ -> the corpus directory it fed
python3 tools/build-topic-coverage.py --pattern "Platform Builder|OAL|BSP" \
    --out data/reports/platform-builder-coverage.tsv
python3 tools/build-kb.py              # knowledge/ (entities, declarations, requirements)
python3 tools/check-kb.py              # validate knowledge/ ("knowledge OK")

# Turn the knowledge base into include/def material (prototype; writes to build/)
python3 tools/gen-include-def.py --list
python3 tools/gen-include-def.py --set learn/windows-ce-5.0 --out build/generated/wince50

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

* 2026-10 (the boundary, measured): the Windows CE / Win32 boundary is now
  explicit in the knowledge base — every entity carries `surface` (CE-only,
  shared, Win32 spelling of a CE name, catalog-only, or Win32-only; the last is
  empty: no imported Win32 page lacks a CE name behind it) and every
  Unicode/ANSI link records its basis (`page-statement` from the page itself,
  or `import-rule` from `data/reports/win32-shared.tsv`) — and in the
  generator: a Win32 declaration is used only when no CE set prints one, and
  then it is marked as the desktop-Windows reference in the fragment, the
  manifest and the `.def` worklist.  Collection was re-measured instead of
  assumed: `tools/build-chm-inventory.py` accounts for all 105 help files
  under `sources/` (20,745 pages) and `tools/build-topic-coverage.py` shows the
  Platform Builder / OAL / BSP material is complete in the catalogs
  (662 of 662; the 2026-10 review had claimed it was missing — corrected in
  `docs/review-2026-10.ja.md`).  1,155 Unicode/ANSI spellings are folded onto
  their base name (up from 893), 585 of them giving a CE name its Win32 page.
* 2026-10 (knowledge precision and the first generator): 893 Unicode/ANSI
  variant spellings were folded onto their base name on the pages' own
  evidence, the declaration records gained a derived `calling_convention`,
  Header/Library values that name no file were taken out of the maps
  (`knowledge/reports/filtered-values.tsv`) instead of becoming file names,
  `tools/check-kb.py` was added and wired into all five collection workflows,
  `tools/audit-sources.py` now accounts for every artifact under `sources/`
  (172 artifacts, none unclassified), the CE 2.0 developer site was re-read and
  its 20 shop-window pages (press releases, order/download pages, partner and
  logo programmes, case studies) were refused with the reason recorded in
  `data/reports/site-excluded.tsv` (pages: 121,039), and the first consumer,
  `tools/gen-include-def.py`, was written: for a CE 5.0 target it emits 592
  verbatim header fragments, 184 module `.def` worklists and a manifest, into a
  git-ignored `build/` (nothing generated is committed).
* 2026-10 (.NET and knowledge layer): the .NET sets moved out of
  `corpus/learn/` into `corpus/dotnet/` (10,657 pages — Windows CE's own
  documentation stays in `corpus/learn/`), the remaining duplicate pages were
  resolved (672 page copies collapsed to the copy kept, recorded per page in
  `data/index/aliases.tsv`; the table had 673 rows at the time because one
  site page was later found to be a temp copy and removed), 45 pages that were still only under
  `sources/` (44 of them remain — one was a byte-identical FrontPage temp copy
  of another page)
  were imported into `corpus/site/`, and `knowledge/` was added: the
  machine-readable knowledge base (24,442 API entities, 110,345 declarations,
  156,548 requirements, 3,289 CE constraint sentences at that point; the
  refined counts are above), built by
  `tools/build-kb.py` and consumed by an include/def generator.
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
* 2026-10 additions: `corpus/site/` (the CE-era web sites that came with the
  media), `corpus/dotnet/` (the .NET families as their own tree),
  `knowledge/` (the knowledge base), `data/reports/win32-coverage.tsv`,
  `corpus/mvb/windows-ce-1.0/` (CE 1.0 pages),
  `corpus/win32/` (the CE-shared Win32 pages from
  `MicrosoftDocs/sdk-api` + the sdk-api snapshot), `tools/fetch-upstream.py`,
  `corpus/msdn-library/2010-05/` (the wayback capture, filed by set instead of
  in its own top-level tree), the DevCon '99 CE 2.11/2.12 SDK documentation,
  and the harvest scheduler rewrite (keep-alive, per-host pacing, robots.txt,
  sqlite resume index, `--dry-run`, `--workers`).
