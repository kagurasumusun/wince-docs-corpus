/* Tl.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _TL_IDL_
#define _TL_IDL_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* TLPUBINFO  [struct; ce-only] */
typedef struct TLPUBINFO { 
 DWORD cbSize; 
 DWORD dwVersion; 
 DWORD dwFlags; 
 DWORD dwConnectTimeOut; 
 DWORD dwKeepAliveTimeOut; 
 DWORD cbDataSize; 
 BYTE pData[1]; 
} TLPUBINFO, *PTLPUBINFO;

#endif /* _TL_IDL_ */
