/* lfapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 20 declarations, 2 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LFAPI_
#define _LFAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define LOCATION_OFFSET_UNSET 0xFFFFFFFF

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* LOCATION_REPORT_LATLONG  [struct; ce-only] */

/* PLUGIN_STATE  [enum; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* LOCATION_SERVICE_STATE  [struct; ce-only] */
typedef struct _LOCATION_SERVICE_STATE {
 DWORD serviceState; 
 DWORD numLoadedProviders;
 DWORD numLoadedResolvers;
 DWORD numActiveProviders;
 DWORD numActiveResolvers;
} LOCATION_SERVICE_STATE, *PLOCATION_SERVICE_STATE;

#endif /* _LFAPI_ */
