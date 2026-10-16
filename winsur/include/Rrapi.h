/* Rrapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RRAPI_
#define _RRAPI_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699 */

/* CeRapiFreeBuffer  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
HRESULT CeRapiFreeBuffer( 
 LPVOID Buffer 
);
#endif /* _WIN32_WCE */

#endif /* _RRAPI_ */
