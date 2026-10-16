/* bthutil.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _BTHUTIL_
#define _BTHUTIL_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BTH_RADIO_MODE  [enum; ce-only] */
enum BTH_RADIO_MODE {
 BTH_POWER_OFF,
 BTH_CONNECTABLE,
 BTH_DISCOVERABLE
};

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* BthGetMode  [function; ce-only; CE 6.0..699; Bthutil.lib] */
int BthGetMode(
 DWORD*
 pdwMode
);

/* BthSetMode  [function; ce-only; CE 6.0..699; Bthutil.lib] */
int BthSetMode(
 DWORD
 dwMode
);
#endif /* _WIN32_WCE */

#endif /* _BTHUTIL_ */
