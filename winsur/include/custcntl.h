/* custcntl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 7 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CUSTCNTL_
#define _CUSTCNTL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CCF_NOTEXT 1
#define CCHCCCLASS 32
#define CCHCCDESC 32
#define CCHCCTEXT 256
#define LPFNCCINFO LPFNCCINFOW
#define LPFNCCSIZETOTEXT LPFNCCSIZETOTEXTW
#define LPFNCCSTYLE LPFNCCSTYLEW

#endif /* _CUSTCNTL_ */
