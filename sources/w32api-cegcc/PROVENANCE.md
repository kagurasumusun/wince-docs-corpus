# PROVENANCE — CeGCC w32api headers (primary cross-check reference, REVIEW ONLY)

Primary pinned reference for the `winsur/` cross-check reports in
`knowledge/reports/xcheck-*.tsv|.md`.  This file is the licence
investigation the project requires before any outside reference may be
used: acquisition route, publisher, licence scope, usage decision.

**Why this reference is primary.**  Windows CE is a 32-bit target; the
`mingw-w64` reference (see `sources/mingw-w64/`) is 64-bit desktop
Windows material and survives only as a secondary reference.  CeGCC is
the gcc cross-development toolchain *for Windows CE itself*; its
`w32api` module is the classic mingw.org w32api **adapted for CE**
(`ChangeLog.ce`, `libce/`, `_WIN32_WCE` branches in 29 headers
including `winbase.h`), making it the closest public reference to the
CE SDK surface.

## Acquisition route

- Upstream project: **CeGCC** (`https://cegcc.sourceforge.net/`), a
  SourceForge project.  Its SVN layout keeps the headers in the
  `w32api` module.  A 160 MB full-SVN clone (`svn2github/cegcc` on
  GitHub) exists; it was refused as an acquisition target — only the
  w32api module is needed here.
- Downloaded: `https://codeload.github.com/MaxKellermann/w32api/tar.gz/8e64b608fc9c4d81e206e920ecc977d941577bef`
  — the focused GitHub mirror of exactly that w32api module.
  (`jkoan/cegcc-w32api` on GitHub has the *identical* head commit
  `8e64b608fc9c`; it is the same content under a name that says
  "cegcc".)
- Pinned commit: `8e64b608fc9c4d81e206e920ecc977d941577bef`
  (branch `wip`, commit date 2017-10-19, "winnt.h: Add support for ARM
  floating point registers in CONTEXT", fetched 2026-10-14)
- Stored here: `w32api-cegcc-8e64b608fc9c4d81e206e920ecc977d941577bef-src.tar.gz`
  (1.4 MB), sha256 `0ae478eef6a43510b1242a5a709f2d6d5eeb35056b95207b16c5ee36a3ba7db9`

## Publisher and authorship

The package header (`README.w32api`, kept beside this file as
`PUBLIC-DOMAIN-README.w32api.txt`): "Free headers and libraries for
the Win32 API — Originally written by Anders Norlander … Now
maintained by MinGW Developers … URL: http://www.mingw.org".  The CE
adaptation is the CeGCC project's work (mirror maintained by
Max Kellermann, a CeGCC developer).  It is NOT Microsoft material and
is kept entirely outside `corpus/` — a third-party reference, never a
corpus source.

## Licence scope (verified from the files in the tarball)

- The package statement in `README.w32api` (verbatim):
  > "Unless otherwise stated in individual source files,
  > THIS SOFTWARE IS NOT COPYRIGHTED.  This source code is offered for
  > use in the public domain.  You may use, modify or distribute it
  > freely."
- Its own exceptions, named in the same file:
  - portions of `winsock.h`, `winsock2.h`, `ws2tcpip.h`: University of
    California (1980–1993) and Digital Equipment (1993) copyright —
    permissive BSD-style notices;
  - `gl.h`: from the Mesa 3-D graphics library, Brian Paul
    (1999–2001), permissive Mesa licence, notice retention.
- Per-file scan of all **256** files directly inside `include/` at the
  pinned commit (the *same* rules are re-run and re-counted by
  `tools/xcheck_references.py`, so the tally is reproducible):
  233 files carry no own notice (package-level public domain), 20
  repeat the public-domain wording (one of them, `rtutils.h`, alongside
  a permissive notice), and 3 (`winsock.h`, `winsock2.h`, `ws2tcpip.h`)
  carry the UCB/DEC notices named by the package.  No other restrictive
  licence was located; no LGPL/GPL wording anywhere in the parse scope.
  Parse scope is that top level only — no recursion, so the `GL/`
  subdirectory (the Mesa-licensed `gl.h` the package names) is outside
  every report.
- `lib/` holds 91 and `libce/` holds 59 linker `.def` export lists
  (including `coredll.def`, `aygshell.def`, `CellCore.def`) under the
  same package statement; they are parsed as a second cross-check
  channel for the `winsur/link/*.def` worklists.

## Usage decision

- **Parsing scope:** every file of `include/`, plus `lib/*.def` and
  `libce/*.def` — all public domain or short permissive notices, all
  quoted with header:line attribution in the reports.
- **Cross-check reports** in `knowledge/reports/` remain review-only
  (a listed name is a lead, not a value to adopt).
- **Generator gap-fill (not a copy):** `tools/w32api_gaps.py` may emit
  a `#define` into `winsur/` only when a CE page *names* the constant
  and no CE/Win32 documentation page numbers it.  Whole headers are
  never copied.  `MAX_PATH` is never taken (CE prints 128).  winsock/gl
  files stay out of parse scope.
- Candidates evaluated and NOT taken (recorded so the search is
  reproducible): vanilla mingw.org w32api mirrors on GitHub
  (`onixie/w32api`, `crossbuild/w32api`) — same public-domain package
  *without* the CE adaptation, subsumed by this acquisition; Wine
  project headers (LGPL — refused by policy); ReactOS headers (GPL —
  refused); Mono's C# interop constants (MIT but the same community
  numbers role as the already isolated pinvoke layer — would duplicate
  it, not extend it); `gkvas/wince` (repackaged binaries, no licence
  clarity).
