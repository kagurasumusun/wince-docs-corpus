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
| `windows-ce-1.0/` | CE 1.0 Desktop Emulation SDK CD: `PEGSDK.MVB`, `PEGDDK.MVB`, `RELNOTES.HLP`, `MSDNLIB.HLP`. | Not extracted yet (Multimedia Viewer books). |
| `windows-ce-2.0/` | CE 2.0 Technical Information CD (Windows CE Developer site mirror, 41 HTML pages). | Pages preserved as-is in `sources/`; no pending extraction. |
| `windows-ce-3.0/` | `WindowsCE3.0_DocumentationArchive.zip` + `Important_ReadMe.txt` (Microsoft Download Center, id 41197). | `corpus/chm/windows-ce-3.0/` (8,962 pages). |
| `windows-ce-4.2/` | CE .NET 4.2 Platform Builder Emulation Edition: `EMULATOR.CHM`, `REMTOOLS.CHM`, release notes. | Reference only — the 4.x API reference comes from Learn (`corpus/learn/windows-ce-net-4x/`). |
| `windows-ce-5.0/` | CE 5.0 CD1: 98 component CHMs (`P302_wce*.chm` … `P407_*.chm`) + release notes. | Reference only — CE 5.0 pages in the corpus were harvested from Learn. |
| `windows-ce-6.0/` | CE 6.0 DVD: release notes (the DVD carries no documentation CHM/HTM set). | Reference only. |

Extracted text is never edited in place; if a source turns out to be wrong,
fix the extraction under `corpus/` and note it in the release's
`PROVENANCE.md`.
