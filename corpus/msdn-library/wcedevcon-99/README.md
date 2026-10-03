# corpus/msdn-library/wcedevcon-99/

The documentation on the **Windows CE Developers Conference (DevCon '99)
Conference CD** — 7,437 pages from the disc Microsoft handed out at the
conference (24 May 1999), Internet Archive item
[`windowscedevcon99conferencecd`](https://archive.org/details/windowscedevcon99conferencecd).
The disc carries the **Windows CE 3.0 SDK documentation in HTML**, the CHMs of
the same components, and the conference's own site.

| Directory | Pages | What it is |
|-----------|------:|------------|
| `wcesdkr/` | 3,315 | Windows CE 3.0 **SDK Reference** — the Win32 API of CE 3.0 (window, graphics, file, registry, socket, … functions) |
| `wceapc/` | 995 | **Auto PC** SDK documentation (the Auto PC Win32 subset and its controls) |
| `wceddk/` | 741 | Windows CE 3.0 **Device Driver Kit** reference — driver and kernel APIs |
| `wcesdkg/` | 456 | Windows CE 3.0 **SDK Guide** — the programming guide that goes with the reference |
| `wcecomm/` | 244 | Communications reference (WinSock, RAS, TAPI, infrared) |
| `wceui/` | 188 | User-interface reference and guides |
| `MPLAYER2/` | 174 | Windows Media Player 2 control, for CE (CHM component) |
| `wcehpc/` | 143 | Handheld PC Pro (CE 2.11/3.0) SDK documentation |
| `wcecore/` | 91 | Core OS reference (memory, processes, threads, files) |
| `wcesvcs/` | 86 | System services reference |
| `wceppc/` | 70 | Palm-size PC SDK documentation |
| `Handhelds/` | 29 | Handheld-device hardware notes (CHM component) |
| `wcegloss/`, `wceglob/`, `wceintro/`, `wcelib/` | 53 | Glossary, overview, introduction and library notes |
| `ACCESSIB/`, `MPSUPP/` | 9 | Accessibility and multimedia-supplement notes (CHM components) |
| `Windows_CE_Developers_Conference_DevCon_99_Conference_CD/` | 839 | the conference site on the disc: agenda, keynotes, tracks, sessions, sponsors, the `qworks/` material and the SDK/readme pages that sit in its component trees |

The books are the same titles the MSDN Library carried in 1999–2000, so many of
these pages duplicate (textually) what `../datadungeon-2000-04/` has crawled —
and they cover most of what that crawl still had queued. The queued URLs were
checked book by book before anything was dropped (`tools/mark-crawl-covered.py`
compares the pages both sides already hold; the two editions differ by a word
here and there, so a page id alone is not proof):

| Book | Queued on the mirror | Verdict |
|------|---------------------:|---------|
| `wcesdkr` | 3,244 | covered (98% of ids present, sampled pages identical) |
| `wceapc` | 740 | covered |
| `wceddk` | 741 | covered |
| `wcecomm`, `wcecore`, `wceglob` | 253 | covered |
| `wcemfc`, `wceatl` | 3,455 | **not covered** — the disc has no CE MFC/ATL books |
| `wcegloss` | 24 | **not covered** — the editions split the glossary into different pages |
| `vbce`, `_toc`, `wceui`, `wcesvcs`, `wcehpc`, `wceppc`, `mobchan` | ~540 | not covered |

4,978 URLs were dropped from the frontier — see `queues/mirrors.tsv` and
`data/reports/crawl-covered.tsv` — so the mirror is not asked again for
documentation the corpus already has, and the crawl (twice a day,
`../datadungeon-2000-04/README.md`) finishes the rest.

## What was imported, and what was not

`queues/media.tsv` runs this disc through `tools/import-media.py` with the
action `import-scratch`: the 338 MB ISO is downloaded to a scratch directory,
its documentation is copied out, and the image is discarded (the runner caches
it between runs, and `data/reports/media-imported.tsv` records that the import
is done). Of the 9,433 files on the disc:

* **imported** — the HTML documentation books, the 37 component CHMs (unpacked
  with 7z by `tools/extract-chm.py`) and 3 WinHelp books (`ACCESSIB.HLP`,
  `MPSUPP.HLP`, `mplayer2.hlp`, decoded with helpdeco);
* **excluded by the queue's regex** — FrontPage's per-file metadata
  (`_vti_cnf/`, 427 tiny property files: the disc was published from a
  FrontPage web).  They are not documentation, and they were the tree's only
  "HTML without an end tag" warnings;
* **skipped and counted** — the conference disc's samples and toolchain:
  1,082 `.h`, 945 `.cpp`, 657 `.dll`, 324 `.lib`, 202 `.rc`, 115 `.dsp`,
  110 `.pdb`, … i.e. the SDK itself. Headers, libraries and sample sources are
  not part of this corpus (see "What is collected" in the top-level
  `README.md`).

## Provenance

`PROVENANCE.md` in this directory records the Internet Archive item, the file
name, size and md5 of the image the pages came from, and that the medium itself
is not kept. The run's own output is `data/reports/media-last.txt`.
