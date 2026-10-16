/* Htiframe.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _HTIFRAME_
#define _HTIFRAME_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FINDFRAME_FLAGS  [enum; ce-only] */
typedef enum { 
 FINDFRAME_NONE = 0, 
 FINDFRAME_JUSTTESTEXISTENCE = 1, 
 FINDFRAME_INTERNAL = 0x80000000 
} FINDFRAME_FLAGS;
typedef FINDFRAME_FLAGS *PFINDFRAME_FLAGS, *LPFINDFRAME_FLAGS;

/* FRAMEOPTIONS_FLAGS  [enum; ce-only] */
typedef enum { 
 FRAMEOPTIONS_SCROLL_YES = 0x00000001, 
 FRAMEOPTIONS_SCROLL_NO = 0x00000002, 
 FRAMEOPTIONS_SCROLL_AUTO = 0x00000004, 
 FRAMEOPTIONS_NORESIZE = 0x00000008, 
 FRAMEOPTIONS_NO3BORDER = 0x00000010, 
 FRAMEOPTIONS_DESKTOP = 0x00000020, 
 FRAMEOPTIONS_BROWSERBAND = 0x00000040 
} FRAMEOPTIONS_FLAGS;
typedef FRAMEOPTIONS_FLAGS *PFRAMEOPTIONS_FLAGS, *LPFRAMEOPTIONS_FLAGS;

#endif /* _HTIFRAME_ */
