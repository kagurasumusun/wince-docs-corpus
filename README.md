# wince-docs-corpus

Preservation repository for the *official* Microsoft **Windows CE (1.0–6.0)**
documentation that the [wince-api](https://github.com/kagurasumusun/wince-api)
project harvests: the Microsoft Learn / archived-MSND `previous-versions` pages
(`learn.microsoft.com/en-us/previous-versions/windows/embedded/...`), plus the
official **Windows CE 3.0 Technical Documentation** CHM archive from the
Microsoft Download Center (id 41197), which is the complete CE 1/2/3 reference.

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
pages3/<id>.html    Windows CE 3.0 library      (Download Center CHM) 8962
pages4/<id>.html    CE 4.x archive pages        (v=msdn.10)
pages5/<id>.html    CE 5.0 archive pages        (v=msdn.10)
pages6/<id>.html    Windows Embedded CE 6.0     (v=winembedded.60)
pagesw/             desktop Win32 reference pages (current Learn naming)
pageswm/            Windows Mobile 6.5 pages
pagesmag/           MSDN Magazine articles
pagesnet/           .NET Framework 3.5 (v=vs.90) class-library pages
                    harvested for the CE .NET (Compact) Framework
                    surface (M102b; see wince-api tools/cf-harvest.py)
ce30/               official CE 3.0 CHM archive + provenance (see ce30/PROVENANCE.md)
coredll/            coredll.def export lists
rows.json           harvested Requirement records (CE 5.0; see wince-api)
rows3.json          harvested CE 3.0 records (title/sig/os/versions/header/lib)
rows4.json          harvested Requirement records (CE 4.x)
rows-prints.json    the code prints that the Requirement-row harvest
                    drops: ce-fetch.py records a page's code block only
                    when it is call-shaped (`NAME(`), so pages whose
                    print is a plain typedef / tagged definition /
                    #define reached rows*.json with an empty `sig`.
                    Regenerated from the preserved pages below by
                    wince-api tools/ce-prints.py (80 records: 78 tagdef,
                    2 typedef; 3,394 pages print no declaration of their
                    own title, which is the measured basis of the hold
                    policy).
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

## Tree provenance notes (M52)

* `pagesw/` -- desktop Win32 reference pages fetched from
  learn.microsoft.com/windows/win32/api (fixed-ABI value sources for
  the wince-api M52 derived-value policy; per-item derivation paths in
  wince-api docs/inventory.md M52).
* `pageswm/` -- Windows Mobile 6.5 documentation pages extracted from
  the official Microsoft Download Center CHM
  (https://download.microsoft.com/download/d/5/3/d532530a-507f-488e-9747-1f8757071d92/windowsmobile6.5.chm,
  linked from https://learn.microsoft.com/en-us/previous-versions/windows/embedded/dn887939(v=msdn.10)).
  The CHM is not committed (63 MB); the URL is the durable official
  source.  Pages are named wm65-&lt;title&gt;.html after their CHM topic
  titles.

## M53 (2026-09-09)

- pages5 +82: the CE 5.0 Standard Shell Reference book
  (`tools/manifests/stdshell.manifest` in wince-api: 21 functions +
  2 callbacks, 10 structures, 33 interface-method pages, SHGNO, 2
  macros, 17 messages).
- pages6 +2: ee504556 (SHGNO) and ee505480 (SHFILEOPSTRUCT) twins
  grounding the M53 held-value analysis.  Observation recorded: the
  WM 6.5 SHRecognizeGesture page's "Windows Embedded CE 6.0 R3" GUID
  link now resolves to a Consolidated 2013 revision at
  ee503202(v=winembedded.80) with the same body; the corpus keeps the
  generation-correct ee503202(v=winembedded.60) CE 6.0 page (verified
  still live 2026-09-09).
- pagesw +14: the desktop Win32 derivation-source pages for the M53
  fixed-ABI value derivations (list:
  `tools/manifests/stdshell-desktop.manifest` in wince-api).
- pageswm +3: wm65-NMRGINFO, wm65-GN_CONTEXTMENU,
  wm65-NM_RECOGNIZEGESTURE (the sole official sources for the M53
  gesture supplement; no CE-side page exists).
- rows.json 2151 -> 2233 (+82).  INDEX 9828 -> 9929.
