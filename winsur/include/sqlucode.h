/* sqlucode.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 6 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SQLUCODE_
#define _SQLUCODE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SQL_C_TCHAR SQL_C_WCHAR
#define SQL_C_WCHAR SQL_WCHAR
#define SQL_SQLSTATE_SIZEW 10
#define SQL_WCHAR (-8)
#define SQL_WLONGVARCHAR (-10)
#define SQL_WVARCHAR (-9)

#endif /* _SQLUCODE_ */
