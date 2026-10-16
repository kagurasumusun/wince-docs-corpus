/* Shtypes.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SHTYPES_
#define _SHTYPES_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SHITEMID  [struct; shared] */
typedef struct _SHITEMID { 
 USHORT cb; 
 BYTE abID[1]; 
 } SHITEMID;
typedef SHITEMID *PSHITEMID, *LPSHITEMID;

#endif /* _SHTYPES_ */
