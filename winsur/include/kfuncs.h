/* kfuncs.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 38 constants, 42 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _KFUNCS_
#define _KFUNCS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define EVENT_PULSE 1
#define EVENT_RESET 2
#define EVENT_SET 3
#define HT_AFSVOLUME 16
#define HT_APISET 6
#define HT_CRITSEC 12
#define HT_DBFILE 9
#define HT_DBFIND 10
#define HT_EVENT 4
#define HT_FILE 7
#define HT_FIND 8
#define HT_FSMAP 14
#define HT_MUTEX 5
#define HT_SEMAPHORE 13
#define HT_SOCKET 11
#define HT_WNETENUM 15
#define OEM_CERTIFY_RUN 1
#define OEM_CERTIFY_TRUST 2
#define SH_COMM 83
#define SH_CPROG 88
#define SH_CURPROC 2
#define SH_CURTHREAD 1
#define SH_CURTOKEN 3
#define SH_D3DM 92
#define SH_DDRAW 91
#define SH_DEVMGR_APIS 86
#define SH_FILESYS_APIS 84
#define SH_GDI 80
#define SH_SERVICES 90
#define SH_SHELL 85
#define SH_TAPI 87
#define SH_WIN32 0
#define SH_WMGR 81
#define SH_WNET 82
#define SYS_HANDLE_BASE 64
#define SYSHANDLE_OFFSET 0x004
#define TLS_FUNCALLOC 0
#define TLS_FUNCFREE 1

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* WaitForAPIReady  [function, macro; ce-only; coredll.dll] */
DWORD WaitForAPIReady(
DWORD dwAPISlotIndex,
DWORD dwTimeout
);

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* DebugBreak  [function; ce-only; harvest-kb; harvest-kb] */
void DebugBreak( void );

/* GetCurrentProcess  [function; ce-only; harvest-kb; harvest-kb] */
HANDLE GetCurrentProcess(void);

/* GetCurrentProcessId  [function; ce-only; harvest-kb; harvest-kb] */
DWORD GetCurrentProcessId(void);

/* GetCurrentThread  [function; ce-only; harvest-kb; harvest-kb] */
HANDLE GetCurrentThread(void);

/* GetCurrentThreadId  [function; ce-only; harvest-kb; harvest-kb] */
DWORD GetCurrentThreadId(void);

/* ResetEvent  [function; ce-only; harvest-kb; harvest-kb] */
BOOL ResetEvent( 
HANDLE hEvent );

/* SetEvent  [function; ce-only; harvest-kb; harvest-kb] */
BOOL SetEvent( 
HANDLE hEvent );

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* CeGetCallerTrust  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib] */
DWORD CeGetCallerTrust (void);

/* CeGetCurrentTrust  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, nk.lib] */
DWORD CeGetCurrentTrust (void);
#endif /* _WIN32_WCE */

#endif /* _KFUNCS_ */
