/* Service.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 16 constants, 18 declarations, 2 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SERVICE_
#define _SERVICE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SERVICE_INIT_CONFIGURE_CONNECT 0x4
#define SERVICE_INIT_CONFIGURE_NO_CONNECT 0x2
#define SERVICE_INIT_CONFIGURE_PENDING_CONNECT 0x3
#define SERVICE_INIT_NO_CONFIGURE 0x1
#define SERVICE_INIT_STANDALONE 0x02
#define SERVICE_INIT_STARTED 0x00000000
#define SERVICE_INIT_STOPPED 0x00000001
#define SERVICE_LOCKED 0x8
#define SERVICE_NO_INIT 0x0
#define SERVICE_STATE_OFF 0
#define SERVICE_STATE_ON 1
#define SERVICE_STATE_SHUTTING_DOWN 3
#define SERVICE_STATE_STARTING_UP 2
#define SERVICE_STATE_UNINITIALIZED 5
#define SERVICE_STATE_UNKNOWN 0xffffffff
#define SERVICE_STATE_UNLOADING 4

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* SERVICE  [typedef; ce-only; heuristic-prefix] */

/* ServicesexeCallbackFunctions  [struct; ce-only] */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* ActivateService  [function; ce-only; unified-kb; unified-kb] */
HANDLE ActivateService( 
 LPCWSTR lpszDevKey, 
 DWORD dwClientInfo 
);

/* GetServiceHandle  [function; ce-only; unified-kb; unified-kb] */
HANDLE GetServiceHandle( 
 LPWSTR szPrefix, 
 LPWSTR szDllName, 
 DWORD pdwDllBuf 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* DeregisterService  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL DeregisterService(
 HANDLE hDevice
);

/* EnumServices  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL EnumServices(
 PBYTE pBuffer,
 DWORD pdwServiceEntries,
 DWORD pdwBufferLen
);

/* RegisterService  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
HANDLE RegisterService(
 LPCWSTR lpszType,
 DWORD dwIndex,
 LPCWSTR lpszLib,
 DWORD dwInfo
);

/* ServiceIoControl  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL ServiceIoControl(
 HANDLE hService,
 DWORD dwIoControlCode,
 LPVOID lpInBuf,
 DWORD nInBufSize,
 LPVOID lpOutBuf,
 DWORD nOutBufSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);

/* ServiceUnbindPorts  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL ServiceUnbindPorts(
 HANDLE hService
);
#endif /* _WIN32_WCE */

#endif /* _SERVICE_ */
