/* Devmgmt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DEVMGMT_
#define _DEVMGMT_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DMSDLINFO  [struct, typedef; ce-only] */
typedef struct {
 SYSTEMTIME stStartTime;
 SYSTEMTIME stDeltaTime;
 DWORD dwFlags;
 TCHAR wzDest [MAX_PATH];
 TCHAR wzCmdLine [MAX_PATH];
} DMSDLINFO, *PDMSDLINFO;

/* DMTASKINFO  [struct, typedef; ce-only] */
typedef struct {
 DWORD dwSize;
 SYSTEMTIME stStartTime;
 SYSTEMTIME stDeltaTime;
 SYSTEMTIME stRetryTime;
 DWORD dwType;
 DWORD dwMaxRetryTime;
 DWORD dwFlags;
 LPTSTR pwzRDN;
 LPTSTR pwzURL;
 LPTSTR pwzURLSig;
 LPTSTR pwzMisc;
 LPTSTR pwzData;
 LPTSTR pwzXml;
} DMTASKINFO, *PDMTASKINFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* CeSetDevMgmtTask  [function; ce-only; CE 4.0..699] */
HRESULT CeSetDevMgmtTask(
 DMTASKINFO* pdi
);

/* CeStartDevMgmtService  [function; ce-only; CE 4.0..699] */
HANDLE CeStartDevMgmtService(
 int nAction,
 HWND hCallbackWnd
);
#endif /* _WIN32_WCE */

#endif /* _DEVMGMT_ */
