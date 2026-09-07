# wince-docs-corpus

Preservation repository for the *official* Microsoft Learn / archived
MSDN **Windows CE (1.0–6.0)** documentation pages that the
[wince-api](https://github.com/kagurasumusun/wince-api) project
harvests (Requirement-row-bearing reference pages of the
`learn.microsoft.com/en-us/previous-versions/windows/embedded/...`
archive).

## Purpose

* **Complete preservation**: every page wince-api reads is stored here
  in full (raw HTML), so the corpus survives Learn archive moves and is
  never re-derived from memory.
* **Session workflow**: wince-api working sessions `export` the
  downloaded pages to this repository and `push`; the local copies are
  then **deleted** at the end of the session (per the owner's
  requirement that the pages be saved on GitHub and removed from the
  sandbox). The next session `clone`s this repository and `import`s the
  pages back before harvesting new books.
* **Clean-room boundary**: raw Microsoft Learn HTML is *not* committed
  to the MIT wince-api tree (which stays clean-room); it lives only
  here, in a preservation repository, with attribution.

## Content

```
pages5/<id>.html    CE 5.0 archive pages        (v=msdn.10)           1175
pages6/<id>.html    Windows Embedded CE 6.0     (v=winembedded.60)      38
rows.json           harvested Requirement records (see wince-api)
catalogs/*.tsv      official TOC snapshots per version tree
INDEX.txt           id / file / tree index of every preserved page
```

New trees (CE .NET `(v=msdn.10)` etc.) will be added as
`pages4/...` when wince-api opens those books.

## Tools

`tools/ce-corpus.py` in wince-api implements the round trip:

```sh
# at session start (after cloning this repo):
python3 tools/ce-corpus.py import --corpus <clone>

# before the end of a session (after harvesting new pages):
python3 tools/ce-corpus.py export --corpus <clone>
git -C <clone> add -A && git -C <clone> commit -m "corpus: <count> pages (CE5/CE6)"
git -C <clone> push
```

## Content origin and license

All HTML files are verbatim copies of Microsoft Learn pages
(`learn.microsoft.com/.../previous-versions/windows/embedded/...`),
retrieved for interoperation and archival reference. Microsoft Learn
content is licensed by Microsoft under the
[CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) license —
attribution: **Microsoft Learn / Microsoft Corporation**, retrieved
2026-09; the pages are republished here unmodified as a personal
archival corpus. wince-api's own headers and tools (MIT, © 2026 Akari
API contributors) are separate original work written only from these
pages' *facts* (interface names, Requirements rows, documented
semantics) and live in the wince-api repository.
