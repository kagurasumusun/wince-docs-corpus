/* Kitlclnt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _KITLCLNT_
#define _KITLCLNT_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* KITLDeInitLibrary  [function; ce-only; CE 5.0..699; Kitldll.lib, kitldll.lib] */
BOOL KITLDeInit Library (void);

/* KITLInitLibrary  [function; ce-only; CE 5.0..699; Kitldll.lib, kitldll.lib] */
BOOL KITLInit Library(
 LPCWSTR pszRegKeyRoot
);
#endif /* _WIN32_WCE */

#endif /* _KITLCLNT_ */
