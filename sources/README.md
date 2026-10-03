# sources/

The verbatim official media the corpus was extracted from — **reference
material, not corpus text**, with one exception: for Windows CE 2.0 the CD's
payload is itself HTML (the "Windows CE Developer" site mirror, 41 pages), and
those files stay here verbatim rather than in `corpus/` because their original
site-relative names (`default.htm`, `prodinfo/vcce.htm`, …) and directory
structure are part of the medium and would collide with the corpus naming
convention (one page id per file). Nothing here is modified: original CHMs, the
WinHelp-era Multimedia Viewer books, the CE 3.0 documentation zip, and the
release-note files that shipped on the same discs. `corpus/` holds the page
text extracted from these sources (plus the Microsoft Learn harvest, which has
no local medium).

Each release directory has a `PROVENANCE.md` recording the Internet Archive
item (or Microsoft Download Center page), the archive URL and file size, the
collection date, exactly which parts were extracted, and what was deliberately
left behind (OS binaries, toolchains, vendor folders — documents only, per the
collection policy in the top-level `README.md`).

| Directory | Medium | Corpus output |
|-----------|--------|---------------|
| `windows-ce-1.0/` | CE 1.0 Desktop Emulation SDK CD: `PEGSDK.MVB`, `PEGDDK.MVB`, `RELNOTES.HLP`, `MSDNLIB.HLP`. | `corpus/mvb/windows-ce-1.0/` (2,104 pages, decoded with helpdeco + `tools/extract-mvb.py`). |
| `windows-ce-2.0/` | CE 2.0 Technical Information CD (Windows CE Developer site mirror, 41 HTML pages). | Pages preserved as-is in `sources/`; no pending extraction. |
| `windows-ce-3.0/` | `WindowsCE3.0_DocumentationArchive.zip` + `Important_ReadMe.txt` (Microsoft Download Center, id 41197). | `corpus/chm/windows-ce-3.0/` (8,962 pages). |
| `windows-ce-4.2/` | CE .NET 4.2 Platform Builder Emulation Edition: `EMULATOR.CHM`, `REMTOOLS.CHM`, release notes. | `corpus/chm/windows-ce-4.2/` (566 pages: the emulator board and remote-tools reference; the 4.x API reference comes from Learn, `corpus/learn/windows-ce-net-4x/`). |
| `windows-ce-5.0/` | CE 5.0 CD1: 98 component CHMs (`P302_wce*.chm` … `P407_*.chm`) + release notes. | `corpus/chm/windows-ce-5.0/` (20,209 pages: the per-component guides and API reference). The Learn harvest (`corpus/learn/windows-ce-5.0/`) shares only 4 of its 20,141 titles, so this is complementary, not a duplicate. |
| `windows-ce-6.0/` | CE 6.0 DVD: release notes (the DVD carries no documentation CHM/HTM set). | Reference only. |

Extracted text is never edited in place; if a source turns out to be wrong,
fix the extraction under `corpus/` and note it in the release's
`PROVENANCE.md`.

## Still sought

Found in web searches but **not downloadable from this working environment**
(outbound network allows only github.com and package registries; the list is
recorded here so a network-enabled run — GitHub Actions or a local machine —
can collect them):

| Source | Where | Why it matters |
|--------|-------|----------------|
| CE 2.0 SDK "Books Online" (Pegasus SDK API reference) | separate SDK CD, sought (see `windows-ce-2.0/PROVENANCE.md`) | the CE 2.0 Win32 API reference (the Technical Information CD has no API reference) |
| CE 5.0 CD5 | <https://archive.org/details/en_win_ce_net_cd5> | further CE 5.0 platform docs beyond CD1 |
| CE 6.0 R2 update | <https://archive.org/details/windows-embedded-ce-6.0-r2> | Platform Builder 6.0 R2 documentation |
| CE 6.0 R3 update | <https://archive.org/details/CE6R3> | CE 6.0 R3 documentation (incl. the 3.5 Compact Framework reference) |
| CE 6.0 Platform Builder SP1 | <https://archive.org/details/windows-embedded-ce-6.0-platform-builder-sp1> + Microsoft Download Center id 4097 (`Release Notes.htm` is a plain file) | Platform Builder 6.0 documentation |
| CE 5.0 Standard SDK | Microsoft Download Center id 17310 (still live) | the CE 5.0 Standard SDK API surface |
| MSDN Library discs (2001–2010) | Internet Archive / WinWorld | the MSDN-era captures of CE 3.0–5.0 reference, including custom-hardware docs |

For page-level material the *queues* are the actionable list, and as of
2026-10 both of them are done: `queues/mslearn-embedded.txt` is exhausted
(`--dry-run` reports 0 to fetch), and `queues/wayback-msdn-2010.txt` — 31,388
captures of the May 2010 MSDN Library — holds the *same topics, id for id*,
as the pages already harvested from learn.microsoft.com: a full pass on
2026-10-02 found 31,226 already in the corpus, 161 stored and one topic
(`ms838324`) the Internet Archive never captured — two requests in total. The next page-level material has to come from sources
that predate or bypass that topic space: the mirror imports
(`corpus/msdn-library/techshelps/`, `corpus/kb/`) and the mirror crawls of the
older MSDN Library editions (`queues/mirrors.tsv`,
`.github/workflows/crawl-mirror.yml`).
