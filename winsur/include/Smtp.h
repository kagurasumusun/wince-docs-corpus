/* Smtp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 13 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _SMTP_
#define _SMTP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define TRANSPORT_CONN_LOST WM_USER + 1
#define TRANSPORT_REFRESH WM_USER + 2

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213)) /* CE 1.0..199, 2.11..2.12 */

/* TransportConnect  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportConnect(HANDLE hService, DWORD dwFlags, HWND hNotify, (BOOL) (*CallBack)(int iStatus, BOOL bUnknownmax));

/* TransportCount  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportCount(HANDLE hService, LPWORD lpNumMsgs);

/* TransportDel  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportDelete(HANDLE hService, MailMsg *MsgPtr);

/* TransportDisconnect  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportConnect(HANDLE hService);

/* TransportError  [function; ce-only; CE 1.0..199, 2.11..2.12] */
int TransportError(HANDLE hService);

/* TransportFreeMsg  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportFreeMessage(MailMsg * MsgPtr);

/* TransportInit  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportInit (HANDLE *NewService, LPWSTR szCommonKey, LPWSTR szTransportKey,);

/* TransportNonIpm  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportNonIpm (MailMsg * pmm);

/* TransportProps  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportProps(HWND hwndParent, LPWSTR szCommonKey, LPWSTR szTransportKey,);

/* TransportRelease  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportRelease(HANDLE hService);

/* TransportSetPassword  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportSetPassword(HANDLE * InPtr, LPWSTR pszPassword, BOOL fRemember);

/* TransportView  [function; ce-only; CE 1.0..199, 2.11..2.12] */
BOOL TransportView(HWND hwndParent, MailMsg *MsgPtr);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213)) /* CE 2.11..2.12 */

/* TransportErrorMsg  [function; ce-only; CE 2.11..2.12] */
int TransportErrorMsg(HANDLE hService, LPWSTR szBuf, int iBufLen, 
int *piSrcLine,);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL TransportDelete(HANDLE hService, MailMsg *MsgPtr);
BOOL TransportFreeMessage(MailMsg * MsgPtr);

#endif /* _SMTP_ */
