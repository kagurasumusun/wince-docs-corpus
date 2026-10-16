/* Winreg.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 43 constants, 19 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINREG_
#define _WINREG_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define HKEY_CLASSES_ROOT ((HKEY)0x80000000)
/* NOT SUPPORTED per learn/windows-ce-5.0: LONG NKRegOpenKeyEx(HKEYhKey,LPCWSTRlpSubKey, DWORDulOptions, REGSAMsamDesired,PHKEYphkResult); Parameters hKey [in] Handle to an open key or any of the following predefined reserved handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does not support the foll [corpus/learn/windows-ce-5.0/ms904870(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: Syntax LONG NKRegOpenKeyEx( HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult ); Parameters hKey [in] Handle to an open key or any of the following predefined reserved handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows Embedded CE  [corpus/learn/windows-embedded-ce-6.0/ee478238(v=winembedded.60).html] */
#define HKEY_CURRENT_CONFIG ((HKEY)0x80000005)
#define HKEY_CURRENT_USER ((HKEY)0x80000001)
/* NOT SUPPORTED per learn/windows-ce-5.0: LONG NKRegOpenKeyEx(HKEYhKey,LPCWSTRlpSubKey, DWORDulOptions, REGSAMsamDesired,PHKEYphkResult); Parameters hKey [in] Handle to an open key or any of the following predefined reserved handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does not support the foll [corpus/learn/windows-ce-5.0/ms904870(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: Syntax LONG NKRegOpenKeyEx( HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult ); Parameters hKey [in] Handle to an open key or any of the following predefined reserved handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows Embedded CE  [corpus/learn/windows-embedded-ce-6.0/ee478238(v=winembedded.60).html] */
#define HKEY_DYN_DATA ((HKEY)0x80000006)
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)
/* NOT SUPPORTED per learn/windows-ce-5.0: LONG NKRegOpenKeyEx(HKEYhKey,LPCWSTRlpSubKey, DWORDulOptions, REGSAMsamDesired,PHKEYphkResult); Parameters hKey [in] Handle to an open key or any of the following predefined reserved handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows CE does not support the foll [corpus/learn/windows-ce-5.0/ms904870(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: Syntax LONG NKRegOpenKeyEx( HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult ); Parameters hKey [in] Handle to an open key or any of the following predefined reserved handle values: HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS Windows Embedded CE  [corpus/learn/windows-embedded-ce-6.0/ee478238(v=winembedded.60).html] */
#define HKEY_PERFORMANCE_DATA ((HKEY)0x80000004)
#define HKEY_USERS ((HKEY)0x80000003)
#define REG_BINARY 3
#define REG_CREATED_NEW_KEY 0x00000001L
#define REG_DWORD 4
#define REG_DWORD_BIG_ENDIAN 5
#define REG_DWORD_LITTLE_ENDIAN 4
#define REG_EXPAND_SZ 2
#define REG_FULL_RESOURCE_DESCRIPTOR 9
#define REG_LINK 6
#define REG_MULTI_SZ 7
#define REG_NONE 0
#define REG_NOTIFY_CHANGE_ATTRIBUTES 0x00000002L
#define REG_NOTIFY_CHANGE_LAST_SET 0x00000004L
#define REG_NOTIFY_CHANGE_NAME 0x00000001L
#define REG_NOTIFY_CHANGE_SECURITY 0x00000008L
#define REG_NOTIFY_THREAD_AGNOSTIC 0x10000000L
#define REG_OPENED_EXISTING_KEY 0x00000002L
#define REG_OPTION_BACKUP_RESTORE 0x00000004L
#define REG_OPTION_CREATE_LINK 0x00000002L
#define REG_OPTION_NON_VOLATILE 0x00000000L
#define REG_OPTION_VOLATILE 0x00000001L
#define REG_PINFLAG_B_MANY 0x4
#define REG_PINFLAG_B_OUTPUT 0x8
#define REG_PINFLAG_B_RENDERER 0x2
#define REG_PINFLAG_B_ZERO 0x1
#define REG_QWORD 11
#define REG_QWORD_LITTLE_ENDIAN 11
#define REG_RESOURCE_LIST 8
#define REG_RESOURCE_REQUIREMENTS_LIST 10
#define REG_SZ 1
#define SC_ACTION_NONE 0
#define SC_ACTION_REBOOT 2
#define SC_ACTION_RESTART 1
#define SC_ACTION_RUN_COMMAND 3
#define SC_STATUS_PROCESS_INFO 0
#define TokenPrimary 1
#define TokenUser 1

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* REG_NOTIFY_INFORMATION  [struct; ce-only] */
typedef struct _REG_NOTIFY_INFORMATION {
 DWORD NextEntryOffset; 
 DWORD Action; 
 DWORD RegNameLength; 
 WCHAR RegName[1]; 
} REG_NOTIFY_INFORMATION, *PREG_NOTIFY_INFORMATION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* RegCopyFile  [function; ce-only; unified-kb; unified-kb] */
BOOL RegCopyFile ( 
LPCWSTR lpszFile );

/* RegRestoreFile  [function; ce-only; unified-kb; unified-kb] */
BOOL RegRestoreFile ( 
LPCWSTR lpszFile );

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* RegCloseKey  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, Fsreg.lib, fsreg.lib, Nkstub.lib] */
LONG RegCloseKey( 
 HKEY hKey 
);

/* RegDeleteKey  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsreg.lib, fsreg.lib; A/W RegDeleteKeyA,RegDeleteKeyW (CE is W-side)] */
LONG RegDeleteKey( 
 HKEY hKey, 
 LPCWSTR lpSubKey 
);

/* RegDeleteValue  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsreg.lib, fsreg.lib; A/W RegDeleteValueA,RegDeleteValueW (CE is W-side)] */
LONG RegDeleteValue( 
 HKEY hKey, 
 LPCWSTR lpValueName 
);

/* RegEnumKeyEx  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsreg.lib, fsreg.lib; A/W RegEnumKeyExA,RegEnumKeyExW (CE is W-side)] */
LONG RegEnumKeyEx(
 HKEY hKey, 
 DWORD dwIndex, 
 LPWSTR lpName, 
 LPDWORD lpcName, 
 LPDWORD lpReserved, 
 LPWSTR lpClass, 
 LPDWORD lpcbClass, 
 PFILETIME lpftLastWriteTime 
);

/* RegEnumValue  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsreg.lib, fsreg.lib; A/W RegEnumValueA,RegEnumValueW (CE is W-side)] */
LONG RegEnumValue( 
 HKEY hKey, 
 DWORD dwIndex, 
 LPWSTR lpValueName, 
 LPDWORD lpcchValueName, 
 LPDWORD lpReserved, 
 LPDWORD lpType, 
 LPBYTE lpData, 
 LPDWORD lpcbData 
);

/* RegFlushKey  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, Fsreg.lib, fsreg.lib, Nkstub.lib] */
LONG RegFlushKey( 
 HKEY hKey 
);

/* RegQueryValueEx  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, Fsreg.lib, fsreg.lib, Nkstub.lib; A/W RegQueryValueExA,RegQueryValueExW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
LONG RegQueryValueEx( 
 HKEY hKey, 
 LPCWSTR lpValueName, 
 LPDWORD lpReserved, 
 LPDWORD lpType, 
 LPBYTE lpData, 
 LPDWORD lpcbData 
);

/* RegSetValueEx  [function; shared; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Fsreg.lib, fsreg.lib; A/W RegSetValueExA,RegSetValueExW (CE is W-side)] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows Embedded CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
LONG RegSetValueEx(
 HKEY hKey,
 LPCWSTR lpValueName,
 DWORD Reserved,
 DWORD dwType,
 const BYTE* lpData,
 DWORD cbData
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* RegNotifyChangeKeyValue  [function; shared; CE 5.0..599; Coredll.lib] */
LONG RegNotifyChangeKeyValue( 
 HKEY hKey, 
 BOOL bWatchSubtree, 
 DWORD dwNotifyFilter, 
 HANDLE hEvent, 
 BOOL fAsynchronous 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CeFindCloseRegChange  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeFindCloseRegChange (
 HANDLE hChangeHandle 
);

/* CeFindFirstRegChange  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HANDLE CeFindFirstRegChange (
 HKEY hKey,
 BOOL bWatchSubtree,
 DWORD dwNotifyFilter
);

/* CeFindNextRegChange  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeFindNextRegChange (
 HANDLE hChangeHandle 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* CeRegGetNotificationInfo  [function; ce-only; CE 6.0..699; coredll.lib] */
LONG CeRegGetNotificationInfo(
 __in HANDLE hChangeHandle,
 __in DWORD dwFlags, 
 __inout_bcount(nBufferLength) __opt LPVOID lpBuffer, 
 __in DWORD nBufferLength, 
 __out LPDWORD lpBytesReturned, 
 __out LPDWORD lpBytesAvailable );

/* CeRegTestSetValueW  [function; ce-only; CE 6.0..699; coredll.lib] */
LONG CeRegTestSetValueW(
 __in HKEY hKey, 
 __in LPCWSTR lpValueName, 
 DWORD dwType, 
 __in_bcount(cbOldData) __opt CONST BYTE* lpOldData, 
 DWORD cbOldData,
 __in_bcount(cbNewData) __opt CONST BYTE* lpNewData, 
 DWORD cbNewData,
 DWORD dwFlags
 );
#endif /* _WIN32_WCE */

#endif /* _WINREG_ */
