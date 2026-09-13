# Windows CE 3.0 Technical Documentation — provenance

## Source (official)

* Product page (Microsoft Download Center):
  `https://www.microsoft.com/en-us/download/details.aspx?id=41197`
* Direct archive URL:
  `https://download.microsoft.com/download/1/3/d/13d0b628-4758-4b87-a9f2-6e98c940e6a9/WindowsCE3.0_DocumentationArchive.zip`
* Archive file: `WindowsCE3.0_DocumentationArchive.zip` (12,4xx KB; published 2024-07-15
  on the Download Center page; the CHM inside is dated Dec 3 2013 and is the retired
  MSDN "Windows CE 3.0" library, `© 2004 Microsoft Corporation`).
* Collected: 2026-09-14 (JST).

## Contents

* `WindowsCE3.0_DocumentationArchive.zip` — the untouched official archive.
* `Important_ReadMe.txt` — the unblocking note shipped inside the zip.

The archive contains a single CHM (`WindowsCE3.0_DocumentationArchive.chm`,
13,370,824 bytes). It was extracted with p7zip (`7z x`) to obtain 8,962 HTML
reference/guide pages, which are preserved individually under `../pages3/`
(raw official HTML). Per-page harvest records (title, signature, "Runs on",
"Versions", "Defined in", "Link to") are in `../rows3.json`; the full page
catalog is `../catalogs/catalog-windows-ce-30.tsv`.

## Why this is load-bearing

CE 1.x/2.x API documentation is **not** published on Learn. This archive is the
only complete official reference for the CE 1/2/3 API surface: every API
reference page carries a `Versions: <N> and later` Requirements row, so the
CE 1.0 / 2.0 / 2.1 / 2.10 / 2.11 / 2.12 / 3.0 surfaces are derivable directly
from official statements (no desktop-Win32 analogy).

Extraction/parsing is done by `tools/ce3-collect.py` in the wince-api repo.
