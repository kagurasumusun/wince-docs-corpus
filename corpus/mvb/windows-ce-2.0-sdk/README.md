# corpus/mvb/windows-ce-2.0-sdk/

Windows CE 2.0 documentation extracted from the **Microsoft Windows CE Platform
SDK (H/PC) 2.0** disc (02/98), Internet Archive item
[`MPLATSDK.20`](https://archive.org/details/MPLATSDK.20). This is the H/PC
edition of the CE 2.0 Platform SDK — the toolchain, headers and samples of the
release, with the documentation that shipped on the same disc.

| Directory | Pages | Source file | Content |
|-----------|------:|-------------|---------|
| `WINDBG/` | 292 | `windbg.hlp` (WinHelp) | Windows CE debugger reference — the target-debugging guide of the CE 2.0 toolchain |
| `MPLATSDK.20/` | 1 | `readme.htm` | the disc's own ReadMe (installation, components, known issues) |

293 pages. The medium is **not** kept: the entry in `queues/media.tsv` uses the
action `import-scratch`, so `.github/workflows/import-media.yml` downloads the
41 MB image to a scratch directory, imports the documentation and discards the
image again (the SDK around it is 1,383 files of headers, libraries, samples and
installer — not corpus material). `PROVENANCE.md` in this directory records the
item, file name, size and md5 the pages came from.

## What was imported, and what was not

The disc is an InstallShield installer: `tools/import-media.py` reads the ISO
with `tools/iso9660.py`, unpacks `data1.cab`/`_sys1.cab`/`_user1.cab` with
`unshield` (7z cannot read InstallShield cabinets), and imports only the
documentation it finds. Of the 1,383 files on the disc:

* **imported** — the two WinHelp books above (decoded to HTML with helpdeco,
  the same route as `corpus/mvb/windows-ce-1.0/`, images dropped);
* **excluded by the queue's regex** — `infoview.hlp`, 1,236 topics of help for
  the InfoViewer/Visual C++ *viewer UI* itself (dialog boxes, wizard fields,
  editor options). It is Microsoft help, but not Windows CE material, and the
  CE 1.0 tree excludes the equivalent `MSDNLIB.HLP` for the same reason;
* **skipped and counted** — 178 `.h`, 82 `.lib`, 70 `.dll`, 62 `.c`, 23 `.cpp`,
  21 `.rc`, 16 `.def`, 7 `.mak`, 5 `.dsp` and the rest of the SDK: headers,
  libraries, binaries and sample sources are not imported into this corpus
  (see "What is collected" in the top-level `README.md`).

## Not extracted

`data1/Online_help_files/` holds the disc's **Books Online in InfoViewer
format** — `Mips.ivi` + `Mips.ivt` and nine more book/index pairs. No tool here
decodes `.ivt`, so those books are still unread; the Win32 API reference of
CE 2.0 itself is covered by the MSDN Library sets already in the corpus
(`corpus/msdn-library/techshelps/` CEGUIDE/WCEDDK, `corpus/msdn-library/datadungeon-2000-04/`).

## How these pages were produced

```bash
# on a runner (archive.org is not reachable from the maintenance environment):
python3 tools/import-media.py --config queues/media.tsv --only windows-ce-2.0-sdk
```

The run's own output is committed as `data/reports/media-last.txt`; the workflow
that carries it is `.github/workflows/import-media.yml`.
