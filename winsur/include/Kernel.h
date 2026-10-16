/* Kernel.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 5 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _KERNEL_
#define _KERNEL_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* FlushDCache  [function; ce-only; CE 4.0..699; Nk.lib] */
void FlushDCache(void);

/* FlushICache  [function; ce-only; CE 4.0..699; Nk.lib] */
void FlushICache(void);

/* KLocalFileTimeToFileTime  [function; ce-only; CE 4.0..699; Nk.lib] */
BOOL KLocalFileTimeToFileTime(
 const FILETIME* lpft,
 LPFILETIME lpst
);

/* OEMCacheRangeFlush  [function; ce-only; CE 4.0..699] */
void OEMCacheRangeFlush(
 LPVOID pAddr,
 DWORD dwLength,
 DWORD dwFlags 
);

/* SC_GetTickCount  [function; ce-only; CE 4.0..699; Nk.lib, Nkstub.lib] */
DWORD SC_GetTickCount(void);
#endif /* _WIN32_WCE */

#endif /* _KERNEL_ */
