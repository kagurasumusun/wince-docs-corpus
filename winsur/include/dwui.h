/* dwui.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _DWUI_
#define _DWUI_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* _BucketResponse  [struct; ce-only; DwUI.dll] */
typedef struct _BucketResponse {
 BOOL fUploadSucceeded;
 DWORD dwUploadError;
 char* pchUploadFile;
 int iBucket;
 int iBucketTable;
 char* pchResponse;
 int iResponseType;
} BucketResponse;

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* iResponseType  [?; ce-only; CE 6.0..699; DwUI.dll] */
enum {
 ResponseTypeMin = 0,
 ResponseTypeDialogLink = 0,
 ResponseTypeAutolaunch = 1,
 ResponseTypeDialogSurvey = 2,
 ResponseTypeLightweight = 3,
 ResponseTypeMax = 4,
};
#endif /* _WIN32_WCE */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* GetUserConsent  [function; ce-only; CE 6.0..699; DwUI.dll] */
HRESULT GetUserConsent(
 LPCWSTR pwzDumpFilePath,
 BOOL* pfUserConsented
);

/* WatsonUploadResponse  [function; ce-only; CE 6.0..699; DwUI.dll] */
HRESULT WatsonUploadResponse(
 BucketResponse* pBucketResponse
);
#endif /* _WIN32_WCE */

#endif /* _DWUI_ */
