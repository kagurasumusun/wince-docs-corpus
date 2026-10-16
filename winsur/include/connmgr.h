/* connmgr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 18 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CONNMGR_
#define _CONNMGR_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */
#define INITGUID must
#endif /* _WIN32_WCE */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ConnMgrConRefTypeEnum  [enum; ce-only] */
typedef enum _ConnMgrConRefTypeEnum{
 ConRefType_NAP = 0,
 ConRefType_PROXY
} ConnMgrConRefTypeEnum;
typedef ConnMgrConRefTypeEnum *PConnMgrConRefTypeEnum, *LPConnMgrConRefTypeEnum;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* ConnMgrApiReadyEvent  [function; ce-only; unified-kb; unified-kb] */
HANDLE WINAPI ConnMgrApiReadyEvent (
 void
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* ConnMgrConnectionStatus  [function; ce-only; CE 6.0..699; cellcore.lib] */
HRESULT WINAPI ConnMgrConnectionStatus(
 HANDLE hConnection,
 DWORD *pdwStatus
);

/* ConnMgrReleaseConnection  [function; ce-only; CE 6.0..699; cellcore.lib] */
HRESULT WINAPI ConnMgrReleaseConnection(
 HANDLE hConnection,
 LONG lCache 
);

/* ConnMgrSetConnectionPriority  [function; ce-only; CE 6.0..699; cellcore.lib] */
HRESULT WINAPI ConnMgrSetConnectionPriority(
 HANDLE hConnection,
 DWORD dwPriority
);

/* ConnMgrUnregisterScheduledConnection  [function; ce-only; CE 6.0..699; cellcore.lib] */
HRESULT WINAPI ConnMgrUnregisterScheduledConnection(
 LPCWSTR pwszToken
);
#endif /* _WIN32_WCE */

#endif /* _CONNMGR_ */
