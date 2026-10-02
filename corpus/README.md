# corpus/

The documentation text, one HTML file per page, grouped by **source** and then
by **documentation set**:

```
corpus/
├── learn/<set>/          pages harvested from learn.microsoft.com
├── chm/windows-ce-3.0/   pages extracted from the official CE 3.0 CHM
├── wayback-msdn/2010-05/ pages recovered from the Internet Archive
└── msdn-library/windows-mobile-6.5/  MSHelp-format Windows Mobile 6.5 topics
```

Total: 77,953 pages.

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
topic name for CE 3.0, and the MSDN topic id for the Wayback snapshot. This
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
* `wayback-msdn/2010-05/` — `web.archive.org` snapshot of
  `msdn.microsoft.com/en-us/library/<id>.aspx` taken 2010-05-01
  (queue: `queues/wayback-msdn-2010.txt`). These 253 .NET Compact Framework
  topics are kept next to the Learn copies because they are a different
  capture of the same documentation (2010 MSDN rendering, not Learn).
* `msdn-library/windows-mobile-6.5/` — 34 Windows Mobile 6.5 topics in MSDN
  Library (MSHelp XML) format; see
  `msdn-library/windows-mobile-6.5/PROVENANCE.md`.

## Regenerating the index

```bash
python3 tools/build-index.py       # data/index/INDEX.tsv
python3 tools/build-index-sql.py   # data/index/corpus.sqlite3
python3 tools/build-gap-report.py  # data/reports/missing-pages.tsv
```
