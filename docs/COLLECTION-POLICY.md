# Collection policy

What this repository is, in one sentence: **the documentation Microsoft
published for Windows CE and its derivatives, plus the part of the Win32
documentation that Windows CE shares, plus the open-source documents named
in `queues/oss-docs.tsv`** — nothing else.

Windows CE is **not** a full Win32: it is the CE-specific surface plus the
shared part, so "shared" is decided not by resemblance but by a Windows CE
document using the name.  The knowledge base carries that decision per name
(`surface` in `knowledge/kb/entities.jsonl`, one row per name in
`knowledge/reports/surface.tsv`).

The policy is executable: `tools/check-policy.py` fails (exit 1) when a page
that does not belong appears in `corpus/`. Every collection workflow runs it.

```
python3 tools/check-policy.py
corpus/            121,050 pages in 10 trees
  CE trees         105,103 pages
  other layers     10,668 pages (dotnet, oss; oss allowlist 11)
corpus/win32/api/  5,279 CE-shared API pages
# corpus/win32/common/  shared-surface reference pages (data/win32-common-pages.tsv)
policy             OK
```

The .NET families are collected but **kept apart** (`corpus/dotnet/`, 10,657
pages): they document a managed layer on top of Windows CE, so they are neither
part of the CE API surface nor a reason to widen the Win32 rule. See
`corpus/dotnet/README.md`.

## In scope

| Tree | What it holds |
|------|---------------|
| `corpus/learn/` | the `previous-versions/windows/embedded` documentation on Microsoft Learn for the operating system itself: Windows CE 5.0, Windows CE .NET 4.x, Windows Embedded CE 6.0, Windows Embedded Compact 7 and the unclassified CE-era topics |
| `corpus/dotnet/` | the .NET families that shipped in the same namespace but document a layer on top of CE: POS for .NET, the .NET Micro Framework, the .NET Compact Framework |
| `corpus/site/` | the CE-era web sites that came with the media (the CE 2.0 developer site, plus the CE 4.2/5.0/6.0 pages that were still only under `sources/`) |
| `corpus/chm/` | the product documentation shipped as CHMs: CE 3.0, the 98 CE 5.0 component CHMs, the CE .NET 4.2 emulator/remote-tools CHMs |
| `corpus/mvb/` | the CE 1.0 Books Online and the CE 2.0 SDK (H/PC) disc documentation |
| `corpus/msdn-library/` | the MSDN Library CE sets of the CE 1.0/2.0 era (techshelps), the April 2000 MSDN Library crawl (CE 2.12/3.0), the 2010-05 capture, Windows Mobile 6.5, and the CE 2.11/2.12 SDK documentation of the DevCon '99 disc |
| `corpus/kb/` | the Windows CE KnowledgeBase articles |
| `corpus/win32/api/` | the **Win32-common** half: sdk-api pages whose API name Windows CE also documents |
| `corpus/win32/common/` | shared-surface reference pages named in `data/win32-common-pages.tsv` (the base-type table with its typedef bodies) |
| `corpus/oss/` | official documentation pages from named open-source projects (Qt, SDL, OpenSSL, wxWidgets) that are themselves about Windows CE. An allowlist (`queues/oss-docs.tsv`), not a source tree. Kept out of the CE API surface (`layer: oss`) |

## Out of scope (and how it is kept out)

| Not collected | Kept out by |
|---------------|-------------|
| another product's documentation (desktop Win32 API reference, the Shell, DirectX, WMI, WinRT, Windows Media, the desktop programming guides, Commerce Server pages Microsoft itself misfiled in the embedded namespace) | the name rule below; `tools/check-policy.py` refuses any `corpus/win32/` page whose API name CE does not document |
| source code, headers, samples, toolchains, OS images, installer payloads — including the source trees of the open-source projects whose documentation is allowlisted | `tools/import-media.py` counts and skips them; `tools/harvest.py` stores pages only; `tools/check-corpus.py`/`check-policy.py` report a `source or binary` count that must stay 0; `queues/oss-docs.tsv` names documents, not repositories |
| a medium's shop window and leftovers: sponsor and vendor pages, sample trees and their readme pages, FrontPage metadata (`_vti_cnf/`, `_vti_pvt/`, `_derived/`) | per-medium exclude regexes in `queues/media.tsv` plus the built-in metadata-directory rule in `tools/import-media.py` |
| help for a medium's own viewer/IDE (InfoViewer, the Visual C++ help) | per-medium exclude regexes in `queues/media.tsv` |
| third-party mirrors, vendor knowledge bases, blog posts, and an open-source document that is not on the allowlist | `queues/third-party-sources.md` (the accepted mirrors for the CE 1.0/2.0 era, and the open-source documents that were looked at and refused, are listed there); `queues/oss-docs.tsv` is the only door into `corpus/oss/`. **One deliberate exception, and where it stops, is the pinvoke.net section below** |

## What the corpus is for

The corpus is the *material* of a knowledge base, not the end product: the
goal is a machine-readable, traceable description of the Windows CE API
surface from which the include and def files of a CE-targeting toolchain can be
generated. The collection policy therefore also decides what is *structured*:
`tools/build-kb.py` reads the pages and writes `knowledge/` (entities,
declarations, requirements, constraints), each record quoting the page it came
from, and the .NET tree is parsed into that layer with `layer: "dotnet"` rather
than mixed into the CE surface. Nothing is ever invented to fill a gap; gaps
are listed (`knowledge/reports/gaps.tsv`) and collected. The first consumer of
that layer, `tools/gen-include-def.py`, turns one CE version's records into
header fragments and `.def` worklists under a git-ignored `build/` -- material
for a generator, not a finished toolchain. See `knowledge/README.md`.

## The Win32-common rule

Windows CE implements a subset of Win32, so the corpus carries the Win32
documentation **for exactly that subset**:

* A page of `MicrosoftDocs/sdk-api` is imported into `corpus/win32/api/` when
  its API name is an API name Windows CE documents
  (`tools/ce_api_names.py`, evidence in `data/reports/ce-api-names.tsv`),
  including the `A`/`W` variants of a shared base name: CE documents
  `CreateFile`, so `CreateFileA` and `CreateFileW` come along.
* Nothing else is imported. There is no "module context" ring: the desktop
  siblings of a shared API (the Shell, WMP, DirectShow filters CE never had,
  WMI, DirectX, WinRT, ...) are **not** CE documentation.
* The Win32 *programming guides* (`MicrosoftDocs/win32`) are desktop
  documentation — transactional NTFS, change journals, the desktop service
  control manager — and are not part of the corpus either.
  `tools/fetch-upstream.py guides --out DIR` extracts them as an offline extra
  outside the repository for anyone who wants the desktop reading.
* The one thing the CE books never printed, and the shared surface cannot be
  built without, is the **name|description table of the base types with their
  typedef bodies** ("Windows Data Types": `typedef PVOID HANDLE;`, "declared
  in WinNT.h").  That shared-surface reference page is admitted into
  `corpus/win32/common/` one page at a time
  (`data/win32-common-pages.tsv`, imported by
  `tools/fetch-upstream.py common` from the pinned `MicrosoftDocs/win32`
  snapshot).  The rule is deliberately narrow: only pages that document the
  shared *base surface* (types, their declarations, type constants,
  generic-text mappings) — never a desktop feature area — and
  `tools/check-policy.py` refuses anything else under `corpus/win32/common/`.
  The same surface is collected from msdn / mslearn / the Wayback Machine by
  the harvest queue `queues/to-fetch-w32-common.txt`.
* `data/win32-exclude.tsv` lists the reviewed exceptions: two name matches
  where CE documents a *different* thing with the same name (CE's
  `Run (Windows Media Player)` vs. the printer-driver `RUN` structure; the
  device-driver `Address` of the CE 3.0 DDK vs. the dbghelp `ADDRESS`
  structure) and seven modules that document an API family CE never had
  (Windows Runtime `roapi`, Direct2D helpers, the shim-database `TAG` macro of
  `exposeenums2managed`, Windows Contacts `icontact`, the desktop Task
  Scheduler `mstask`, Core Audio device topology, display cloning).

Every imported page carries its CE evidence:
`data/reports/win32-imported.tsv` has `path / module / kind / name / ce_sets /
ce_page_ids`, and `data/reports/win32-shared.tsv` maps each shared name to the
CE page ids that document it.

The rule is not a guess and not an assumption that Windows CE is Win32: a name
is in the corpus only when a CE document uses it, and the knowledge base says so
per name — `surface` in `knowledge/kb/entities.jsonl` (and
`knowledge/reports/surface.tsv`) marks each entity `ce-only`, `shared`,
`win32-spelling` (an A/W spelling of a CE name), `catalog-only` (only the CE TOC
names it — a collection lead) or `win32-only` (documented by the shared-surface
reference only — the base-type rows of `corpus/win32/common/` that no CE page
names, e.g. `HRESULT` in the CE 5.0 list's absence).

The rule is reviewed from both sides: `tools/build-win32-coverage.py` lists the
CE-documented names that state a shared-surface header (`Winbase.h`,
`Winuser.h`, ...) but have no page in `corpus/win32/`
(`data/reports/win32-coverage.tsv`).  Names the reference documents through a
Unicode/ANSI variant spelling are not listed -- the knowledge base folds
`CreateSemaphoreW` onto the CE name `CreateSemaphore` on the page's own
"Unicode and ANSI" statement. Of the 960 rows that remain, 768 are
message/notification/macro constants (`WM_PAINT`, `CB_GETEDITSEL`, ...) that
sdk-api has no page for, and the rest are CE-only APIs (`Ce*` RAPI,
`CommandBar_*`) and Win32 APIs the reference no longer pages (`GetStringType`,
`Random`): no page was missed, and the list keeps the question answerable.

## The one third-party exception: pinvoke as weak auxiliary reference

Every rule above says the corpus is **Microsoft's own documentation**.  There
is one deliberate carve-out, and its boundary is written into the tools rather
than left to habit.  It has two accept paths, both equally isolated:

* `sources/dotnet-pinvoke/` holds the pinned snapshot of
  [github.com/dotnet/pinvoke](https://github.com/dotnet/pinvoke) (the .NET
  Foundation's community-maintained re-formatting of the pinvoke.net data as
  C# bindings; **archived upstream**, MIT): `sources/dotnet-pinvoke/PROVENANCE.md`
  records the commit.  Because the tree is C# *code*, it is kept out of
  `corpus/` (the corpus stays documentation-only): `tools/pinvoke_extract.py`
  reads the tarball and writes only the isolated aux records (constant names
  and values as printed, module placement, `[DllImport]` APIs) to
  `knowledge/aux/`, every row quoting its `.cs` line by archive member and
  line number and stamped `dotnet-pinvoke-mit`.
* `corpus/pinvoke/` may hold pages of the pinvoke.net P/Invoke reference wiki
  (a user-contributed third-party site), and **only** the wiki sections named
  in `queues/pinvoke-net.txt` (`default.aspx/{module}`: the CE-relevant
  modules such as `coredll` and `rapi`, the shared Win32 modules, and the
  wiki's Constants/Structures/Enums sections).  `tools/check-policy.py`
  refuses any page outside exactly those sections — the queue is the door,
  the same way `queues/oss-docs.tsv` is for `corpus/oss/`.
* **Why it exists at all**: the constants problem.  The official
  documentation numbers fewer constants than an include file needs
  (`WM_USER`, `SW_SHOW`, `WS_OVERLAPPED` and thousands of others are
  documented by name but never *numbered* by Microsoft's CE pages), while
  the pinvoke community pages print numeric spellings of those names.  It
  is used **only** as a *weak auxiliary* hint for judging constant /
  value / header **linkage** where Microsoft's own pages state nothing —
  highest-suspicion, lowest-priority evidence by construction.  In
  practice: the dotnet/pinvoke rows currently file **343** otherwise
  unlinked constants at rank `pinvoke-weak`, the remaining **2,012** names
  stay on the open worklist (`knowledge/reports/constant-header-gaps.tsv`),
  and the review table (`knowledge/reports/constant-pinvoke-review.tsv`)
  compares each community value against the documented CE value (335 of
  335 linked names agree, hex/decimal spellings aside).
* **Why it is isolated**: pinvoke.net is not documentation of Windows CE and
  its numbers are not Windows CE facts.  Therefore
  * `tools/build-kb.py` never mints an entity, declaration, requirement or
    constant from it; its facts are written to `knowledge/aux/`, a separate
    layer beside (never inside) the specification the include/def surface is
    generated from — see `knowledge/aux/README.md`;
    * the generator (`tools/gen-include-def.py`) consumes it at the
      weakest rank: header *linkage* as `pinvoke-weak` in
      `kb/constant-headers.tsv`, and — only for a constant a CE page
      **names** but no CE page, Win32 CC-BY page, or public-domain CeGCC
      w32api **numbers** — a last-rank MIT *value* (`tools/pinvoke_gaps.py`).
      Official numbers always outrank it.  No C header is copied.
  * `data/license-scopes.tsv` stamps the wiki tree `pinvoke-user-wiki`,
    redistribution **no**, and the tarball `dotnet-pinvoke-mit` (MIT):
    either way it is evidence for review, never publishable documentation
    inside the CE surface.

## The second third-party exception: licence-vetted header mirrors as review-only cross-check

Two pinned header mirrors under `sources/` answer one question:
**which names exist that the CE corpus never documents**, and do values
agree where both sides speak.  The licence of each was investigated
before any use — acquisition route, publisher, licence scope read from
the files themselves, usage decision, all recorded in the source's
`PROVENANCE.md`:

* `sources/w32api-cegcc/` — **the only reference**: the CeGCC toolchain's
  w32api (pinned commit `8e64b608`), the classic 32-bit Win32 API headers
  adapted for Windows CE itself (`libce/`, `_WIN32_WCE` branches).
  Windows CE is a 32-bit target; this is the right frame.  The package
  is public domain with named permissive notices (its `README.w32api`),
  and the per-file tally is reproducible by `tools/xcheck_references.py`.
  **No header file is copied.**  The generator may take a single
  `#define NAME value` when a CE page names the constant and no
  documentation page numbers it (`tools/w32api_gaps.py`).
* **Standing prohibition (2026-10, user order): Wine, ReactOS and
  MinGW-w64 are NOT Windows CE — their material must never be used as a
  reference here.**  Their snapshots and every report derived from them
  are deleted; do not re-add them.

`tools/xcheck_references.py` writes only *reports* under
`knowledge/reports/xcheck-*.tsv` + `xcheck-summary.md` (each row
attributed header:line of its pinned commit): 24,936 candidate names
absent from the CE corpus from w32api-cegcc (plus 10,828 `.def` export
leads from its `libce/`+`lib/` lists against `winsur/link/*.def`); and
where both sides number a name the verdicts run to flagged divergences —
`MAX_PATH` (CE's DirectShow DVD `Dvdata.h` page prints 128,
a local shadow of the desktop's 260) and `HTTP_QUERY_MAX` (CE pages
print 75; the reference prints 45 — generational drift).  The
isolation is stricter than the pinvoke carve-out: nothing it parses is
an input to `tools/build-kb.py`, `tools/gen-include-def.py` or
`winsur/`.  A listed name is a lead for further documentation
searching, never a value to adopt.

## Review 2026-10 (what was wrong, what changed)

The corpus had grown by collecting whole Win32 *modules* instead of the shared
surface, and by importing everything an older medium happened to contain. The
review removed 16,228 pages (68 MB) and closed the doors that let them in.

| Finding | Evidence | Action |
|---------|----------|--------|
| 11,819 desktop-only sdk-api pages ("module context" of 183 modules) filled `corpus/win32/api/` | `--scope modules` was the default of `tools/fetch-upstream.py` and `import-win32.yml` | default and only rule is now "CE documents the name"; 5,279 pages remain; `--scope modules` is gone |
| 3,357 desktop Win32 programming guides in `corpus/win32/guide/` | headings like *Transactional NTFS*, *Change Journals*, *Service control manager* | tree removed, extraction moved behind `fetch-upstream.py guides --out DIR` (outside the corpus) |
| the DevCon '99 import dragged in 839 pages of sponsor shop window, sample trees and their readmes, plus `_vti_cnf`/`_vti_pvt` FrontPage metadata (423 pages), `MPLAYER2/` (desktop Media Player 2 Books Online), `MPSUPP/` (generic product support pages), `ACCESSIB/` (general accessibility pages) and `Handhelds/` (a vendor's spec sheets) | `find corpus/msdn-library/wcedevcon-99 -path '*_vti_cnf*'` etc. | the medium's exclude regex in `queues/media.tsv` now refuses them; `tools/import-media.py` refuses metadata directories for every medium; 6,382 pages of CE 2.11/2.12 SDK documentation remain |
| a Microsoft Commerce Server page sat in `learn/unclassified/` | `ms866183(v=msdn.10).html` (canonical URL in the embedded namespace, content about `Microsoft.CommerceServer`) | removed |
| four pages survived the name rule although the *same name* documents another product: Windows Contacts (`icontact`), the desktop Task Scheduler (`mstask`), the shim-database `TAG` macro (`exposeenums2managed`) and the dbghelp `ADDRESS` structure | their upstream descriptions name the other product (`[Windows Contacts]`, `[Task Scheduler]`, "Identifies an entry in the shim database") while the CE page of that name documents the Pocket Outlook object, the Mobile Channels `TAG` or the device-driver `Address` | the four modules/pages are refused in `data/win32-exclude.tsv`; 5,279 pages remain, and every remaining page's CE evidence is one line in `data/reports/win32-imported.tsv` |
| the .NET families were mixed into `corpus/learn/` (10,657 pages), so CE counts, `learn/` greps and coverage numbers were ambiguous | every set-level count in the repository, and `tools/ce_api_names.py`, which had to exclude the same pages from the Win32 mining by hand | the .NET sets moved to `corpus/dotnet/` (`tools/harvest.py` has `DOTNET_DIR`/`DOTNET_SETS`); the CE trees hold CE pages only; the knowledge base records the pages with `layer: "dotnet"` |
| the mined Win32 name list was never looked at as a whole | — | `data/reports/ce-api-names.tsv` makes every name, its CE sets and its CE page ids reviewable; the two name-level and seven module-level exceptions live in `data/win32-exclude.tsv` |
| `data/index/INDEX.tsv` had 6 ragged rows (page titles spanned several lines) | `awk -F'\t' 'NF!=4'` | `tools/build-index.py` folds whitespace in titles |

Checked and found correct during the same review, so it stayed:

* the CE sets themselves (`learn/` is 100 % the `previous-versions/windows/
  embedded` namespace; the CHM/MVB/KB/MSDN-Library trees are CE releases);
* pages whose text is mostly a code listing: they are documentation pages that
  *quote* code (KnowledgeBase articles, sample chapters), not source files;
* GDI+, TAPI, TSPI, UPnP, WSD, P2P, Smart Card, LDAP, WinInet, ICM, DirectShow
  and Windows Media pages: Windows CE documents those APIs itself, so their
  Win32 pages are genuinely part of the shared surface (each one is listed with
  its CE page ids in `data/reports/win32-shared.tsv`).
* the pairing itself: every imported page carries the CE page it was matched
  against. The 149 pages whose CE side is a catalog entry or a CE SDK anchor
  page were read one by one — the CE page has the same API name in all of them,
  except for the `address` case above.
* the duplicates were the media's own structure, not import errors: of the
  672 byte-for-byte duplicate groups, 640 pages of the CE 2.12 SDK reference
  appeared both in the DevCon '99 capture and in the `datadungeon` MSDN CD
  capture, 30 CE 5.0 pages sat in both the `wcemouse5` and the `wcestylus5`
  component CHM, and 2 were one CE 1.0 book page that shipped twice on its CD.
  **They have since been resolved** (2026-10): the duplicate copy was removed
  and the keeper recorded per page in `data/index/aliases.tsv`
  (`tools/dedupe-corpus.py`; priority `learn` > `dotnet` > `chm` > `mvb` >
  `wcedevcon-99` > `techshelps` > `kb` > `windows-mobile-6.5` > `2010-05` >
  `datadungeon`, so the page survives in the most authoritative tree; a 673rd
  row was the FrontPage temp copy `site/windows-ce-2.0/programs/~hsB154.html`,
  byte-identical to `weblogo.html` -- both were removed when the CE 2.0 site
  was re-read in 2026-10, so the table now holds 672 rows).
  `--check` reports 0 groups now, and
  `corpus/msdn-library/2010-05/` keeps its 161 wayback captures next to the
  Learn pages they duplicate because they are a *different capture* of the same
  documentation, not a copy of it.

## Adding something new

1. Collect it (a queue, a medium, an upstream repository).
2. If it is Win32 material, it goes through `tools/ce_api_names.py` — do not
   add a folder by hand.
3. Run `tools/check-policy.py`, `tools/check-corpus.py --report`,
   `tools/dedupe-corpus.py --check`, `tools/audit-sources.py`,
   `tools/build-chm-inventory.py`, `tools/build-index.py`,
   `tools/build-index-sql.py`, `tools/build-ce-api-names.py`,
   `tools/build-win32-map.py`, `tools/build-win32-coverage.py`,
   `tools/build-kb.py` and `tools/check-kb.py`, and commit the refreshed
   reports with it.  (All five collection workflows do exactly this before they
   commit; `tools/build-topic-coverage.py --pattern <subject> --out …` measures
   a whole subject area when a collection question is about one.)
