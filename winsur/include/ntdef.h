/* ntdef.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NTDEF_
#define _NTDEF_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define NTAPI __stdcall
#define OBJ_CASE_INSENSITIVE 64L
#define OBJ_EXCLUSIVE 32L
#define OBJ_INHERIT 2L
#define OBJ_OPENIF 128L
#define OBJ_OPENLINK 256L
#define OBJ_PERMANENT 16L
#define OBJ_VALID_ATTRIBUTES 498L
#define STATUS_SUCCESS ((NTSTATUS)0)

#endif /* _NTDEF_ */
