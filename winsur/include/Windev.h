/* Windev.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINDEV_
#define _WINDEV_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CTL_CODE  [macro, function; ce-only] */
#define CTL_CODE( DeviceType, Function, Method, Access) (
 ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method));

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* IsAPIReady  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.dll, coredll.dll] */
BOOL IsAPIReady(
 DWORD hAPI
);
#endif /* _WIN32_WCE */

#endif /* _WINDEV_ */
