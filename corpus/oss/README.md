# corpus/oss/ — open-source documentation that states Windows CE facts

Eleven pages. Not Microsoft's documentation, and not a source tree.

Each page is a text rendering, captured 2026-10-05, of one official document
that is itself about Windows CE or a CE derivative (Windows Mobile, Windows
Embedded Compact). Site navigation was left out. The article, from the first
heading, is the document text as retrieved. The note before that heading is
this project's, so the capture and the licence conditions are visible and are
not part of the quotation the knowledge base keeps.

| Project | Pages | What was taken | What was not |
|---------|------:|----------------|--------------|
| Qt 4.8 / 5.6 | 8 | The Windows CE platform documents at `doc.qt.io` archives: requirements, install, introduction, custom SDKs, signing, hardware acceleration, and the 4.8 index. Qt 5.6 is here only for the requirements page, which names Windows Embedded Compact 6 and 7. | The rest of the Qt documentation. The SIP Dialog example. OpenGL ES and OpenVG pages whose bodies are Qt's graphics plugin, not a Windows CE document. `qplatformdefs.h` and every other header. |
| SDL | 1 | The SDL wiki page that is only about Windows CE (`SDL2/README-wince`), under CC BY 4.0. | `README.WinCE` in the SDL 1.2 source tree. Its `COPYING` is the GNU LGPL 2.1, which permits verbatim copies of the complete source. Collecting that tree is forbidden here, and the file carries no separate licence that would let us keep it alone. |
| OpenSSL 1.0.2u | 1 | `INSTALL.WCE`, a documentation file. | The library source, including `e_os2.h`. |
| wxWidgets 3.0.5 | 1 | `docs/msw/wince/readme.txt`. | `include/wx/msw/wince/setup.h` and the library source. The mixed platform pages (`page_port.html`, the preprocessor-symbol list) were not excerpted. |

The knowledge base records each page as `layer: oss` and quotes the article.
It does not mint an API entity from the title, and it does not read a code
sample on the page as a declaration or a constant. `tools/gen-include-def.py`
does not emit this layer.

The allowlist is `queues/oss-docs.tsv`. A page that is not on it fails
`tools/check-policy.py`.
