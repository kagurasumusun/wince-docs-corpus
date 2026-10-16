/* Oalintr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _OALINTR_
#define _OALINTR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x600)) /* CE 4.0..599 */

/* OEMRequestSysIntr  [function; ce-only; CE 4.0..599] */
DWORD OEMRequestSysIntr(DWORD Irq);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* PerfCountFreq  [function; ce-only; CE 4.0..699; Nk.lib] */
DWORD PerfCountFreq();
#endif /* _WIN32_WCE */

#endif /* _OALINTR_ */
