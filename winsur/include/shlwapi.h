/* shlwapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 17 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SHLWAPI_
#define _SHLWAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DLLVER_PLATFORM_NT 0x00000002
#define DLLVER_PLATFORM_WINDOWS 0x00000001
#define STIF_DEFAULT 0x0L
#define STIF_SUPPORT_HEX 0x1L
#define URL_DONT_ESCAPE_EXTRA_INFO 0x02000000
#define URL_DONT_SIMPLIFY 0x08000000
#define URL_ESCAPE_PERCENT 0x00001000
#define URL_ESCAPE_SEGMENT_ONLY 0x00002000
#define URL_ESCAPE_SPACES_ONLY 0x04000000
#define URL_ESCAPE_UNSAFE 0x20000000
#define URL_INTERNAL_PATH 0x00800000
#define URL_PARTFLAG_KEEPSCHEME 0x00000001
#define URL_PLUGGABLE_PROTOCOL 0x40000000
#define URL_UNESCAPE 0x10000000
#define URL_UNESCAPE_HIGH_ANSI_ONLY 0x00400000
#define URL_UNESCAPE_INPLACE 0x00100000
#define WINSHLWAPI DECLSPEC_IMPORT

#endif /* _SHLWAPI_ */
