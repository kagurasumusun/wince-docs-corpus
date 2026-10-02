# corpus/msdn-library/2010-05/

The Internet Archive capture of the MSDN Library topics for this corpus,
taken from the snapshot dated 2010-05-01:

```
https://web.archive.org/web/20100501000000/https://msdn.microsoft.com/en-us/library/<id>.aspx
```

253 topics, filed under **the same set directories as the Microsoft Learn
pages they duplicate** (`dotnet-compact-framework/`, `windows-ce-5.0/`);
topics that are not in the corpus are filed under `unclassified/`.

They are kept next to the Learn copies because they are a *different capture*
of the same documentation: the 2010 MSDN rendering (Web page, with the MSDN
Library-era navigation and `<title>`) rather than the archived Microsoft Learn
rendering. That makes them useful for diffing what changed between the two
publications, and as a fallback if a Learn page ever disappears.

* Queue: `queues/wayback-msdn-2010.txt` (31,388 URLs — the capture covers the
  whole CE namespace, but only the topics that were also harvested from Learn
  are kept here to avoid a second complete copy).
* Harvester: `tools/harvest.py` (kind `wayback`, 1.5 s delay to archive.org).
* File names are the original MSDN topic ids (`01c3x0ze.html`), i.e. the
  same page id the Learn copy uses.
