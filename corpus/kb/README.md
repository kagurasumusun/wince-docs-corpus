# corpus/kb/

The **Windows CE articles of the Microsoft KnowledgeBase Archive**
(<https://github.com/jeffpar/kbarchive>, `master`, last commit 2023-04-12).
That archive holds the Knowledge Base as it stood around 2002 (Microsoft's FTP
archive, courtesy of Michal Necasek) together with articles from the Microsoft
Programmer's Library CD-ROMs; it is plain text, one file per article, and it
has no product category for Windows CE — the CE articles are spread over the
`visualc`, `vbwin`, `exchange`, `winmisc` and similar ranges.

257 articles were selected: every article whose header block (`DOCUMENT`,
`TITLE`, `PRODUCT`, `PROD/VER` and the "applies to" list) mentions a Windows CE
family product — Windows CE, Handheld PC, H/PC, Palm-size PC, Pocket PC,
Windows CE Services, the CE toolkits or Windows Embedded. They document the
CE 1.0/2.0/2.1x era and the CE toolkits: known problems of VBCE/eVB, the CE
emulator and CE Services connectivity, Palm-size PC and H/PC behaviour, and
platform issues that the product documentation does not mention.

```
corpus/kb/<number range>/<qid>.html     e.g. corpus/kb/174/q174752.html
```

Each page is the original article text verbatim (CP-1252 re-encoded to UTF-8,
line endings normalised) inside a `<pre class="kb">` block, with the article
title as the page title; the file name is the original `Q<id>.TXT` name in
lower case. This is a *support/KB* tree, not product documentation, which is
why it is not filed under a release directory.

Re-import (partial clone: only the `txt/` tree is fetched):

```bash
python3 tools/import-kbarchive.py --clone --cache-dir .cache
python3 tools/import-kbarchive.py --src <clone> --list    # what would be imported
```
