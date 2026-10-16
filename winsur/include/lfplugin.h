/* lfplugin.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 18 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LFPLUGIN_
#define _LFPLUGIN_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* ProviderIoctlCall  [function; ce-only; CE 6.0..699] */
DWORD ProviderIoctlCall(
 HANDLE hProv, 
 DWORD dwCode, 
 BYTE* pBufIn, 
 DWORD cbIn, 
 BYTE* pBufOut, 
 DWORD* pcbOut
);

/* ProviderIoctlClose  [function; ce-only; CE 6.0..699] */
DWORD ProviderIoctlClose(
 HANDLE hProv
);

/* ProviderStop  [function; ce-only; CE 6.0..699] */
DWORD ProviderStop(void);

/* ProviderUnInitialize  [function; ce-only; CE 6.0..699] */
DWORD ProviderStop(void);

/* ResolverIoctlCall  [function; ce-only; CE 6.0..699] */
DWORD ResolverIoctlCall(
 HANDLE hProv,
 DWORD dwCode,
 BYTE* pBufIn,
 DWORD cbIn,
 BYTE* pBufOut,
 DWORD* pcbOut
);

/* ResolverIoctlClose  [function; ce-only; CE 6.0..699] */
DWORD ResolverIoctlClose(
 HANDLE hProv
);

/* ResolverStop  [function; ce-only; CE 6.0..699] */
DWORD ResolverStop(void);

/* ResolverUnInitialize  [function; ce-only; CE 6.0..699] */
DWORD ResolverUnInitialize(void);
#endif /* _WIN32_WCE */

#endif /* _LFPLUGIN_ */
