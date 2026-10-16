/* Kwin32.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _KWIN32_
#define _KWIN32_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* OEMIoControl  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL OEMIoControl( 
 DWORD dwIoControlCode, 
 LPVOID lpInBuf, 
 DWORD nInBufSize, 
 LPVOID lpOutBuf, 
 DWORD nOutBufSize, 
 LPDWORD lpBytesReturned 
);
#endif /* _WIN32_WCE */

#endif /* _KWIN32_ */
