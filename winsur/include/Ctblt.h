/* Ctblt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CTBLT_
#define _CTBLT_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* SetClearTypeBltGamma  [function; ce-only; CE 5.0..699; Ctblt.lib] */
void SetClearTypeBltGamma(
 ULONG ulGamma
);

/* SetClearTypeBltMasks  [function; ce-only; CE 5.0..699; Ctblt.lib] */
void SetClearTypeBltMasks(
 ULONG fRedMask,
 ULONG fGreMask,
 ULONG fBluMask
);
#endif /* _WIN32_WCE */

#endif /* _CTBLT_ */
