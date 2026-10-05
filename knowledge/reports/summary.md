# Knowledge base coverage

Generated 2026-10-05 by `python3 tools/build-kb.py`.

The knowledge base is built from the pages in `corpus/` only: every declaration, requirement and constraint record quotes the page it came from. This report says how much of the corpus is *structured* so far, and what is missing -- it is the collection worklist, not a quality judgement of a document.

## ABI

* syntax declarations: **93,510**; of those **89,899** print no calling convention (none is guessed) and **3,611** print one (winapi 2,924, stdcall 416, cdecl 264, extern-c 6, fastcall 1)
* member lines that print a type: **38,909** out of **46,854**; bitfields **126**, `#pragma pack` **4**, `__declspec(align` **5**
* statements a page makes about alignment, byte order, pointer width or a structure size: **969** quoted sentences (`kind: "abi-note"` in `kb/constraints.jsonl`; the structure-size sentences are counted again on their own line below)
* layout tables (`Offset | Field | Size | …`): **399** documented offset rows over **58** page(s), quoted row by row in `kb/abi-offsets.jsonl` (the flat view is `kb/abi-offsets.tsv`, with the page and its title). **18** of the rows name a member the same page declares in a syntax block; the others are rows whose field the page does not declare (wire/packet layouts, array spellings such as `dwIndex[0]` where the declaration says `dwOffset`, and string literals inside the table) -- each is kept as the page printed it, and the column is marked `matches_declared_member`
* structure sizes stated in prose: **5** sentences (the number is a read of the quoted sentence, never a guess)
* numbered constants (`Name | Value`, `Return code | Hexadecimal | Decimal`, `Symbolic constant | Value (Hex)`, `Control code | Value`, `Message identifier | Value`, `Element | Hex code`, `Value | Weight` for the font-weight constants, a cell printed `NAME = 0x0001` or `NAME (0x0001)`, and the same shapes): **18,746** rows over **791** page(s), quoted in `kb/constants.jsonl` (the flat view is `kb/constants.tsv`).  A row is kept only when the name is one identifier and the value is one number; a one-letter `A=0` cell is left out, and a hexadecimal is never converted.  A decimal is kept only when the page prints one.  A constant the page does not number has no row
* where a page states **no** offset, none is recorded: for the structures whose members a page documents without printing a body, `kb/struct-fields.tsv` keeps the names and documented order only, and `reports/abi.tsv` says how many offsets a name has (0 for most)

## Totals

* pages parsed: **121,050**
* API entities: **26,686** -- CE-specific **21,175**, documented by Windows CE and the Win32 reference alike **4,353**, Win32 pages for a CE name's A/W spelling **1,155**, named by the CE catalog only **3**, unclaimed Win32 pages **0** (`reports/surface.tsv`; 585 names have a Win32 page through a variant spelling)
* declarations extracted: **109,912** (C/C++ 78,586 in `kb/declarations.jsonl`, managed-code signatures 31,326 in `kb/declarations-dotnet.jsonl` -- the separated .NET layer)
* requirement statements: **168,092**
* numbered constants: **18,746** (`kb/constants.jsonl`, 791 page(s))
* Windows CE constraint sentences: **3,250** and ABI statements quoted from the pages (**969**, `kind: "abi-note"`)
* entities with a gap record: **16,491** (`reports/gaps.tsv`)
* structures whose members a page documents without printing a declaration body: **801** (842 page(s) carry a member list, 840 of them print no declaration at all; `kb/struct-fields.tsv` has the member names and order, one row per field -- the pages state no offsets, so none are recorded)
* relations between definitions: **25,825** (`unicode-ansi`/`unicode-ansi-base`/`unicode-ansi-variant` from the page's own statement, `interface-method`, `layer`, `ce-name-lead` for the spelling a CE page prints)
* catalog-only names (the CE TOC names it, no CE page for it is in the corpus): **3** (`reports/catalog-leads.tsv` shows the CE page the name list points at, what that page actually prints, and what the Win32 page documents -- a lead, not a CE definition)
* requirement values that name no file (a library statement like `Developer Implemented`) stay in `kb/requirements.jsonl` with an empty derived key and are listed in `reports/filtered-values.tsv`

## What each tree contributed

| tree | pages | with entity | with requirements | with declaration | requirements | declarations |
|------|-------|-------------|-------------------|------------------|--------------|--------------|
| `learn/windows-ce-5.0` | 24,694 | 14,596 | 14,719 | 15,063 | 36,218 | 17,281 |
| `learn/windows-embedded-ce-6.0` | 23,714 | 16,483 | 16,701 | 16,739 | 40,726 | 18,887 |
| `chm/windows-ce-5.0` | 20,179 | 11,457 | 9,698 | 14,790 | 23,411 | 16,059 |
| `learn/windows-ce-net-4x` | 8,969 | 6,535 | 6,512 | 6,327 | 16,626 | 7,164 |
| `chm/windows-ce-3.0` | 8,962 | 6,949 | 5,030 | 6,802 | 11,592 | 7,558 |
| `msdn-library/wcedevcon-99` | 6,382 | 4,532 | 3,205 | 4,512 | 6,821 | 4,916 |
| `dotnet/pos-for-net` | 5,793 | 0 | 0 | 5,067 | 0 | 23,157 |
| `msdn-library/techshelps` | 5,165 | 3,802 | 3,229 | 3,261 | 8,994 | 3,350 |
| `dotnet/dotnet-micro-framework` | 4,012 | 0 | 0 | 1,835 | 0 | 6,535 |
| `msdn-library/datadungeon-2000-04` | 2,931 | 1,328 | 0 | 677 | 0 | 758 |
| `mvb/windows-ce-1.0/PEGSDK` | 1,918 | 1,470 | 0 | 268 | 0 | 429 |
| `dotnet/dotnet-compact-framework` | 852 | 0 | 0 | 636 | 0 | 2,135 |
| `chm/windows-ce-4.2` | 566 | 278 | 257 | 254 | 502 | 278 |
| `learn/unclassified` | 413 | 325 | 304 | 280 | 657 | 293 |
| `win32/api/winuser` | 378 | 378 | 378 | 20 | 2,046 | 26 |
| `win32/api/commctrl` | 336 | 336 | 336 | 215 | 970 | 217 |
| `mvb/windows-ce-2.0-sdk/WINDBG` | 291 | 29 | 0 | 13 | 0 | 18 |
| `win32/api/strmif` | 271 | 271 | 271 | 2 | 1,059 | 2 |
| `learn/windows-embedded-compact-7` | 256 | 0 | 0 | 165 | 0 | 495 |
| `win32/api/oleauto` | 226 | 226 | 226 | 9 | 904 | 10 |
| `win32/api/objidl` | 222 | 222 | 222 | 1 | 601 | 1 |
| `win32/api/winldap` | 212 | 212 | 212 | 14 | 1,023 | 17 |
| `win32/api/wincrypt` | 204 | 204 | 204 | 31 | 843 | 33 |
| `win32/api/tapi` | 193 | 193 | 193 | 0 | 887 | 0 |
| `win32/api/wingdi` | 185 | 185 | 185 | 21 | 1,005 | 26 |
| `mvb/windows-ce-1.0/PEGDDK` | 181 | 42 | 0 | 20 | 0 | 29 |
| `win32/api/wininet` | 169 | 169 | 169 | 0 | 835 | 0 |
| `msdn-library/2010-05` | 161 | 101 | 101 | 157 | 263 | 329 |
| `win32/api/oaidl` | 156 | 156 | 156 | 9 | 347 | 10 |
| `win32/api/control` | 102 | 102 | 102 | 3 | 408 | 3 |
| `win32/api/winsock2` | 94 | 94 | 94 | 28 | 455 | 39 |
| `win32/api/oleidl` | 93 | 93 | 93 | 0 | 194 | 0 |
| `win32/api/wmp` | 93 | 93 | 93 | 0 | 276 | 0 |
| `win32/api/mmeapi` | 84 | 84 | 84 | 0 | 448 | 0 |
| `win32/api/tspi` | 82 | 82 | 82 | 0 | 164 | 0 |
| `win32/api/imm` | 70 | 70 | 70 | 3 | 484 | 3 |
| `win32/api/immdev` | 70 | 70 | 70 | 3 | 484 | 3 |
| `win32/api/winbase` | 65 | 65 | 65 | 3 | 343 | 4 |
| `win32/api/combaseapi` | 63 | 63 | 63 | 1 | 306 | 1 |
| `win32/api/ocidl` | 62 | 62 | 62 | 0 | 151 | 0 |
| `win32/api/strsafe` | 60 | 60 | 60 | 4 | 180 | 4 |
| `win32/api/wsdtypes` | 58 | 58 | 58 | 0 | 229 | 0 |
| `win32/api/winddi` | 53 | 53 | 53 | 1 | 207 | 1 |
| `win32/api/iphlpapi` | 48 | 48 | 48 | 17 | 192 | 17 |
| `win32/api/fileapi` | 47 | 47 | 47 | 0 | 265 | 0 |
| `win32/api/mediaobj` | 46 | 46 | 46 | 1 | 182 | 1 |
| `win32/api/winscard` | 46 | 46 | 46 | 26 | 219 | 26 |
| `win32/api/winnls` | 45 | 45 | 45 | 4 | 250 | 4 |
| `win32/api/sspi` | 44 | 44 | 44 | 0 | 246 | 0 |
| `win32/api/usp10` | 43 | 43 | 43 | 2 | 160 | 4 |
| `win32/api/wsdbase` | 43 | 43 | 43 | 0 | 174 | 0 |
| `win32/api/objidlbase` | 41 | 41 | 41 | 0 | 126 | 0 |
| `win32/api/wsddisco` | 41 | 41 | 41 | 0 | 165 | 0 |
| `win32/api/amvideo` | 38 | 38 | 38 | 11 | 142 | 13 |
| `win32/api/wsdclient` | 38 | 38 | 38 | 0 | 154 | 0 |
| `win32/api/windnsdef` | 36 | 36 | 36 | 0 | 149 | 0 |
| `win32/api/winsock` | 36 | 36 | 36 | 14 | 194 | 20 |
| `win32/api/snmp` | 35 | 35 | 35 | 0 | 123 | 0 |
| `msdn-library/windows-mobile-6.5` | 34 | 27 | 27 | 27 | 102 | 36 |
| `win32/api/ras` | 34 | 34 | 34 | 11 | 168 | 11 |
| `win32/api/ddraw` | 33 | 33 | 33 | 4 | 128 | 4 |
| `win32/api/processthreadsapi` | 32 | 32 | 32 | 2 | 265 | 2 |
| `win32/api/shobjidl_core` | 32 | 32 | 32 | 4 | 127 | 8 |
| `win32/api/upnp` | 31 | 31 | 31 | 0 | 93 | 0 |
| `win32/api/winnetwk` | 30 | 30 | 30 | 4 | 148 | 4 |
| `win32/api/commdlg` | 28 | 28 | 28 | 0 | 125 | 0 |
| `win32/api/objbase` | 28 | 28 | 28 | 1 | 115 | 1 |
| `kb/180` | 26 | 0 | 0 | 23 | 0 | 23 |
| `win32/api/winreg` | 25 | 25 | 25 | 0 | 147 | 0 |
| `win32/api/prsht` | 24 | 24 | 24 | 18 | 64 | 18 |
| `win32/api/tlhelp32` | 23 | 23 | 23 | 0 | 97 | 0 |
| `win32/api/winnt` | 23 | 23 | 23 | 7 | 102 | 7 |
| `kb/215` | 21 | 0 | 0 | 13 | 0 | 13 |
| `win32/api/qnetwork` | 21 | 21 | 21 | 0 | 43 | 0 |
| `win32/api/ws2spi` | 21 | 21 | 21 | 4 | 59 | 5 |
| `win32/api/mmstream` | 20 | 20 | 20 | 1 | 40 | 1 |
| `win32/api/shellapi` | 20 | 20 | 20 | 5 | 88 | 13 |
| `win32/api/synchapi` | 19 | 19 | 19 | 0 | 154 | 0 |
| `win32/api/minwinbase` | 17 | 17 | 17 | 3 | 94 | 3 |
| `win32/api/p2p` | 17 | 17 | 17 | 0 | 68 | 0 |
| `win32/api/upnphost` | 17 | 17 | 17 | 0 | 51 | 0 |
| `win32/api/wsdhost` | 17 | 17 | 17 | 0 | 70 | 0 |
| `win32/api/libloaderapi` | 16 | 16 | 16 | 0 | 88 | 0 |
| `win32/api/shlobj_core` | 16 | 16 | 16 | 2 | 97 | 4 |
| `win32/api/vpconfig` | 15 | 15 | 15 | 0 | 32 | 0 |
| `win32/api/comcat` | 14 | 14 | 14 | 0 | 28 | 0 |
| `win32/api/memoryapi` | 14 | 14 | 14 | 0 | 83 | 0 |
| `win32/api/mpconfig` | 14 | 14 | 14 | 0 | 42 | 0 |
| `win32/api/nspapi` | 14 | 14 | 14 | 0 | 86 | 0 |
| `win32/api/msime` | 13 | 13 | 13 | 0 | 30 | 0 |
| `win32/api/winber` | 13 | 13 | 13 | 0 | 52 | 0 |
| `win32/api/wsdutil` | 13 | 13 | 13 | 0 | 65 | 0 |
| `win32/api/raseapif` | 12 | 12 | 12 | 0 | 36 | 0 |
| `win32/api/ole2` | 11 | 11 | 11 | 0 | 48 | 0 |
| `win32/api/winineti` | 11 | 11 | 11 | 0 | 85 | 0 |
| `kb/192` | 10 | 0 | 0 | 5 | 0 | 5 |
| `site/windows-ce-2.0/prodinfo` | 10 | 0 | 0 | 0 | 0 | 0 |
| `win32/api/sysinfoapi` | 10 | 10 | 10 | 0 | 52 | 0 |
| `win32/api/debugapi` | 9 | 9 | 9 | 0 | 47 | 0 |
| `win32/api/heapapi` | 9 | 9 | 9 | 2 | 45 | 2 |
| `win32/api/uxtheme` | 9 | 9 | 9 | 0 | 36 | 0 |
| `win32/api/wincred` | 9 | 9 | 9 | 0 | 44 | 0 |
| `win32/api/wsdxmldom` | 9 | 9 | 9 | 0 | 27 | 0 |
| `oss/qt` | 8 | 0 | 0 | 0 | 0 | 0 |
| `site/windows-ce-2.0/technical` | 8 | 0 | 0 | 0 | 0 | 0 |
| `win32/api/coml2api` | 8 | 8 | 8 | 0 | 40 | 0 |
| `win32/api/dmoreg` | 8 | 8 | 8 | 1 | 33 | 1 |
| `win32/api/gdiplusimaging` | 8 | 8 | 8 | 1 | 29 | 1 |
| `win32/api/icmpapi` | 8 | 8 | 8 | 5 | 47 | 6 |
| `win32/api/unknwn` | 8 | 8 | 8 | 1 | 18 | 1 |
| `win32/api/windns` | 8 | 8 | 8 | 0 | 35 | 0 |
| `win32/api/ws2def` | 8 | 8 | 8 | 0 | 42 | 0 |
| `win32/api/wsdxml` | 8 | 8 | 8 | 0 | 32 | 0 |
| `kb/209` | 7 | 0 | 0 | 5 | 0 | 5 |
| `kb/265` | 7 | 0 | 0 | 4 | 0 | 4 |
| `win32/api/iaccess` | 7 | 7 | 7 | 0 | 14 | 0 |
| `win32/api/ipmib` | 7 | 7 | 7 | 0 | 34 | 0 |
| `win32/api/winioctl` | 7 | 7 | 7 | 5 | 25 | 5 |
| `win32/api/wsdattachment` | 7 | 7 | 7 | 0 | 29 | 0 |
| `kb/238` | 6 | 0 | 0 | 2 | 0 | 2 |
| `kb/271` | 6 | 0 | 0 | 4 | 0 | 4 |
| `kb/301` | 6 | 0 | 0 | 1 | 0 | 1 |
| `win32/api/cchannel` | 6 | 6 | 6 | 0 | 14 | 0 |
| `win32/api/dmort` | 6 | 6 | 6 | 0 | 30 | 0 |
| `win32/api/stringapiset` | 6 | 6 | 6 | 2 | 33 | 2 |
| `win32/api/timeapi` | 6 | 6 | 6 | 0 | 32 | 0 |
| `win32/api/winver` | 6 | 6 | 6 | 2 | 36 | 2 |
| `win32/api/ws2tcpip` | 6 | 6 | 6 | 3 | 23 | 4 |
| `kb/189` | 5 | 0 | 0 | 0 | 0 | 0 |
| `kb/190` | 5 | 0 | 0 | 4 | 0 | 4 |
| `kb/208` | 5 | 0 | 0 | 4 | 0 | 4 |
| `kb/241` | 5 | 0 | 0 | 2 | 0 | 2 |
| `kb/247` | 5 | 0 | 0 | 2 | 0 | 2 |
| `kb/254` | 5 | 0 | 0 | 4 | 0 | 4 |
| `win32/api/dmoimpl` | 5 | 5 | 5 | 0 | 20 | 0 |
| `win32/api/errhandlingapi` | 5 | 5 | 5 | 0 | 25 | 0 |
| `win32/api/ipexport` | 5 | 5 | 5 | 1 | 25 | 1 |
| `win32/api/shtypes` | 5 | 5 | 5 | 2 | 21 | 4 |
| `win32/api/timezoneapi` | 5 | 5 | 5 | 0 | 26 | 0 |
| `win32/api/windef` | 5 | 5 | 5 | 0 | 32 | 0 |
| `win32/api/winperf` | 5 | 5 | 5 | 0 | 25 | 0 |
| `win32/api/wtypesbase` | 5 | 5 | 5 | 0 | 26 | 0 |
| `kb/181` | 4 | 0 | 0 | 3 | 0 | 3 |
| `kb/183` | 4 | 0 | 0 | 4 | 0 | 4 |
| `kb/195` | 4 | 0 | 0 | 1 | 0 | 1 |
| `kb/234` | 4 | 0 | 0 | 3 | 0 | 3 |
| `kb/240` | 4 | 0 | 0 | 1 | 0 | 1 |
| `kb/250` | 4 | 0 | 0 | 3 | 0 | 3 |
| `mvb/windows-ce-1.0/RELNOTES` | 4 | 0 | 0 | 0 | 0 | 0 |
| `win32/api/datetimeapi` | 4 | 4 | 4 | 0 | 20 | 0 |
| `win32/api/dsgetdc` | 4 | 4 | 4 | 0 | 20 | 0 |
| `win32/api/dvp` | 4 | 4 | 4 | 0 | 20 | 0 |
| `win32/api/ole` | 4 | 4 | 4 | 0 | 20 | 0 |
| `win32/api/olectl` | 4 | 4 | 4 | 0 | 16 | 0 |
| `win32/api/pnrpdef` | 4 | 4 | 4 | 0 | 13 | 0 |
| `win32/api/propidl` | 4 | 4 | 4 | 1 | 17 | 1 |
| `win32/api/wmsdkidl` | 4 | 4 | 4 | 0 | 16 | 0 |
| `win32/api/wsipv6ok` | 4 | 4 | 4 | 3 | 24 | 3 |
| `kb/177` | 3 | 0 | 0 | 1 | 0 | 1 |
| `kb/185` | 3 | 0 | 0 | 2 | 0 | 2 |
| `kb/187` | 3 | 0 | 0 | 0 | 0 | 0 |
| `kb/191` | 3 | 0 | 0 | 3 | 0 | 3 |
| `kb/193` | 3 | 0 | 0 | 0 | 0 | 0 |
| `kb/194` | 3 | 0 | 0 | 2 | 0 | 2 |
| `kb/196` | 3 | 0 | 0 | 1 | 0 | 1 |
| `kb/232` | 3 | 0 | 0 | 2 | 0 | 2 |
| `kb/253` | 3 | 0 | 0 | 3 | 0 | 3 |
| `kb/266` | 3 | 0 | 0 | 0 | 0 | 0 |
| `kb/275` | 3 | 0 | 0 | 3 | 0 | 3 |
| `kb/319` | 3 | 0 | 0 | 1 | 0 | 1 |
| `win32/api/bthsdpdef` | 3 | 3 | 3 | 0 | 9 | 0 |
| `win32/api/cpl` | 3 | 3 | 3 | 0 | 12 | 0 |
| `win32/api/docobj` | 3 | 3 | 3 | 0 | 6 | 0 |
| `win32/api/dsrole` | 3 | 3 | 3 | 0 | 12 | 0 |
| `win32/api/gdiplustypes` | 3 | 3 | 3 | 0 | 6 | 0 |
| `win32/api/iptypes` | 3 | 3 | 3 | 0 | 17 | 0 |
| `win32/api/schannel` | 3 | 3 | 3 | 0 | 14 | 0 |
| `win32/api/secext` | 3 | 3 | 3 | 0 | 17 | 0 |
| `win32/api/udpmib` | 3 | 3 | 3 | 0 | 15 | 0 |
| `win32/api/vpnotify` | 3 | 3 | 3 | 0 | 8 | 0 |
| `win32/api/vptype` | 3 | 3 | 3 | 0 | 11 | 0 |
| `kb/186` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/207` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/218` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/220` | 2 | 0 | 0 | 0 | 0 | 0 |
| `kb/221` | 2 | 0 | 0 | 0 | 0 | 0 |
| `kb/222` | 2 | 0 | 0 | 2 | 0 | 2 |
| `kb/235` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/242` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/243` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/245` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/260` | 2 | 0 | 0 | 2 | 0 | 2 |
| `kb/262` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/263` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/269` | 2 | 0 | 0 | 1 | 0 | 1 |
| `kb/296` | 2 | 0 | 0 | 0 | 0 | 0 |
| `kb/306` | 2 | 0 | 0 | 0 | 0 | 0 |
| `site/windows-ce-4.2` | 2 | 0 | 1 | 1 | 2 | 2 |
| `site/windows-ce-5.0` | 2 | 0 | 1 | 1 | 1 | 5 |
| `win32/api/commoncontrols` | 2 | 2 | 2 | 0 | 8 | 0 |
| `win32/api/ddrawi` | 2 | 2 | 2 | 0 | 10 | 0 |
| `win32/api/dimm` | 2 | 2 | 2 | 2 | 12 | 4 |
| `win32/api/dpa_dsa` | 2 | 2 | 2 | 1 | 6 | 1 |
| `win32/api/dpapi` | 2 | 2 | 2 | 2 | 8 | 2 |
| `win32/api/dvdmedia` | 2 | 2 | 2 | 1 | 6 | 4 |
| `win32/api/errors` | 2 | 2 | 2 | 0 | 6 | 0 |
| `win32/api/gdiplusenums` | 2 | 2 | 2 | 0 | 6 | 0 |
| `win32/api/handleapi` | 2 | 2 | 2 | 2 | 10 | 2 |
| `win32/api/ifmib` | 2 | 2 | 2 | 0 | 10 | 0 |
| `win32/api/iprtrmib` | 2 | 2 | 2 | 0 | 10 | 0 |
| `win32/api/ntdef` | 2 | 2 | 2 | 0 | 7 | 0 |
| `win32/api/processenv` | 2 | 2 | 2 | 0 | 18 | 0 |
| `win32/api/profileapi` | 2 | 2 | 2 | 1 | 10 | 1 |
| `win32/api/psapi` | 2 | 2 | 2 | 0 | 16 | 0 |
| `win32/api/shlwapi` | 2 | 2 | 2 | 0 | 10 | 0 |
| `win32/api/unknwnbase` | 2 | 2 | 2 | 0 | 6 | 0 |
| `win32/api/urlmon` | 2 | 2 | 2 | 0 | 8 | 0 |
| `win32/api/winhttp` | 2 | 2 | 2 | 0 | 8 | 0 |
| `win32/api/wtypes` | 2 | 2 | 2 | 0 | 6 | 0 |
| `kb/165` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/169` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/172` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/173` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/174` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/176` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/184` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/199` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/202` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/206` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/212` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/214` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/216` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/217` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/219` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/224` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/229` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/230` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/231` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/236` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/239` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/246` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/248` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/249` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/252` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/255` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/259` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/264` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/268` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/270` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/272` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/273` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/285` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/286` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/291` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/297` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/299` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/303` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/304` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/312` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/314` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/315` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/316` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/317` | 1 | 0 | 0 | 1 | 0 | 1 |
| `kb/322` | 1 | 0 | 0 | 0 | 0 | 0 |
| `kb/323` | 1 | 0 | 0 | 0 | 0 | 0 |
| `mvb/windows-ce-2.0-sdk/MPLATSDK.20` | 1 | 1 | 0 | 0 | 0 | 0 |
| `oss/openssl` | 1 | 0 | 0 | 0 | 0 | 0 |
| `oss/sdl` | 1 | 0 | 0 | 0 | 0 | 0 |
| `oss/wxwidgets` | 1 | 0 | 0 | 0 | 0 | 0 |
| `site/windows-ce-2.0` | 1 | 0 | 0 | 0 | 0 | 0 |
| `site/windows-ce-2.0/embedded` | 1 | 0 | 0 | 0 | 0 | 0 |
| `site/windows-ce-6.0` | 1 | 0 | 1 | 1 | 1 | 19 |
| `win32/api/af_irda` | 1 | 1 | 1 | 0 | 5 | 0 |
| `win32/api/audiomediatype` | 1 | 1 | 1 | 0 | 3 | 0 |
| `win32/api/aviriff` | 1 | 1 | 1 | 0 | 3 | 0 |
| `win32/api/dmodshow` | 1 | 1 | 1 | 0 | 3 | 0 |
| `win32/api/errorrep` | 1 | 1 | 1 | 0 | 4 | 0 |
| `win32/api/gdiplusheaders` | 1 | 1 | 1 | 0 | 2 | 0 |
| `win32/api/gdipluspixelformats` | 1 | 1 | 1 | 0 | 3 | 0 |
| `win32/api/gdiplusstringformat` | 1 | 1 | 1 | 0 | 2 | 0 |
| `win32/api/guiddef` | 1 | 1 | 1 | 1 | 6 | 1 |
| `win32/api/icm` | 1 | 1 | 1 | 0 | 3 | 0 |
| `win32/api/ifdef` | 1 | 1 | 1 | 0 | 3 | 0 |
| `win32/api/in6addr` | 1 | 1 | 1 | 0 | 6 | 0 |
| `win32/api/inaddr` | 1 | 1 | 1 | 0 | 6 | 0 |
| `win32/api/ioapiset` | 1 | 1 | 1 | 0 | 5 | 0 |
| `win32/api/lmapibuf` | 1 | 1 | 1 | 0 | 5 | 0 |
| `win32/api/mmreg` | 1 | 1 | 1 | 0 | 9 | 0 |
| `win32/api/mpeg2structs` | 1 | 1 | 1 | 1 | 4 | 1 |
| `win32/api/mstcpip` | 1 | 1 | 1 | 0 | 2 | 0 |
| `win32/api/mswsock` | 1 | 1 | 1 | 0 | 6 | 0 |
| `win32/api/pchannel` | 1 | 1 | 1 | 0 | 4 | 0 |
| `win32/api/pnrpns` | 1 | 1 | 1 | 0 | 4 | 0 |
| `win32/api/propidlbase` | 1 | 1 | 1 | 1 | 5 | 1 |
| `win32/api/richedit` | 1 | 1 | 1 | 0 | 4 | 0 |
| `win32/api/routprot` | 1 | 1 | 1 | 0 | 4 | 0 |
| `win32/api/shobjidl` | 1 | 1 | 1 | 0 | 4 | 0 |
| `win32/api/tcpmib` | 1 | 1 | 1 | 1 | 5 | 1 |
| `win32/api/tvout` | 1 | 1 | 1 | 0 | 6 | 0 |
| `win32/api/verrsrc` | 1 | 1 | 1 | 0 | 4 | 0 |
| `win32/api/winternl` | 1 | 1 | 1 | 0 | 3 | 0 |
| `win32/api/wintrust` | 1 | 1 | 1 | 0 | 4 | 0 |
| `win32/api/ws2bth` | 1 | 1 | 1 | 0 | 4 | 0 |

The full per-book breakdown (one row per component CHM, mirror folder, ...) is `reports/coverage-by-tree.tsv`.

## Reading the numbers

* *with requirements / with declaration* counts pages, not entities: a page of prose has neither, and that is expected.
* `corpus/site/` and `corpus/kb/` are mostly prose and release notes, so their reference coverage is low by nature.
* The `.NET` tree (`corpus/dotnet/`) is documentation of a layer on top of Windows CE; its `Namespace:`/`Assembly:` values are recorded in the same requirement records, with `layer: dotnet`, and are not part of the CE include/def surface.
* The open-source documents (`corpus/oss/`) are `layer: oss`.  Each page is quoted as an `oss-statement`.  No entity, declaration or constant is minted from them, and the include/def generator does not emit them.

## What a version's own pages state

A header or a `.def` for one Windows CE version can only be built from what *that version's pages* state.  The columns count entities documented by the set, and — of those — how many have a syntax declaration, a header file and a library stated by a page of that same set.  A fact stated only by another version is not counted here (a generator may borrow it, and must say so).  A calling convention, an export ordinal or a constant with no value cell is absent because the documents do not state it.

| set | entities | syntax | header | library | functions with all three | numbered constants |
|-----|----------|--------|--------|---------|--------------------------|--------------------|
| `learn/windows-ce-5.0` | 14,529 | 12,556 | 12,368 | 6,868 | 6,182 / 10,424 | 4,169 (3,054 names) |
| `learn/windows-embedded-ce-6.0` | 16,312 | 14,977 | 14,036 | 7,436 | 7,093 / 12,176 | 4,353 (3,231 names) |
| `learn/windows-ce-net-4x` | 6,503 | 5,606 | 5,995 | 3,595 | 3,359 / 4,525 | 1,031 (985 names) |
| `chm/windows-ce-5.0` | 11,364 | 10,504 | 7,928 | 4,967 | 4,492 / 9,228 | 3,380 (2,339 names) |
| `chm/windows-ce-3.0` | 6,746 | 6,155 | 4,415 | 1,804 | 1,732 / 5,324 | 2,480 (1,405 names) |
| `chm/windows-ce-4.2` | 277 | 235 | 242 | 0 | 0 / 227 | 0 (0 names) |
| `mvb/windows-ce-1.0/PEGSDK` | 1,467 | 189 | 0 | 0 | 0 / 1,128 | 72 (72 names) |
| `msdn-library/wcedevcon-99` | 4,466 | 4,138 | 3,125 | 0 | 0 / 3,612 | 2,268 (1,206 names) |
| `msdn-library/techshelps` | 3,747 | 3,063 | 3,076 | 0 | 0 / 2,957 | 321 (178 names) |

Numbered constants are rows of a name/value table the page prints, or a cell it prints as `NAME = 0x0001` / `NAME (0x0001)` (`kb/constants.jsonl`).  A heading such as `Value (Hex)`, `Control code`, `Message identifier`, `Hex code` or `Weight` is read when the cells are one identifier and one number.  Digits in a column the page heads as hexadecimal are stored as printed; `0x` is not added.  A scan code beside a virtual key, a code page beside a character set, and a locale beside an LCID are not constant values, so those tables are not read.  Symbol decoration (`_Name@N`) and export ordinals are not in these documents, so none is recorded.

## The gaps

`reports/gaps.tsv` lists, for every CE-only entity, which of the three things an include/def generator needs is missing from the documents collected so far:

`doc_role` in `kb/entities.jsonl` says what the corpus has for a name: `api-definition` (a page prints its syntax), `api-page` (a reference page without a syntax block -- the gap this list is about) or `topic` (the name is only the title of a prose page, so it is not listed here).

| missing | entities | what to collect |
|---------|----------|-----------------|
| `no-declaration` | 3,089 | the page prints no syntax block -- look for the same topic in another collected set (another medium often has it), or add the SDK/DOC medium that does |
| `no-header` | 4,526 | the page has no `Header` requirement -- same approach |
| `no-library` | 15,115 | the page has no `Link Library`/`Library` requirement -- expected for compiler intrinsics and macros, worth collecting for functions |

## Using it

* `kb/entities.jsonl` -- one record per API name; `headers`, `libraries` and `dlls` are the include/link mapping, `syntax_declarations` the evidence for the declaration, `ce_sets` the version scope.
* `kb/entities.jsonl` `relations` -- the links between definitions (the page's own Unicode/ANSI pair, `Interface::Method`, the CE<->Win32 layer match, `ce-name-lead` for a name the CE page prints under a different spelling), each with its page and the printed text; `present` says whether the target exists in this file.
* `kb/entities.jsonl` `generation_use` -- the derived, rule-based list of generator steps the record can feed (`include-declaration`, `type-definition`, `link-library`, `def-export`, `abi-layout`, `abi-members` when only the documented member list exists, `abi-note` when the declarations or pages state ABI facts, `unicode-mapping`, `version-scope`, `ce-restriction`). It says what the record *can* be used for, with the fields that justify it.
* `kb/modules.tsv` -- sdk-api module -> entities (the Win32-side grouping; the module comes from each page's UID).
* `kb/declarations.jsonl` -- the raw C/C++ declarations. Nothing is normalised: an include generator reads the text and the `spacing` flag.
* `kb/declarations-dotnet.jsonl` -- the signature blocks of the separated .NET layer (`language: managed`), kept out of the C declaration file on purpose.
* `kb/requirements.jsonl` -- Header/Library/DLL/OS-version statements with both the mapped `field` and the page's own `label`.
* `kb/constraints.jsonl` -- the Windows CE restriction sentences (`kind: "ce-restriction"`) and the ABI sentences a page states (`kind: "abi-note"`, with the `pattern` that matched: alignment, byte order, pointer width, structure size). Each is quoted, not summarised.
* `kb/constants.jsonl` -- one row of a name/value table a page prints, or one cell printed `NAME = 0x0001` / `NAME (0x0001)` (the identifier and the number, both as printed; `decimal` only when the page prints a decimal beside the value; `headers` only the header files that same page names). A constant the page does not number is not here.
* `kb/sets.tsv`, `kb/headers.tsv`, `kb/libraries.tsv`, `kb/dlls.tsv`, `kb/modules.tsv` -- the same data aggregated.

