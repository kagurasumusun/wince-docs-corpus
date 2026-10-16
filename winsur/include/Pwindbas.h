/* Pwindbas.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 10 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _PWINDBAS_
#define _PWINDBAS_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* REPLCHANGEINFO  [struct; ce-only] */
struct REPLCHANGEINFO {
 WORD wVersion;
 WORD wStatus;
 WORD wObjType;
 CEOID oidChanged;
 CEOID oidDbase;
};

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* GetSystemMemoryDivision  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL GetSystemMemoryDivision(
 LPDWORD lpdwStorePages,
 LPDWORD lpdwRamPages,
 LPDWORD lpdwPageSize
);

/* SetSystemMemoryDivision  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD SetSystemMemoryDivision(
 DWORD dwStorePages
);
#endif /* _WIN32_WCE */

#endif /* _PWINDBAS_ */
