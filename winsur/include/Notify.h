/* Notify.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 32 constants, 31 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NOTIFY_
#define _NOTIFY_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define APP_RUN_AFTER_EXTENDED_EVENT L"AppRunAfterExtendedEvent"
#define APP_RUN_AFTER_RESTORE L"AppRunAfterRestore"
#define APP_RUN_AFTER_SYNC L"AppRunAfterSync"
#define APP_RUN_AFTER_TZ_CHANGE L"AppRunAfterTzChange"
#define APP_RUN_AFTER_WAKEUP L"AppRunAfterWakeup"
#define APP_RUN_AT_AC_POWER_OFF L"AppRunAtAcPowerOff"
#define APP_RUN_AT_AC_POWER_ON L"AppRunAtAcPowerOn"
#define APP_RUN_AT_DEVICE_CHANGE L"AppRunDeviceChange"
#define APP_RUN_AT_IR_DISCOVERY L"AppRunAtIrDiscovery"
#define APP_RUN_AT_NET_CONNECT L"AppRunAtNetConnect"
#define APP_RUN_AT_NET_DISCONNECT L"AppRunAtNetDisconnect"
#define APP_RUN_AT_RS232_DETECT L"AppRunAtRs232Detect"
#define NOTIFICATION_EVENT_DEVICE_CHANGE 7
#define NOTIFICATION_EVENT_IR_DISCOVERED 8
#define NOTIFICATION_EVENT_MACHINE_NAME_CHANGE 13
#define NOTIFICATION_EVENT_NET_CONNECT 5
#define NOTIFICATION_EVENT_NET_DISCONNECT 6
#define NOTIFICATION_EVENT_NONE 0
#define NOTIFICATION_EVENT_OFF_AC_POWER 4
#define NOTIFICATION_EVENT_ON_AC_POWER 3
#define NOTIFICATION_EVENT_RESTORE_END 10
#define NOTIFICATION_EVENT_RS232_DETECTED 9
#define NOTIFICATION_EVENT_SYNC_END 2
#define NOTIFICATION_EVENT_TIME_CHANGE 1
#define NOTIFICATION_EVENT_TZ_CHANGE 12
#define NOTIFICATION_EVENT_WAKEUP 11
#define PUN_DIALOG 4
#define PUN_LED 1
#define PUN_PRIVATE 32
#define PUN_REPEAT 16
#define PUN_SOUND 8
#define PUN_VIBRATE 2

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CE_NOTIFICATION_TRIGGER  [struct; ce-only] */
typedef struct UserNotificationTrigger { DWORD dwSize; DWORD dwType; DWORD dwEvent; WCHAR* lpszApplication; WCHAR* lpszArguments; SYSTEMTIME stStartTime; SYSTEMTIME stEndTime;} CE_NOTIFICATION_TRIGGER, *PCE_NOTIFICATION_TRIGGER;

/* CE_USER_NOTIFICATION  [struct; ce-only] */
typedef struct UserNotificationType {
 DWORD ActionFlags;
 TCHAR* pwszDialogTitle;
 TCHAR* pwszDialogText;
 TCHAR* pwszSound;
 DWORD nMaxSound;
 DWORD dwReserved;
} CE_USER_NOTIFICATION, *PCE_USER_NOTIFICATION;

/* CE_NOTIFICATION_INFO_HEADER  [struct; ce-only] */
typedef struct UserNotificationInfoHeader {
 HANDLE hNotification;
 DWORD dwStatus;
 CE_NOTIFICATION_TRIGGER* pcent;
 CE_USER_NOTIFICATION* pceun;
} CE_NOTIFICATION_INFO_HEADER, *PCE_NOTIFICATION_INFO_HEADER;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* CeClearUserNotification  [function; ce-only; unified-kb; unified-kb] */
BOOL CeClearUserNotification( 
 HANDLE hNotification 
);

/* CeSetUserNotification  [function; ce-only; unified-kb; unified-kb] */
HANDLE CeSetUserNotification( 
 HANDLE hNotification, 
 TCHAR* pwszAppName, 
 SYSTEMTIME* lpTime, 
 PCE_USER_NOTIFICATION lpUserNotification 
);

/* CeSetUserNotificationEx  [function; ce-only; unified-kb; unified-kb] */
HANDLE CeSetUserNotificationEx( 
 HANDLE hNotification, 
 CE_NOTIFICATION_TRIGGER* pcnt, 
 CE_USER_NOTIFICATION* pceun 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699 */

/* CeGetUserNotificationPreferences  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Notify.lib, notify.lib] */
BOOL CeGetUserNotificationPreferences(
 HWND hWndParent, 
 PCE_USER_NOTIFICATION lpNotification 
);

/* CeHandleAppNotifications  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Notify.lib, notify.lib] */
BOOL CeHandleAppNotifications(
 TCHAR* pwszAppName 
);

/* CeRunAppAtEvent  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Notify.lib, notify.lib] */
BOOL CeRunAppAtEvent(
 TCHAR* pwszAppName, 
 LONG lWhichEvent 
);

/* CeRunAppAtTime  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Notify.lib, notify.lib] */
BOOL CeRunAppAtTime(
 TCHAR* pwszAppName, 
 SYSTEMTIME* lpTime 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* CeGetUserNotification  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Notify.lib, notify.lib] */
BOOL CeGetUserNotification(
 HANDLE hNotification, 
 DWORD cBufferSize, 
 LPDWORD pcBytesNeeded, 
 LPBYTE pBuffer 
);

/* CeGetUserNotificationHandles  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Notify.lib, notify.lib] */
BOOL CeGetUserNotificationHandles(
 HANDLE* rghNotifications, 
 DWORD cHandles, 
 LPDWORD pcHandlesNeeded 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* CeEventHasOccurred  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL CeEventHasOccurred(
 LONG lWhichEvent,
 TCHAR* pwszEndOfCommandLine
);
#endif /* _WIN32_WCE */

#endif /* _NOTIFY_ */
