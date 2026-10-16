/* Msr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MSR_
#define _MSR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* NKrdmsr  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL NKrdmsr(
 DWORD dwAddr,
 DWORD* lpdwValHigh,
 DWORD* lpdwValLow
);

/* NKwrmsr  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL NKwrmsr(
 DWORD dwAddr,
 DWORD dwValHigh,
 DWORD dwValLow
);
#endif /* _WIN32_WCE */

#endif /* _MSR_ */
