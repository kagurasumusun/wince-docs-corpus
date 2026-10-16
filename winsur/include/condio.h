/* condio.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CONDIO_
#define _CONDIO_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* towlower  [function; ce-only; CE 5.0..599; coredll.dll] */
int towlower( wint_t c );

/* towupper  [function; ce-only; CE 5.0..599; coredll.dll] */
int towupper( wint_t c );
#endif /* _WIN32_WCE */

#endif /* _CONDIO_ */
