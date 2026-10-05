# Provenance — corpus/oss/

Captured 2026-10-05. The sandbox had no direct HTTPS route to these hosts;
each document was retrieved as a text rendering and wrapped as HTML. The
original HTML bytes were not stored. URLs, and what was refused, are in
`corpus/oss/README.md` and `queues/oss-docs.tsv`.

Licence texts read for this collection, and the wording the registry quotes,
are in `sources/oss-licenses/`. A summary was not substituted for that wording.

Looked at and not collected, so the corpus would not gain an extra or a
source file:

* SDL 1.2 `README.WinCE` — useful (GAPI, semaphores, DirectX), but it is a
  file of the LGPL 2.1 source distribution, and the source tree is out of
  scope.
* Qt SIP Dialog example — a sample.
* Qt fine-tuning, performance and shadow-build pages — general Qt documents
  linked from the CE index.
* Qt OpenGL ES and OpenVG pages — titled for Windows CE, but the bodies are
  Qt's graphics-plugin reference. Not taken whole, and not excerpted.
* CMake `cmake-toolchains(7)` — the Windows CE section sits in a manual that
  also documents Linux, Windows Store and Renesas. Not excerpted. The
  one-sentence `WINCE` variable page was left out with it: the copyright file
  for the tag that was tried was not retrieved, and a page is not stored
  without the licence text that attaches to it.
* curl mailing-list posts — not an official document, and they contain source
  patches.
* SQLite's current compile documents — they do not state Windows CE.
* FreeType's download page and the GETINFO rasterizer table — not a Windows
  CE document.
* ICU user guide — no Windows CE document.
* wxWidgets `page_port.html` and the 2.8 preprocessor-symbol page — mixed
  platform documents, not excerpted.
* cegcc / mingw32ce headers — source, and the opposite of a clean room.
* Qt 4.8 `qfunctions_wince.h` / `.cpp` and SDL 1.2 `src/video/gapi/` — read on 2026-10-05 to see which Windows CE names an implementation actually uses. Not stored. The licence notices are in `sources/oss-licenses/`. The names, and what was refused, are in `knowledge/reports/oss-surface.tsv`. Qt's stand-in numbers are marked in that file as not the real values, and they were not copied. SDL's `README.WinCE` remains unstored: it is a file of the LGPL source distribution, and its "not available" list is about the SDL port, not a Windows CE API absence.
