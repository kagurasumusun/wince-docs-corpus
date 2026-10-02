# corpus/mvb/windows-ce-1.0/

Windows CE 1.0 documentation, extracted from the **Multimedia Viewer books**
(and one WinHelp file) that shipped on the CE 1.0 Desktop Emulation SDK CD. This
is the earliest CE documentation in the corpus, and the only CE 1.x material
that exists: Microsoft never published it on the Web.

| Directory | Pages | Source medium | Content |
|-----------|------:|---------------|---------|
| `PEGSDK/` | 1,919 | `PEGSDK.MVB` (5.3 MB) | Pegasus SDK Books Online — the CE 1.0 SDK / Win32 API reference (Winsock, GDI, windowing, memory, files, …) |
| `PEGDDK/` | 181 | `PEGDDK.MVB` (0.4 MB) | Pegasus DDK Books Online — the CE 1.0 driver and kernel reference |
| `RELNOTES/` | 4 | `RELNOTES.HLP` | Release notes for the Pegasus DDK Books Online (known problems, performance notes) |

2,104 pages in total. The media itself is preserved under
`sources/windows-ce-1.0/` (`sources/windows-ce-1.0/PROVENANCE.md`).

## How these pages were produced

`.MVB` is Microsoft's Multimedia Viewer book format and `.HLP` is WinHelp —
neither is HTML, and no official unpacker exists. The books were decoded with
[helpdeco](https://github.com/pmachapman/helpdeco) 2.1.4
(commit `7852737`, GPL), which walks the internal B-trees, decompresses the
topic text and writes an RTF rendition with the help footnotes intact
(`$` = topic title, `#` = topic id, hidden `\v` text = jump targets):

```bash
# helpdeco writes the RTF into the current directory
mkdir -p /tmp/mvb && cd /tmp/mvb
helpdeco -y ../../../sources/windows-ce-1.0/PEGSDK.MVB   # -> PEGSDK.rtf

# one page per topic (page id = the topic's first # id)
python3 ../../../tools/extract-mvb.py --rtf /tmp/mvb/PEGSDK.rtf \
    --book PEGSDK --medium PEGSDK.MVB --out corpus/mvb/windows-ce-1.0
```

The same commands with `PEGDDK.MVB` / `RELNOTES.HLP` produce the other two
directories. `PEGSDK.MVB` and `PEGDDK.MVB` need a one-line fix in helpdeco's
`my_malloc` (it aborts on a zero-byte allocation), which is why the exact
commit is recorded above. `RELNOTES.HLP` is decoded with `-y` so that
helpdeco does not stop at its "overwrite bm0.bmp?" prompt.

One page appears twice in `PEGSDK/` (`AB30G.html`, `AB93G.html` —
`GetColumnProperties` under two different headings); both are kept, which is
why `data/reports/duplicates.tsv` reports a single duplicate group.

`tools/extract-mvb.py` converts the RTF to HTML: one file per `\page`, named
after the topic's context id (`AB5A.html`, `BB0A.html`), title in
`<title>`/`<h1>`, RTF tables → `<table>`, tabs → spaces, hidden link anchors
and `{bmc …}` / `{ewc …}` bitmap directives dropped. **Images are not
converted** (helpdeco writes them as separate BMP/WMF files next to the RTF);
the pages therefore carry the text and tables of the original books, not the
screenshots and diagrams.

## Not extracted

* `MSDNLIB.HLP` (112 topics) is the viewer help of the *Development Library*
  (how to open books, define search ranges, …), not CE documentation, so it
  stays unextracted in `sources/`.
* The CE 1.0 SDK's sample code and the toolchain on the same CD are out of
  scope (documents only, per the collection policy in the top-level README).
