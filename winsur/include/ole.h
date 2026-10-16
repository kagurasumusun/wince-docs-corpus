/* ole.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 11 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OLE_
#define _OLE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define HGLOBAL HANDLE
#define LRESULT LONG
#define OF_GET 2
#define OF_HANDLER 4
#define OF_SET 1
#define OLE_CONST const
#define OLE_LPCSTR LPCSTR
#define OLEVERB_PRIMARY 0
#define OT_EMBEDDED 2L
#define OT_LINK 1L
#define OT_STATIC 3L

#endif /* _OLE_ */
