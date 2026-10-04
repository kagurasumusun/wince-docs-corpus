# corpus/

The documentation text, one page per file, grouped by **source** and then by
**documentation set**. Harvested/extracted pages are HTML; the Win32 material
imported from MicrosoftDocs is markdown (`win32/`), as Microsoft publishes it
that way:

```
corpus/
├── learn/<set>/              CE pages harvested from learn.microsoft.com
├── chm/windows-ce-3.0/       pages extracted from the official CE 3.0 CHM
├── chm/windows-ce-5.0/       the 98 component CHMs of the CE 5.0 CD1
├── chm/windows-ce-4.2/       emulator + remote tools CHMs of CE .NET 4.2
├── mvb/windows-ce-1.0/       CE 1.0 books (Multimedia Viewer/WinHelp era)
├── mvb/windows-ce-2.0-sdk/   CE 2.0 SDK (H/PC) debugger reference + disc ReadMe
├── kb/                       Windows CE KnowledgeBase articles (CE 1.0/2.0 era)
├── site/<set>/               pages of the CE-era web sites that came with the media
├── dotnet/<set>/             the .NET families, documented on top of Windows CE
├── win32/api/                the Win32-common API reference (MicrosoftDocs)
└── msdn-library/
    ├── 2010-05/<set>/        Internet Archive copies of MSDN topics
    ├── techshelps/<set>/     MSDN Library CE 1.0/2.0 sets (techshelps mirror)
    ├── datadungeon-2000-04/  MSDN Library April 2000 CE documentation (crawled)
    ├── wcedevcon-99/         CE 2.11/2.12 SDK/DDK docs of the DevCon '99 disc
    └── windows-mobile-6.5/   MSHelp-format Windows Mobile 6.5 topics
```

Total: 121,039 pages = **105,103 CE pages + 10,657 .NET pages + 5,279
Win32-common pages** (as of 2026-10-04; the April 2000 crawl is still
running). The CE trees are `learn/`, `chm/`, `mvb/`, `kb/`, `site/` and
`msdn-library/`; `dotnet/` is separated because it documents a layer on top of
Windows CE, not the OS its include/def files describe — see
`dotnet/README.md`. For provenance, see
the per-tree READMEs for the provenance of each, and `../queues/
third-party-sources.md` for the mirror policy. What may be collected at all is
`../docs/COLLECTION-POLICY.md`; `../tools/check-policy.py` enforces it.

## Sets under `corpus/learn/` (58,046 pages)

| Set | Pages | Contents |
|-----|------:|----------|
| `windows-ce-5.0` | 24,694 | Windows CE 5.0 product documentation and API reference. |
| `windows-embedded-ce-6.0` | 23,714 | Windows Embedded CE 6.0 documentation and API reference. |
| `windows-ce-net-4x` | 8,969 | Windows CE .NET 4.0/4.1/4.2 topics (native API, drivers, guides). |
| `windows-embedded-compact-7` | 256 | Windows Embedded Compact 7 remote-tools reference (`(Compact 7)`). |
| `unclassified` | 413 | Set could not be determined from page metadata. |

(sdk-api used to contain the same page id in several modules —
`winsock`/`winsock2` and the `A`/`W` variants of a name — so a few hundred page
ids repeat; the SQL index keys pages by path.)

`unclassified/` is a deliberate holding area, not a junk drawer: the 413 pages
are Windows CE 2.12/3.0-era native API topics (e.g. `dprintf`,
`IeXdiARMContext::GetContext`) that predate the per-edition catalogs, .NET Micro
Framework class pages whose namespace is not in the title, and topics that only
shared the `previous-versions/windows/embedded` namespace. Every page in the
tree comes from that namespace (checked 2026-10 against the canonical URL of
each page); one page whose *content* was about another product (`ms866183`,
Microsoft Commerce Server) was removed in the 2026-10 review.

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
| `(Microsoft.PointOfService …)` | `dotnet/pos-for-net` |
| `(Microsoft.SPOT …)` / `(Microsoft.Web.Services …)` / `(Ws …)` / `(Dpws …)` / `(System.Ext …)` | `dotnet/dotnet-micro-framework` |
| `(System …)` / `(Microsoft …)` / `(… Method\|Property\|Class\|…)` | `dotnet/dotnet-compact-framework` |
| `(Windows Mobile <ver>)` | `windows-mobile-<ver>` |
| anything else | `uncategorized` → files land in `unclassified/` |

The table is the single source of truth for both the code and this document;
if you change `BOOK_RULES` in `tools/harvest.py`, update this table. The .NET
rules put their pages under `corpus/dotnet/` (`DOTNET_SETS` in the same tool);
everything else goes under `corpus/learn/`.

## Sets under `corpus/dotnet/` (10,657 pages)

| Set | Pages | Contents |
|-----|------:|----------|
| `pos-for-net` | 5,793 | POS for .NET (`Microsoft.PointOfService`) reference and guides. |
| `dotnet-micro-framework` | 4,012 | .NET Micro Framework (`Microsoft.SPOT.*`, `Ws.*`, `Dpws.*`, `System.Ext.*`, WSD/DPWS stack). |
| `dotnet-compact-framework` | 852 | .NET Compact Framework class-library pages (`System.*` namespaces). |

This is a managed-code layer: its records stay in the knowledge base with
`layer: "dotnet"` and are kept out of the CE include/def surface
(`knowledge/README.md`).

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
* `chm/windows-ce-5.0/` and `chm/windows-ce-4.2/` — the documentation CHMs of
  those two releases, extracted from the official media in `sources/`
  (`tools/extract-chm.py`); see the tree READMEs for what each adds over the
  Learn harvest.
* `msdn-library/techshelps/` — 5,165 pages: the MSDN Library sets for
  Windows CE 1.0/2.0 (CEGUIDE, WCEMFC, WCEATL, VBCE, WCEDDK, VCCE, DNEMBED)
  as mirrored by <https://techshelps.github.io/>; see
  `msdn-library/techshelps/README.md` and `../queues/third-party-sources.md`.
* `msdn-library/datadungeon-2000-04/` — the Windows CE documentation of the
  MSDN Library April 2000 (CE 2.12/3.0 era), crawled from
  <https://library.thedatadungeon.com/> (`queues/mirrors.tsv`,
  `tools/crawl-mirror.py`); 2,931 pages of it are collected so far and the
  crawl continues twice a day where it stopped
* Nothing in `corpus/` is source code: the trees hold pages only, and a medium
  is never unpacked into the corpus (see "What is collected" in the top-level
  `README.md`; `tools/check-corpus.py` reports a `source_files` count and
  `tools/check-policy.py` fails on one).
* `kb/` — 257 Windows CE KnowledgeBase articles from
  <https://github.com/jeffpar/kbarchive>; see `kb/README.md`.
* `mvb/windows-ce-2.0-sdk/` — 293 pages of the Microsoft Windows CE Platform
  SDK (H/PC) 2.0 disc (02/98, Internet Archive `MPLATSDK.20`): the CE debugger
  reference (`windbg.hlp`, 292 pages) and the disc's ReadMe. The disc's
  InfoViewer Books Online (`.ivt`) is not decodable yet; the SDK itself
  (headers, libraries, samples) is deliberately not imported. The medium is
  fetched to a scratch directory and discarded — see
  `mvb/windows-ce-2.0-sdk/README.md`.
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
* `msdn-library/wcedevcon-99/` — 6,382 pages of the Windows CE 2.11/2.12 SDK,
  DDK and Platform Builder documentation on the DevCon '99 conference disc
  (Internet Archive item `windowscedevcon99conferencecd`). The disc's sponsor
  pages, sample trees, desktop Media Player 2 help and FrontPage metadata are
  refused by the exclude regex in `queues/media.tsv` — see
  `msdn-library/wcedevcon-99/PROVENANCE.md`.
* `site/` — 44 pages imported from the CE-era web sites that came with the
  media (`sources/windows-ce-2.0/developer/` — the CE 2.0 developer site,
  including the w32model, comm_mod, porting and mgdi guides — plus the CE
  4.2/5.0/6.0 pages that were still only under `sources/`), by
  `tools/import-site.py` from `queues/site-sets.tsv`; see
  `data/reports/site-imported.tsv` for the receipt. The site is a whole
  product site, so its shop window (press releases, order/download/feedback
  pages, partner and logo programmes, case studies) is refused by the tree's
  exclude regex and recorded, page by page, in
  `data/reports/site-excluded.tsv`.
* `win32/` — 5,279 pages from Microsoft's public Win32 API reference
  (`MicrosoftDocs/sdk-api`, pinned commit): every sdk-api page whose API name
  Windows CE documents, including the `A`/`W` variants of a shared base name.
  Markdown, not HTML; see `win32/README.md`. This is the "Win32-common" half
  of the corpus: the same API is documented on the CE side in `learn/`, `chm/`
  and `msdn-library/`, and `data/reports/win32-shared.tsv` maps one to the
  other, so e.g. `CreateFile` can be read from both angles. The desktop-only
  context of those modules and the desktop Win32 programming guides are *not*
  part of the corpus (`../docs/COLLECTION-POLICY.md`).

## Regenerating the index

```bash
python3 tools/build-index.py       # data/index/INDEX.tsv
python3 tools/build-index-sql.py   # data/index/corpus.sqlite3
python3 tools/build-gap-report.py  # data/reports/missing-pages.tsv
python3 tools/check-policy.py      # the collection policy (must print OK)

# knowledge/ is built from the indexed pages: python3 tools/build-kb.py
```
