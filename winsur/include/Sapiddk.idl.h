/* Sapiddk.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SAPIDDK_IDL_
#define _SAPIDDK_IDL_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SPCFGNOTIFY  [enum; ce-only] */
typedef enum SPCFGNOTIFY{
 SPCFGN_ADD,
 SPCFGN_REMOVE,
 SPCFGN_INVALIDATE,
 SPCFGN_ACTIVATE,
 SPCFGN_DEACTIVATE
} SPCFGNOTIFY;
typedef SPCFGNOTIFY *PSPCFGNOTIFY, *LPSPCFGNOTIFY;

#endif /* _SAPIDDK_IDL_ */
