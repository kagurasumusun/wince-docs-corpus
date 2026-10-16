/* Windowsx.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINDOWSX_
#define _WINDOWSX_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DECLARE_HANDLE32 DECLARE_HANDLE
#define WM_CTLCOLOR 25

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* InsetRect  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL InsetRect( 
 LPRECT lprc, 
 int dx, 
 int dy 
);
#endif /* _WIN32_WCE */

#endif /* _WINDOWSX_ */
