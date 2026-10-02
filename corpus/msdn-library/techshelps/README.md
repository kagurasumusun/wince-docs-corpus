# corpus/msdn-library/techshelps/

The Windows CE documentation sets of the **MSDN Library** as mirrored by
<https://techshelps.github.io/> (repository
<https://github.com/techshelps/techshelps.github.io>, `main`, HEAD
`dbd21c49bbe919fd089084f2a5dd90a602685ba1`). The mirror is a decompiled copy
of MSDN Library editions from the late 1990s — the ones that documented
**Windows CE 1.0 and 2.0**, which Microsoft never published on the Web and
which no other tree of this corpus covers.

| Directory | Pages | Contents |
|-----------|------:|----------|
| `CEGUIDE/` | 973 | Windows CE Guide (SDK guide: core, comms, UI services, API reference intros) |
| `WCEMFC/` | 2,246 | Microsoft Foundation Classes for Windows CE |
| `WCEATL/` | 744 | Active Template Library for Windows CE |
| `VBCE/` | 672 | Visual Basic for Windows CE (toolkit reference, eVB) |
| `WCEDDK/` | 339 | Windows CE Device Driver Kit |
| `VCCE/` | 105 | Visual C++ for Windows CE |
| `DNEMBED/` | 86 | Embedded/Windows CE development topics |

5,165 pages in total. They are third-party mirror copies rather than an
official Microsoft download, which is why they live in their own directory:
`corpus/msdn-library/` is the collection of *mirror* copies of CE
documentation, as opposed to `corpus/learn/`, `corpus/chm/` and `corpus/mvb/`,
which were harvested or extracted from Microsoft's own material.

## What was changed

* The mirror injects a Google Analytics snippet
  (`googletagmanager.com/gtag/js?id=UA-83731338-2`) into every page; it was
  removed during import. The pages are otherwise byte-identical to the mirror
  (original `Windows-1252` markup re-encoded to UTF-8).
* The MSDN Library "Topic Not Found" placeholder pages (`notopic*.htm`) are
  skipped by the importer: they are navigation failures, not documentation.
* Images (`*.gif`) and style sheets are **not** imported: this tree is the
  documentation text.
* File names and the per-set folder structure are the mirror's; inside
  `CEGUIDE/` the original `devdoc/good/wince/` depth is kept.

Re-import (the 802 MB repository is fetched partially, only the CE sets):

```bash
python3 tools/import-techshelps.py --clone --cache-dir .cache/techshelps
```

or, from an existing clone, `python3 tools/import-techshelps.py --src <clone>`.
`--list` prints the per-set page counts; `--dry-run` writes nothing.
