/* Httpfilt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 16 declarations, 8 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _HTTPFILT_
#define _HTTPFILT_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* SF_NOTIFY_ACCESS_DENIED  [function, typedef; ce-only; entity-headers] */

/* SF_NOTIFY_AUTHENTICATION  [function, typedef; ce-only; entity-headers] */

/* SF_NOTIFY_LOG  [function, typedef; ce-only; entity-headers] */

/* SF_NOTIFY_PREPROC_HEADERS  [function, typedef; ce-only; entity-headers] */

/* SF_NOTIFY_READ_RAW_DATA  [function, typedef; ce-only; entity-headers] */

/* SF_NOTIFY_SEND_RAW_DATA  [function, typedef; ce-only; entity-headers] */

/* SF_NOTIFY_SEND_RESPONSE  [function, typedef; ce-only; entity-headers] */

/* SF_NOTIFY_URL_MAP  [function, typedef; ce-only; entity-headers] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* HTTP_FILTER_ACCESS_DENIED  [struct; ce-only] */
typedef struct _HTTP_FILTER_ACCESS_DENIED{
 const CHAR* pszURL;
 const CHAR* pszPhysicalPath;
 DWORD dwReason;
} HTTP_FILTER_ACCESS_DENIED, *PHTTP_FILTER_ACCESS_DENIED;

/* HTTP_FILTER_AUTHENT  [struct; ce-only] */
typedef struct _HTTP_FILTER_AUTHENT{ 
 CHAR* pszUser;
 DWORD cbUserBuff;
 CHAR* pszPassword;
 DWORD cbPasswordBuff;
} HTTP_FILTER_AUTHENT, *PHTTP_FILTER_AUTHENT;

/* HTTP_FILTER_CONTEXT  [struct; ce-only] */
typedef struct _HTTP_FILTER_CONTEXT {
 DWORD cbSize;
 DWORD Revision; 
 PVOID ServerContext; 
 DWORD ulReserved; 
 BOOL fIsSecurePort; 
 PVOID pFilterContext; 
 BOOL (WINAPI* GetServerVariable); 
 BOOL (WINAPI* AddResponseHeaders); 
 BOOL (WINAPI* WriteClient); 
 VOID* (WINAPI* AllocMem); 
 BOOL (WINAPI* ServerSupportFunction); 
} HTTP_FILTER_CONTEXT, *PHTTP_FILTER_CONTEXT;

/* HTTP_FILTER_LOG  [struct; ce-only] */
typedef struct _HTTP_FILTER_LOG{
 const CHAR* pszClientHostName;
 const CHAR* pszClientUserName;
 const CHAR* pszServerName;
 const CHAR* pszOperation;
 const CHAR* pszTarget;
 const CHAR* pszParameters;
 DWORD dwHttpStatus;
 DWORD dwWin32Status;
 DWORD dwBytesSent;
 DWORD dwBytesRecvd;
 DWORD msTimeForProcessing;
} HTTP_FILTER_LOG, *PHTTP_FILTER_LOG;

/* HTTP_FILTER_PREPROC_HEADERS  [struct; ce-only] */
typedef struct _HTTP_FILTER_PREPROC_HEADERS{
BOOL (WINAPI* GetHeader)(
 struct _HTTP_FILTER_CONTEXT* pfc,
 LPSTR lpszName,
 LPVOID lpvBuffer,
 LPDWORD lpdwSize
 );
BOOL (WINAPI* SetHeader)(
 struct _HTTP_FILTER_CONTEXT* pfc,
 LPSTR lpszName,
 LPSTR lpszValue
 ); 
BOOL (WINAPI* AddHeader)( 
 struct _HTTP_FILTER_CONTEXT* pfc,
 LPSTR lpszName,
 LPSTR lpszValue
 ); 
 DWORD HttpStatus;
 DWORD dwReserved;
} HTTP_FILTER_PREPROC_HEADERS, *PHTTP_FILTER_PREPROC_HEADERS;

/* HTTP_FILTER_RAW_DATA  [struct; ce-only] */
typedef struct _HTTP_FILTER_RAW_DATA{
 PVOID pvInData;
 DWORD cbInData;
 DWORD cbInBuffer;
 DWORD dwReserved;
} HTTP_FILTER_RAW_DATA, *PHTTP_FILTER_RAW_DATA;

/* HTTP_FILTER_SEND_RESPONSE  [struct; ce-only; Httpfilt.lib] */
typedef struct HTTP_FILTER_SEND_RESPONSE{
 BOOL (WINAPI* GetHeader); 
 BOOL (WINAPI* SetHeader); 
 BOOL (WINAPI* AddHeader); 
 DWORD HttpStatus;
 DWORD dwReserved; 
} HTTP_FILTER_SEND_RESPONSE, *PHTTP_FILTER_SEND_RESPONSE;

/* HTTP_FILTER_URL_MAP  [struct; ce-only] */
typedef struct _HTTP_FILTER_URL_MAP{
 const CHAR* pszURL;
 CHAR* pszPhysicalPath;
 DWORD cbPathBuff;
} HTTP_FILTER_URL_MAP, *PHTTP_FILTER_URL_MAP;

/* SF_REQ_TYPE  [enum; ce-only] */
enum SF_REQ_TYPE{
 SF_REQ_SEND_RESPONSE_HEADER,
 SF_REQ_ADD_HEADERS_ON_DENIAL,
 SF_REQ_SET_NEXT_READ_SIZE,
 SF_REQ_SET_PROXY_INFO,
 SF_REQ_GET_CONNID,
 SF_REQ_SET_CERTIFICATE_INFO,
 SF_REQ_GET_PROPERTY,
 SF_REQ_NORMALIZE_URL,
 SF_REQ_DISABLE_NOTIFICATIONS
} ;

/* SF_REQ_DISABLE_NOTIFICATIONS  [extra enum] */
enum SF_REQ_TYPE{
  SF_REQ_SEND_RESPONSE_HEADER,
  SF_REQ_ADD_HEADERS_ON_DENIAL,
  SF_REQ_SET_NEXT_READ_SIZE,
  SF_REQ_SET_PROXY_INFO,
  SF_REQ_GET_CONNID,
  SF_REQ_SET_CERTIFICATE_INFO,
  SF_REQ_GET_PROPERTY,
  SF_REQ_NORMALIZE_URL,
  SF_REQ_DISABLE_NOTIFICATIONS
} ;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* AddHeader  [function; ce-only; CE 3.0..399, 5.0..699; Httpfilt.lib, httpfilt.lib] */
BOOL WINAPI* AddHeader(
 PHTTP_FILTER_CONTEXT pfc, 
 LPSTR lpszName, 
 LPSTR lpszValue
);

/* AddResponseHeaders  [function; ce-only; CE 3.0..399, 5.0..699] */
BOOL WINAPI* AddResponseHeaders(
 PHTTP_FILTER_CONTEXT pfc,
 LPSTR lpszHeaders,
 LPSTR dwReserved 
);

/* AllocMem  [function; ce-only; CE 3.0..399, 5.0..699; Httpfilt.lib, httpfilt.lib] */
VOID* WINAPI* AllocMem(
 PHTTP_FILTER_CONTEXT pfc,
 DWORD cbSize,
 DWORD dwReserved 
);

/* HttpFilterProc  [function; ce-only; CE 3.0..399, 5.0..699; httpfilt.lib] */
DWORD WINAPI HttpFilterProc(
 PHTTP_FILTER_CONTEXT pfc, 
 DWORD NotificationType, 
 VOID* pvNotification
);

/* TerminateFilter  [function; ce-only; CE 3.0..399, 5.0..699; httpfilt.lib] */
BOOL WINAPI TerminateFilter(
 DWORD dwFlags
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL WINAPI *SetHeader(  PHTTP_FILTER_CONTEXT pfc,  LPSTR lpszName,  LPSTR lpszValue );

#endif /* _HTTPFILT_ */
