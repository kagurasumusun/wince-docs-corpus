# corpus/

The documentation text, one page per file, grouped by **source** and then by
**documentation set**. Harvested/extracted pages are HTML; the Win32 material
imported from MicrosoftDocs is markdown (`win32/`), as Microsoft publishes it
that way:

```
corpus/
├── learn/<set>/              pages harvested from learn.microsoft.com
├── chm/windows-ce-3.0/       pages extracted from the official CE 3.0 CHM
├── mvb/windows-ce-1.0/       CE 1.0 books (Multimedia Viewer/WinHelp era)
├── kb/                       Windows CE KnowledgeBase articles (CE 1.0/2.0 era)
├── win32/api/, win32/guide/  Win32 reference + guides (MicrosoftDocs)
└── msdn-library/
    ├── 2010-05/<set>/        Internet Archive copies of MSDN topics
    ├── techshelps/<set>/     MSDN Library CE 1.0/2.0 sets (techshelps mirror)
    ├── datadungeon-2000-04/  MSDN Library April 2000 CE documentation (crawled)
    └── windows-mobile-6.5/   MSHelp-format Windows Mobile 6.5 topics
```

Total: 105,839 pages (85,387 in the CE trees + 20,452 Win32 pages) — see
the per-tree READMEs for the provenance of each, and `../queues/
third-party-sources.md` for the mirror policy.

## Sets under `corpus/learn/` (68,704 pages)

| Set | Pages | Contents |
|-----|------:|----------|
| `windows-ce-5.0` | 24,694 | Windows CE 5.0 product documentation and API reference. |
| `windows-embedded-ce-6.0` | 23,714 | Windows Embedded CE 6.0 documentation and API reference. |
| `windows-ce-net-4x` | 8,970 | Windows CE .NET 4.0/4.1/4.2 topics (native API, drivers, guides). |
| `pos-for-net` | 5,793 | POS for .NET (`Microsoft.PointOfService`) reference. |
| `dotnet-micro-framework` | 4,012 | .NET Micro Framework (`Microsoft.SPOT.*`, `Ws.*`, `Dpws.*`, `System.Ext.*`, WSD/DPWS stack). |
| `dotnet-compact-framework` | 852 | .NET Compact Framework class-library pages (`System.*` namespaces). |
| `windows-embedded-compact-7` | 256 | Windows Embedded Compact 7 remote-tools reference (`(Compact 7)`). |
| `unclassified` | 414 | Set could not be determined from page metadata. |

(IDs differ from the page count: sdk-api contains the same page id in several
modules — `winsock`/`winsock2` and the `A`/`W` variants of a name — so a few
hundred page ids repeat; the SQL index keys pages by path.)

`unclassified/` is a deliberate holding area, not a junk drawer: 313 of the
414 pages are Windows CE 2.12/3.0-era native API topics (e.g. `dprintf`,
`IeXdiARMContext::GetContext`) that predate the per-edition catalogs, 55 are
.NET Micro Framework class pages whose namespace is not in the title, and the
remaining 46 only shared the `previous-versions/windows/embedded` namespace
(2 Windows Server topics, 44 undetermined — one of them the Visual Studio page
whose page id the CE .NET catalog also lists).

Pages that arrived in the wrong set were correctable against the official
catalogs and were moved: 12 CE 6.0 pages that had been filed under CE 5.0
because their titles say "Windows CE 5.0 vs. Windows Embedded CE 6.0", one
CE 5.0 migration topic filed under CE .NET, and one Visual Studio page whose
page id the CE .NET catalog also lists.

## How the sets are chosen

`tools/harvest.py` classifies each harvested page by its title (and, as a
fallback, markers in the body):

| Rule (title pattern, in order) | Set |
|--------------------------------|-----|
| `(Windows CE .NET …)` / `(Windows CE 4.x)` / `(Windows CE 4.0)` | `windows-ce-net-4x` |
| `(Windows CE 5.0)` | `windows-ce-5.0` |
| `(Windows Embedded CE 6.0 …)` / `(Microsoft.RemoteToolSdk …)` | `windows-embedded-ce-6.0` |
| `(Compact 7)` | `windows-embedded-compact-7` |
| `(Microsoft.PointOfService …)` | `pos-for-net` |
| `(Microsoft.SPOT …)` / `(Microsoft.Web.Services …)` / `(Ws …)` / `(Dpws …)` / `(System.Ext …)` | `dotnet-micro-framework` |
| `(System …)` / `(Microsoft …)` / `(… Method\|Property\|Class\|…)` | `dotnet-compact-framework` |
| `(Windows Mobile <ver>)` | `windows-mobile-<ver>` |
| anything else | `uncategorized` → files land in `unclassified/` |

The table is the single source of truth for both the code and this document;
if you change `BOOK_RULES` in `tools/harvest.py`, update this table.

## File naming

The file name is the page id — the last segment of the page's canonical URL
for Learn pages (version tag included: `aa450192(v=msdn.10).html`), the CHM
topic name for CE 3.0, the topic's context id (`AB5A.html`) for the CE 1.0
Books Online, and the MSDN topic id for the Wayback snapshot. This
keeps file names joinable with `data/catalogs/*.tsv`, `data/manifests/*` and
`data/reports/missing-pages.tsv` without any mapping file.

## Source trees and their provenance

* `learn/` — `learn.microsoft.com/en-us/previous-versions/windows/embedded/…`.
  Queues: `queues/mslearn-embedded.txt`, `queues/to-fetch-mslearn.txt`.
  The pages are the archived (read-only) Microsoft Learn copies of the old
  MSDN library.
* `chm/windows-ce-3.0/` — extracted from
  `sources/windows-ce-3.0/WindowsCE3.0_DocumentationArchive.zip`
  (see `sources/windows-ce-3.0/PROVENANCE.md`).
* `msdn-library/techshelps/` — 5,165 pages: the MSDN Library sets for
  Windows CE 1.0/2.0 (CEGUIDE, WCEMFC, WCEATL, VBCE, WCEDDK, VCCE, DNEMBED)
  as mirrored by <https://techshelps.github.io/>; see
  `msdn-library/techshelps/README.md` and `../queues/third-party-sources.md`.
* `msdn-library/datadungeon-2000-04/` — the Windows CE documentation of the
  MSDN Library April 2000, crawled from
  <https://library.thedatadungeon.com/> (`queues/mirrors.tsv`,
  `tools/crawl-mirror.py`).
* `kb/` — 257 Windows CE KnowledgeBase articles from
  <https://github.com/jeffpar/kbarchive>; see `kb/README.md`.
* `mvb/windows-ce-1.0/` — the CE 1.0 Books Online (`PEGSDK.MVB` 1,919 pages,
  `PEGDDK.MVB` 181, `RELNOTES.HLP` 4) decoded from the Multimedia Viewer
  format with helpdeco and converted by `tools/extract-mvb.py`; see
  `mvb/windows-ce-1.0/README.md` and
  `sources/windows-ce-1.0/PROVENANCE.md`.
* `msdn-library/2010-05/` — `web.archive.org` snapshot of
  `msdn.microsoft.com/en-us/library/<id>.aspx` taken 2010-05-01
  (queue: `queues/wayback-msdn-2010.txt`). 161 topics (60 .NET Compact
  Framework, 101 Windows CE 5.0), filed under the *same set directories* as
  the Learn pages they duplicate, because they are a different capture of the
  same documentation (2010 MSDN rendering, not Learn). The set is derived
  from the page id; ids that are not in the corpus are written to
  `msdn-library/2010-05/unclassified/`. 92 further captures that turned out to
  be the Internet Archive's "JavaScript required" interstitial rather than a
  page were removed; `tools/harvest.py` now detects that interstitial and
  retries other capture dates instead of storing it.
* `msdn-library/windows-mobile-6.5/` — 34 Windows Mobile 6.5 topics in MSDN
  Library (MSHelp XML) format; see
  `msdn-library/windows-mobile-6.5/PROVENANCE.md`.
* `win32/` — 20,452 pages from Microsoft's public Win32 documentation
  repositories (`MicrosoftDocs/sdk-api` and `MicrosoftDocs/win32`): the 183
  sdk-api modules that contain a CE-shared API name (5,219 shared pages +
  11,876 context pages) and 3,357 programming-guide pages for the subsystems
  CE implements (files, GDI, Winsock, memory, sync, processes, debugging,
  CryptoAPI, COM, …). Markdown, not HTML; see `win32/README.md`. This is the
  "w32共通部分" of the corpus: the same API is documented on the CE side in
  `learn/` and `chm/`, and `data/reports/win32-shared.tsv` maps one to the
  other, so e.g. `CreateFile` can be read from both angles.

## Regenerating the index

```bash
python3 tools/build-index.py       # data/index/INDEX.tsv
python3 tools/build-index-sql.py   # data/index/corpus.sqlite3
python3 tools/build-gap-report.py  # data/reports/missing-pages.tsv
```
