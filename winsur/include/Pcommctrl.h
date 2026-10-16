/* Pcommctrl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PCOMMCTRL_
#define _PCOMMCTRL_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DPA  [struct; ce-only] */
typedef struct _DPA {
 int cp;
 void FAR* FAR* pp;
 HANDLE hheap;
 int cpAlloc;
 int cpGrow;
} DPA;
typedef DPA *PDPA, *LPDPA;

#endif /* _PCOMMCTRL_ */
