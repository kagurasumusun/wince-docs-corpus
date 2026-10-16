/* Webproxy.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WEBPROXY_
#define _WEBPROXY_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* PROXY_HTTP_INFORMATION  [struct; ce-only] */
typedef struct _PROXY_HTTP_INFORMATION {
 DWORD dwSize;
 DWORD dwProxyVersion;
} PROXY_HTTP_INFORMATION, *PPROXY_HTTP_INFORMATION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* ProxyInitializeFilter  [function; ce-only; CE 5.0..699] */
DWORD WINAPI ProxyInitializeFilter(
 PPROXY_HTTP_INFORMATION pInfo
);

/* ProxyNotifyAddrChange  [function; ce-only; CE 5.0..699] */
DWORD WINAPI ProxyNotifyAddrChange(void);

/* ProxySignalFilter  [function; ce-only; CE 5.0..699] */
DWORD ProxySignalFilter(
 DWORD dwSignal
);

/* ProxyUninitializeFilter  [function; ce-only; CE 5.0..699] */
DWORD WINAPI ProxyUninitializeFilter (void);
#endif /* _WIN32_WCE */

#endif /* _WEBPROXY_ */
