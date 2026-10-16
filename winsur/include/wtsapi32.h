/* wtsapi32.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 28 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WTSAPI32_
#define _WTSAPI32_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define NOTIFY_FOR_ALL_SESSIONS 1
#define NOTIFY_FOR_THIS_SESSION 0
#define PWTS_SESSION_INFO PWTS_SESSION_INFOW
#define WM_WTSSESSION_CHANGE 0x02B1
#define WTS_CONSOLE_CONNECT 0x1
#define WTS_CONSOLE_DISCONNECT 0x2
#define WTS_CURRENT_SERVER_HANDLE 0
#define WTS_CURRENT_SESSION ((DWORD)-1)
#define WTS_EVENT_ALL 0x7FFFFFFF
#define WTS_EVENT_CONNECT 0x00000008
#define WTS_EVENT_CREATE 0x00000001
#define WTS_EVENT_DELETE 0x00000002
#define WTS_EVENT_DISCONNECT 0x00000010
#define WTS_EVENT_FLUSH 0x80000000
#define WTS_EVENT_LICENSE 0x00000100
#define WTS_EVENT_LOGOFF 0x00000040
#define WTS_EVENT_LOGON 0x00000020
#define WTS_EVENT_NONE 0x00000000
#define WTS_EVENT_RENAME 0x00000004
#define WTS_EVENT_STATECHANGE 0x00000080
#define WTS_REMOTE_CONNECT 0x3
#define WTS_REMOTE_DISCONNECT 0x4
#define WTS_SESSION_INFO WTS_SESSION_INFOW
#define WTS_SESSION_LOCK 0x7
#define WTS_SESSION_LOGOFF 0x6
#define WTS_SESSION_LOGON 0x5
#define WTS_SESSION_REMOTE_CONTROL 0x9
#define WTS_SESSION_UNLOCK 0x8

#endif /* _WTSAPI32_ */
