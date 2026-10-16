/* astdtapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ASTDTAPI_
#define _ASTDTAPI_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* tapiRequestMakeCall  [function; shared; CE 6.0..699; cellcore.lib; A/W tapiRequestMakeCallA,tapiRequestMakeCallW (CE is W-side)] */
LONG tapiRequestMakeCall (
 LPCTSTR lpszDestAddress,
 LPCTSTR lpszAppName,
 LPCTSTR lpszCalledParty,
 LPCTSTR lpszComment 
);
#endif /* _WIN32_WCE */

#endif /* _ASTDTAPI_ */
