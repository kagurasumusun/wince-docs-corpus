# corpus/win32/

The **Win32-common** half of the documentation: the pages of Microsoft's public
Win32 API reference (`MicrosoftDocs/sdk-api`) whose API name Windows CE also
documents. They are kept next to the CE-specific material so that both halves
of an API question are in one place.

```
corpus/win32/
└── api/<module>/<page>.md     Win32 API reference (5,279 pages)
```

**5,279 pages for 5,068 CE-documented API names.** Nothing else is here — there
is no "module context" ring and no programming-guide tree. The desktop
siblings of a shared API (the Shell, DirectX, WMI, WinRT, Windows Media,
DirectShow filters CE never had, …) are another product's documentation, and
the Win32 *programming guides* of `MicrosoftDocs/win32` describe desktop
Windows (transactional NTFS, change journals, the desktop service control
manager), so neither belongs in a Windows CE corpus.
`tools/check-policy.py` enforces exactly that: every markdown page under
`corpus/win32/` must be a sdk-api page whose name CE documents.

Format is the upstream markdown (YAML front matter with `title`, `description`,
`helpviewer_keywords`, `ms.assetid`, …) — not HTML like the rest of the corpus.
The upstream commit, licenses and the snapshot are documented in
`sources/microsoftdocs/PROVENANCE.md`; extraction is reproducible with
`python3 tools/fetch-upstream.py subset --source sdk-api`.

## How a page gets here

A page is imported when its API name — or, for an `A`/`W` variant, the base
name — is an API name Windows CE's own documentation uses:

* **`CreateFile` → `CreateFileA`, `CreateFileW`.** Windows CE documents
  `CreateFile`; sdk-api publishes the ANSI and Unicode pages, so both come
  along.
* The name list is built and audited by `tools/ce_api_names.py` from
  `data/catalogs/*.tsv` (the page titles of the CE 3.0/5.0/.NET 4.x/6.0 product
  documentation) plus the names mined from the CE sets that have no catalog —
  CE 1.0/2.0 Books Online, the MSDN Library CE sets, the CE 2.11/2.12 SDK, the
  2010-05 capture, Windows Mobile 6.5 and the KnowledgeBase
  (`data/reports/ce-api-names.tsv` prints every name with its CE page ids).
* `data/win32-exclude.tsv` removes the reviewed coincidences — two name
  matches (`Run (Windows Media Player)` is not the printer-driver `RUN`
  structure; the device-driver `Address` of the CE 3.0 DDK is not the dbghelp
  `ADDRESS` structure) and seven modules that document an API family Windows CE
  never had (Windows Runtime, Direct2D, the shim-database `TAG` macro, Windows
  Contacts, the desktop Task Scheduler, Core Audio device topology, display
  cloning).

Nothing is included "for context": if Windows CE does not document the name,
the page stays out, however closely related it looks.

## The reports

| Report | Columns | What it answers |
|--------|---------|-----------------|
| `data/reports/win32-shared.tsv` | `name`, `ce_sets`, `ce_page_ids`, `win32_pages` | which part of Win32 Windows CE shares, and where each side is |
| `data/reports/win32-imported.tsv` | `path`, `module`, `kind`, `name`, `ce_sets`, `ce_page_ids` | the evidence for every imported page: the CE page(s) that document its API |
| `data/reports/ce-api-names.tsv` | `name`, `ce_sets`, `ce_page_ids`, `sources` | the name list the import is derived from, including names no sdk-api page exists for |

```bash
grep -P '^createfile\t' data/reports/win32-shared.tsv
corpus/win32/api/fileapi/nf-fileapi-createfilew.md   # -> CE: aa517318(v=msdn.10), ee490417(...), ...
python3 tools/find-api.py CreateFile                 # the same lookup across CE + Win32
```

Kinds in the file names: `nf` function, `ns` structure/union, `ne`
enumeration, `nc` callback, `nn` interface, `ni` control code, `nl`
class/library, `na` attribute (upstream's own prefixes, kept so a page can be
traced back to the snapshot without a mapping file).

## The desktop reading, outside the corpus

The generic Win32 programming guides are useful background — and they are
desktop documentation, not CE documentation. They are therefore *not* in the
corpus, but they can still be extracted as an offline extra:

```bash
python3 tools/fetch-upstream.py guides --out .cache/win32-guides
```

`.cache/` is git-ignored, so the guides stay out of the repository (and
`tools/check-policy.py` reports them if they are ever copied into `corpus/`).

## Caveats

* These are **desktop Win32** pages. They describe the full Windows API, which
  is a superset of what Windows CE implements — a page here is a *reference*,
  not proof that a given CE version has the API. The CE page (in
  `corpus/learn/<set>/`) or the CE CHM topic is the authority on that; where
  the two disagree, the CE page wins. Typical divergences: transactional NTFS
  and reparse points (not on CE), the services/power models, and anything
  introduced after CE 6.0.
* The pages carry upstream front matter (`ms.assetid`, `helpviewer_keywords`,
  `old-location`) — useful for matching a topic to old MSDN/CHM ids.
  `data/index/INDEX.tsv` and the SQL index include these pages with ids such as
  `nf-fileapi-createfilew` and book `win32/api/fileapi`.
* Windows CE documents some of these APIs only in one release (for example
  `corpus/chm/windows-ce-3.0/` for the CE 3.0 era); `ce_sets` in the reports
  says which sets document the name, and `data/catalogs/*.tsv` joins a name to
  its CE page.
