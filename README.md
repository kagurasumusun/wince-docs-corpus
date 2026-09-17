# wince-docs-corpus

Preservation corpus of the **official Microsoft Windows CE (1.0–6.0)
documentation**, collected and maintained for the
[Akari-dev](https://github.com/kagurasumusun/Akari-dev) project (a
Windows CE API surface — headers / .def / import libraries / startup
integration — for building llvm-project against Windows CE targets).

This repository stores **documentation only**. It contains no source
code of Windows CE, no SDK, and no reimplementation.

## Collection policy (see [AGENTS.md](AGENTS.md) for the full rules)

* **In scope — complete collection targets:** the official Microsoft
  public documentation for Windows CE on **MSDN / Microsoft Learn /
  the Wayback Machine** (archived MSDN), plus official Microsoft
  Download Center documentation archives (CHM/HLP).
* **Out of scope — never collected:**
  * shared-source releases, Platform Builder source, Visual Studio
    source (not public documentation);
  * unauthorized non-public information, material of unknown
    provenance or acquisition path, illegal sources, and
    **information derived from binary/device dumps**;
  * Wine, ReactOS, MinGW, mingw-w64, w32api, mingwrt — these are not
    collected and are not used as evidence (the sole exception: the
    **CeGCC-lineage w32api / mingwrt** trees may be consulted as a
    *value-check reference only*, never copied, never as a source of
    declarations);
  * desktop Win32 and desktop .NET Framework reference pages (not
    Windows CE documentation; a former `pagesw/`/`pagesnet/`
    collection was removed on 2026-09-18 under this policy).

## Layout

```
docs/
  mslearn/                          learn.microsoft.com
                                    /en-us/previous-versions/windows/embedded
    windows-ce-net-4x/              Windows CE .NET 4.0/4.1/4.2 books (v=msdn.10)
    windows-ce-5.0/                 Windows CE 5.0 books            (v=msdn.10)
    windows-embedded-ce-6.0/        Windows Embedded CE 6.0 books   (v=winembedded.60)
  chm/
    windows-ce-3.0/                 Windows CE 3.0 library, extracted from the
                                    official Download Center CHM archive (id 41197)
  wayback-msdn/
    2010-05/                        MSDN library pages as archived by the
                                    Wayback Machine on 2010-05-01 (being harvested)
archives/                           official Microsoft documentation archives
  windows-ce-1.0/                   PEGSDK/PEGDDK help files (PROVENANCE.md inside)
  windows-ce-2.0/                   CE 2.0 developer documentation
  windows-ce-3.0/                   WindowsCE3.0_DocumentationArchive.zip (untouched)
  windows-ce-4.2/                   CE 4.2 documentation archive
  windows-ce-5.0/                   CE 5.0 documentation CHM set (101 files)
  windows-ce-6.0/                   CE 6.0 release notes
supplementary/
  windows-mobile-6.5/               Windows Mobile 6.5 (CE 5.2-based platform) pages
                                    extracted from the official WM 6.5 CHM —
                                    kept only where they document CE-platform APIs
data/
  catalogs/                         official per-version TOC snapshots (TSV:
                                    `id(v=tag)<TAB>title`)
  rows/                             requirement-row extractions used by Akari-dev
                                    (title/signature/OS versions/header/library)
  manifests/                        per-book page-id manifests
  index/INDEX.tsv                   master index: id, book, path, title
  harvest/                          harvest logs (fail-*.log)
urls/                               canonical URL queues
  mslearn-embedded.txt              full MSLearn embedded-archive URL set
  wayback-msdn-2010.txt             Wayback 2010-05 MSDN snapshots
  msdn-live.txt                     live msdn.microsoft.com URLs (redirect record)
  to-fetch-mslearn.txt              outstanding MSLearn pages (harvester input)
tools/
  harvest.py                        rate-limited harvester (resume-safe, batch push)
  make-index.py                     regenerates data/index/INDEX.tsv
.github/workflows/harvest.yml       GitHub Actions harness for long harvests
```

## Harvesting

Harvesting is deliberately polite: **one sequential worker per target
site** with a fixed inter-request delay (0.4 s for learn.microsoft.com,
1.5 s for web.archive.org) and exponential backoff on HTTP 429/503.
No parallel scraping, no mass concurrent access.

```sh
python3 tools/harvest.py --queue urls/to-fetch-mslearn.txt --batch 500 --push
python3 tools/harvest.py --queue urls/wayback-msdn-2010.txt --batch 500 --push
python3 tools/make-index.py        # refresh the index after harvesting
```

The harvester is resume-safe (already-stored pages are skipped), so
interrupted runs — local or GitHub Actions — simply continue.

## Session workflow (per the owner's rules)

* At the start of a work session: `git clone` (or `git pull`) this
  repository.
* During the session: harvest, organize, and **push frequently**
  (the harvester commits and pushes every `--batch` pages).
* At the end of the session: everything except the Akari-dev checkout
  is removed from the working environment; the corpus lives here.

## Content origin and license

* Microsoft Learn / MSDN archive pages: © Microsoft Corporation,
  licensed under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/);
  stored verbatim for archival reference — attribution:
  **Microsoft Learn / Microsoft Corporation**.
* Download Center CHM/HLP archives: © Microsoft Corporation, stored
  unmodified with per-directory `PROVENANCE.md` records naming the
  official download page.
* The extraction data in `data/rows/` is factual metadata
  (names, prototypes, requirement rows) transcribed from the pages
  above.
