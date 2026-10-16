/* WinSvc.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 62 constants, 3 declarations, 0 outlines, 2 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINSVC_
#define _WINSVC_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SC_GROUP_IDENTIFIER SC_GROUP_IDENTIFIERW
#define SC_GROUP_IDENTIFIERA '+'
#define SC_GROUP_IDENTIFIERW L'+'
#define SC_MANAGER_ALL_ACCESS 0xf003f
#define SC_MANAGER_CONNECT 1
#define SC_MANAGER_CREATE_SERVICE 2
#define SC_MANAGER_ENUMERATE_SERVICE 4
#define SC_MANAGER_LOCK 8
#define SC_MANAGER_MODIFY_BOOT_CONFIG 32
#define SC_MANAGER_QUERY_LOCK_STATUS 16
#define SERVICE_ACCEPT_HARDWAREPROFILECHANGE 32
#define SERVICE_ACCEPT_NETBINDCHANGE 16
#define SERVICE_ACCEPT_PARAMCHANGE 8
#define SERVICE_ACCEPT_PAUSE_CONTINUE 2
#define SERVICE_ACCEPT_POWEREVENT 64
#define SERVICE_ACCEPT_SESSIONCHANGE 128
#define SERVICE_ACCEPT_SHUTDOWN 4
#define SERVICE_ACCEPT_STOP 1
#define SERVICE_ACTIVE 1
#define SERVICE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SERVICE_QUERY_CONFIG|SERVICE_CHANGE_CONFIG|SERVICE_QUERY_STATUS|SERVICE_ENUMERATE_DEPENDENTS|SERVICE_START|SERVICE_STOP|SERVICE_PAUSE_CONTINUE|SERVICE_INTERROGATE|SERVICE_USER_DEFINED_CONTROL)
#define SERVICE_CHANGE_CONFIG 2
#define SERVICE_CONFIG_DESCRIPTION 1
#define SERVICE_CONFIG_FAILURE_ACTIONS 2
#define SERVICE_CONTINUE_PENDING 5
#define SERVICE_CONTROL_CONTINUE 3
#define SERVICE_CONTROL_DEVICEEVENT 11
#define SERVICE_CONTROL_HARDWAREPROFILECHANGE 12
#define SERVICE_CONTROL_INTERROGATE 4
#define SERVICE_CONTROL_NETBINDADD 7
#define SERVICE_CONTROL_NETBINDDISABLE 10
#define SERVICE_CONTROL_NETBINDENABLE 9
#define SERVICE_CONTROL_NETBINDREMOVE 8
#define SERVICE_CONTROL_PARAMCHANGE 6
#define SERVICE_CONTROL_PAUSE 2
#define SERVICE_CONTROL_POWEREVENT 13
#define SERVICE_CONTROL_SESSIONCHANGE 14
#define SERVICE_CONTROL_SHUTDOWN 5
#define SERVICE_CONTROL_STOP 1
#define SERVICE_ENUMERATE_DEPENDENTS 8
#define SERVICE_INACTIVE 2
#define SERVICE_INTERROGATE 128
#define SERVICE_NO_CHANGE 0xffffffff
#define SERVICE_PAUSE_CONTINUE 64
#define SERVICE_PAUSE_PENDING 6
#define SERVICE_PAUSED 7
#define SERVICE_QUERY_CONFIG 1
#define SERVICE_QUERY_STATUS 4
#define SERVICE_RUNNING 4
#define SERVICE_RUNS_IN_SYSTEM_PROCESS 1
#define SERVICE_START 16
#define SERVICE_START_PENDING 2
#define SERVICE_STATE_ALL 3
#define SERVICE_STOP 32
#define SERVICE_STOP_PENDING 3
#define SERVICE_STOPPED 1
#define SERVICE_USER_DEFINED_CONTROL 256
#define SERVICES_ACTIVE_DATABASE SERVICES_ACTIVE_DATABASEW
#define SERVICES_ACTIVE_DATABASEA "ServicesActive"
#define SERVICES_ACTIVE_DATABASEW L"ServicesActive"
#define SERVICES_FAILED_DATABASE SERVICES_FAILED_DATABASEW
#define SERVICES_FAILED_DATABASEA "ServicesFailed"
#define SERVICES_FAILED_DATABASEW L"ServicesFailed"

/* ==================================================================
 * base types -- fundamental Windows type definitions
 * CE-specific types are marked; verify sizes for your platform
 * ================================================================ */

/* SC_HANDLE
 * source: win32/common/windows-data-types.md */
typedef HANDLE SC_HANDLE;

/* SC_LOCK
 * source: win32/common/windows-data-types.md */
typedef LPVOID SC_LOCK;

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SERVICE_STATUS_HANDLE  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE SERVICE_STATUS_HANDLE;

#endif /* _WINSVC_ */
