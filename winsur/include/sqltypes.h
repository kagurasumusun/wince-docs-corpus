/* sqltypes.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SQLTYPES_
#define _SQLTYPES_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ODBCINT64 __int64
#define SQL_API __stdcall
#define SQL_MAX_NUMERIC_LEN 16
#define SQLLEN SQLINTEGER
#define SQLROWCOUNT SQLUINTEGER
#define SQLROWOFFSET SQLINTEGER
#define SQLSETPOSIROW SQLUSMALLINT
#define SQLTRANSID DWORD
#define SQLULEN SQLUINTEGER

#endif /* _SQLTYPES_ */
