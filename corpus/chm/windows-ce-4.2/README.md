# corpus/chm/windows-ce-4.2/

The documentation of the **Windows CE .NET 4.2 Platform Builder Emulation
Edition** media (`sources/windows-ce-4.2/`, see its `PROVENANCE.md`):
15 pages from `EMULATOR.CHM` and
551 from `REMTOOLS.CHM`, extracted with
`tools/extract-chm.py` (entry `windows-ce-4.2` of `queues/chm-sets.tsv`,
workflow `.github/workflows/extract-chm.yml`).

```
corpus/chm/windows-ce-4.2/emulator/    the x86 emulator board/device reference
corpus/chm/windows-ce-4.2/remtools/    the remote tools (Remote Call Profiler,
                                       Remote Zoomin, Remote File Viewer, ...)
```

The 4.2 *API reference* is not on this media — it is in the Learn harvest
(`corpus/learn/windows-ce-net-4x/`); what the CHMs add is the emulator board
documentation and the remote-tools reference, which no other tree has.
Windows-1252 markup re-encoded to UTF-8; `Topic Not Found` placeholders and
images are not kept.
