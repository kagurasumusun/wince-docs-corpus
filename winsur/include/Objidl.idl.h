/* Objidl.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OBJIDL_IDL_
#define _OBJIDL_IDL_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* ISurrogate  [interface; shared; CE 5.0..599; Ole32.lib, Uuid.lib] */
#endif /* _WIN32_WCE */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BIND_FLAGS  [enum; shared] */
typedef enum tagBIND_FLAGS {
 BIND_MAYBOTHERUSER = 1, 
 BIND_JUSTTESTEXISTENCE = 2, 
} BIND_FLAGS;
typedef BIND_FLAGS *PBIND_FLAGS, *LPBIND_FLAGS;

#endif /* _OBJIDL_IDL_ */
