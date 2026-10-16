/* Wcesock.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WCESOCK_
#define _WCESOCK_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210)) /* CE 2.0..209 */

/* AfxGetCeSocketWindow  [function; ce-only; CE 2.0..209] */
HWND AfxGetCeSocketWindow();
#endif /* _WIN32_WCE */

#endif /* _WCESOCK_ */
