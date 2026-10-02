# corpus/msdn-library/datadungeon-2000-04/

The **Windows CE documentation of the MSDN Library, April 2000**, crawled from
<https://library.thedatadungeon.com/> (a documentation mirror run by the
author of the DirectX reference site; contact hogsy@oldtimes-software.com).
The April 2000 Library is the CE 2.12/3.0 era: it documents the CE device
driver kit, the CE MFC/ATL libraries, the Handheld PC and Palm-size PC SDKs,
Auto PC, Mobile Channels and the CE API reference — material that the
learn.microsoft.com harvest only covers in its later (CE 4.x/5.0) revisions.

The crawl starts at `_toc/toc0_3.html` (the "Windows CE Documentation" table
of contents) plus the introduction and glossary pages, and follows links into
the book folders that the tables of contents themselves point at, so the
other sections of the same Library (Visual Studio, Office, Platform SDK,
Books…) are not touched. Original relative paths are kept:

```
_toc/toc0_3*.html        the table of contents tree
wceintro/, wcegloss/     introduction, glossary
wcecore/, wcecomm/, wceui/, wcesvcs/, wceglob/     the SDK guide
wcemfc/, wceatl/, vcce/, vbce/, wceddk/, wcesdkr/  tools and libraries
wcehpc/, wceapc/, mobchan/, adoce/, _alts/         platform-specific guides
```

## What is stored (and what is not)

The mirror serves every document twice: `X.htm` is a small frameset page (the
site's header bar, the library table of contents in one iframe, the document
in another) and `X.content.htm` is the document itself. Only the documents are
kept — the crawler rewrites a link to `X.content.htm`, walks the wrapper when
there is no such page, and skips both the wrapper chrome and the `_alts/`
"other versions of this page" lists (navigation into the mirror's other
library editions). Everything is re-encoded from the mirror's Windows-1252 to
UTF-8, and the files keep the mirror's own names and relative paths.

## How it is collected

* `tools/crawl-mirror.py` with the `datadungeon-ce` entry of
  `queues/mirrors.tsv`; the workflow `.github/workflows/crawl-mirror.yml`
  runs it on demand, daily (20:30 UTC, after the harvester) and whenever
  `queues/mirrors.tsv` changes.
* Politeness: one request at a time, 2.5 s apart, ~24 pages/minute. The
  site's robots.txt disallows named AI-training crawlers (GPTBot, ClaudeBot,
  anthropic-ai, Amazonbot, CCBot, Google-Extended) — not this one; the crawler
  uses the honest `wince-docs-corpus-harvester` user agent and honours the
  file, and backs off when a server asks for it.
* Progress lives in `data/crawl/datadungeon-ce.json` (committed), so runs are
  split at 600 pages and continue where the last one stopped; a finished tree
  is never fetched twice.
* This is a mirror, not an official Microsoft download: it belongs to
  `corpus/msdn-library/` with the other mirror copies, see
  `../../../queues/third-party-sources.md`. An alternative, offline source
  for the same material would be the MSDN Library April 2000 DVD on
  archive.org (`MSDN_Library_April_2000_DVD`), which the mirror itself
  documents as its origin.

Crawled so far: 271 pages — 202 tables of contents, 66 documents and the
glossary, from 600 requests (first run, 2026-10-02). The frontier
(`data/crawl/datadungeon-ce.json`) has 4,149 URLs queued, most of them the CE
SDK reference (`wcesdkr/`), the programming guides (`wcecore/`, `wceui/`,
`wcecomm/`, `wcesvcs/`) and the remaining tables of contents.
