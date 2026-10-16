/* Rapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 12 constants, 58 declarations, 2 outlines, 0 base types, 0 extra macros, 4 extra decls
 */
#ifndef _RAPI_
#define _RAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define NID_EXTERNAL_PEN 0x08
#define NID_EXTERNAL_TOUCH 0x02
#define NID_INTEGRATED_PEN 0x04
#define NID_INTEGRATED_TOUCH 0x01
#define NID_MULTI_INPUT 0x40
#define NID_READY 0x80
#define RAPI_CONNECTION_IR 1
#define RAPI_CONNECTION_NETWORK 3
#define RAPI_CONNECTION_SERIAL 2
#define RAPI_CONNECTION_USB 0
#define RAPI_DEVICE_CONNECTED 1
#define RAPI_DEVICE_DISCONNECTED 0

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* PEG_USER_NOTIFICATION  [struct; ce-only] */

/* RAPIEXT  [typedef; ce-only; rapi.lib] */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213)) /* CE 1.0..199, 2.11..2.12 */

/* RapiFreeBuffer  [function; ce-only; CE 1.0..199, 2.11..2.12] */
HRESULT RapiFreeBuffer( LPVOID Buffer );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699 */

/* CeCheckPassword  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeCheckPassword( 
 LPWSTR lpszPassword 
);

/* CeCloseHandle  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeCloseHandle( 
 HANDLE hObject 
);

/* CeCopyFile  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeCopyFile(
 LPCWSTR lpExistingFileName, 
 LPCWSTR lpNewFileName, 
 BOOL bFailIfExists 
);

/* CeCreateDirectory  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeCreateDirectory(
 LPCWSTR lpPathName,
 LPSECURITY_ATTRIBUTES lpSecurityAttributes
);

/* CeCreateFile  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
HANDLE CeCreateFile (
 LPCWSTR lpFileName, 
 DWORD dwDesiredAccess, 
 DWORD dwShareMode, 
 LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
 DWORD dwCreationDisposition, 
 DWORD dwFlagsAndAttributes, 
 HANDLE hTemplateFile 
);

/* CeCreateProcess  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeCreateProcess(
 LPCWSTR lpApplicationName, 
 LPCWSTR lpCommandLine, 
 LPSECURITY_ATTRIBUTES lpProcessAttributes, 
 LPSECURITY_ATTRIBUTES lpThreadAttributes, 
 BOOL bInheritHandles, 
 DWORD dwCreationFlags, 
 LPVOID lpEnvironment, 
 LPWSTR lpCurrentDirectory, 
 LPSTARTUPINFO lpStartupInfo, 
 LPPROCESS_INFORMATION lpProcessInformation 
);

/* CeDeleteFile  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeDeleteFile(
 LPCWSTR lpFileName 
);

/* CeFindClose  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeFindClose( 
 HANDLE hFindFile 
);

/* CeGetDesktopDeviceCaps  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
INT CeGetDesktopDeviceCaps(
 INT nIndex 
);

/* CeGetFileAttributes  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
DWORD CeGetFileAttributes(
 LPCWSTR lpFileName 
);

/* CeGetFileSize  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
DWORD CeGetFileSize( 
 HANDLE hFile, 
 LPDWORD lpFileSizeHigh 
);

/* CeGetFileTime  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeGetFileTime( 
 HANDLE hFile, 
 LPFILETIME lpCreationTime, 
 LPFILETIME lpLastAccessTime, 
 LPFILETIME lpLastWriteTime 
);

/* CeGetLastError  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
DWORD CeGetLastError( void );

/* CeGetSpecialFolderPath  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
DWORD CeGetSpecialFolderPath( 
 Int nFolder, 
 DWORD nBufferLength, 
 LPWSTR lpBuffer 
);

/* CeGetStoreInformation  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeGetStoreInformation( 
 LPSTORE_INFORMATION lpsi 
);

/* CeGetSystemInfo  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
VOID CeGetSystemInfo (
 LPSYSTEM_INFO lpSystemInfo 
);

/* CeGetTempPath  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
DWORD CeGetTempPath(
 DWORD nBufferLength,
 LPWSTR lpBuffer 
);

/* CeGetWindow  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
HWND CeGetWindow( 
 HWND hWnd, 
 UINT uCmd 
);

/* CeMoveFile  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeMoveFile(
 LPCWSTR lpExistingFileName, 
 LPCWSTR lpNewFileName 
);

/* CeRapiGetError  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
HRESULT CeRapiGetError(void);

/* CeRapiInit  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
HRESULT CeRapiInit ();

/* CeRapiUninit  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
HRESULT CeRapiUninit ();

/* CeReadFile  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeReadFile ( 
 HANDLE hFile, 
 LPVOID lpBuffer, 
 DWORD nNumberOfBytesToRead, 
 LPDWORD lpNumberOfBytesRead, 
 LPOVERLAPPED lpOverlapped 
);

/* CeRegCloseKey  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
LONG CeRegCloseKey(
 HKEY hKey 
);

/* CeRegDeleteKey  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
LONG CeRegDeleteKey( 
 HKEY hKey, 
 LPCWSTR lpszSubKey 
);

/* CeRegDeleteValue  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
LONG CeRegDeleteValue( 
 HKEY hKey, 
 LPCWSTR lpszValueName 
);

/* CeRegEnumKeyEx  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
LONG CeRegEnumKeyEx(
 HKEY hKey, 
 DWORD dwIndex, 
 LPWSTR lpName, 
 LPDWORD lpcbName, 
 LPDWORD lpReserved, 
 LPWSTR lpClass, 
 LPDWORD lpcbClass, 
 PFILETIME lpftLastWriteTime 
);

/* CeRegEnumValue  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
LONG CeRegEnumValue( 
 HKEY hKey, 
 DWORD dwIndex, 
 LPWSTR lpszValueName, 
 LPDWORD lpcbValueName, 
 LPDWORD lpReserved, 
 LPDWORD lpType, 
 LPBYTE lpData, 
 LPDWORD lpcbData 
);

/* CeRegQueryInfoKey  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
LONG CeRegQueryInfoKey( 
 HKEY hKey, 
 LPWSTR lpClass, 
 LPDWORD lpcbClass, 
 LPDWORD lpReserved, 
 LPDWORD lpcSubKeys, 
 LPDWORD lpcbMaxSubKeyLen, 
 LPDWORD lpcbMaxClassLen, 
 LPDWORD lpcValues, 
 LPDWORD lpcbMaxValueNameLen, 
 LPDWORD lpcbMaxValueLen, 
 LPDWORD lpcbSecurityDescriptor, 
 PFILETIME lpftLastWriteTime 
);

/* CeRegQueryValueEx  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
LONG CeRegQueryValueEx( 
 HKEY hKey, 
 LPCWSTR lpValueName, 
 LPDWORD lpReserved, 
 LPDWORD lpType, 
 LPBYTE lpData, 
 LPDWORD lpcbData 
);

/* CeRegSetValueEx  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
/* Windows CE supports only the Unicode version of this function. */
LONG CeRegSetValueEx (
 HKEY hKey,
 LPCWSTR lpValueName,
 DWORD Reserved,
 DWORD dwType,
 LPBYTE lpData,
 DWORD cbData
);

/* CeRemoveDirectory  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeRemoveDirectory(
 LPCWSTR lpPathName 
);

/* CeSetEndOfFile  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeSetEndOfFile( 
 HANDLE hFile 
);

/* CeSetFileAttributes  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeSetFileAttributes(
 LPCWSTR lpFileName, 
 DWORD dwFileAttributes 
);

/* CeSetFilePointer  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
DWORD CeSetFilePointer( 
 HANDLE hFile, 
 LONG lDistanceToMove, 
 PLONG lpDistanceToMoveHigh, 
 DWORD dwMoveMethod 
);

/* CeSetFileTime  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeSetFileTime (
 HANDLE hFile,
 LPFILETIME lpCreationTime,
 LPFILETIME lpLastAccessTime,
 LPFILETIME lpLastWriteTime
);

/* CeSHCreateShortcut  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeSHCreateShortcut(
 LPWSTR lpszShortcut, 
 LPWSTR lpszTarget 
);

/* CeSHGetShortcutTarget  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeSHGetShortcutTarget(
 LPWSTR lpszShortcut, 
 LPWSTR lpszTarget, 
 Int cbMax 
);

/* CeWriteFile  [function; ce-only; CE 1.0..199, 2.11..2.12, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeWriteFile( 
 HANDLE hFile, 
 LPCVOID lpBuffer, 
 DWORD nNumberOfBytesToWrite, 
 LPDWORD lpNumberOfBytesWritten, 
 LPOVERLAPPED lpOverlapped 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 3.0..399, 5.0..699 */

/* CeGetClassName  [function; ce-only; CE 1.0..199, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
int CeGetClassName( 
 HWND hWnd, 
 LPWSTR lpClassName, 
 Int nMaxCount 
);

/* CeGetWindowLong  [function; ce-only; CE 1.0..199, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
LONG CeGetWindowLong(
 HWND hWnd, 
 Int nIndex 
);

/* CeGetWindowText  [function; ce-only; CE 1.0..199, 3.0..399, 5.0..699; Rapi.lib, rapi.lib] */
int CeGetWindowText (
 HWND hWnd, 
 LPWSTR lpString, 
 int nMaxCount 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 5.0..699 */

/* CeGetSystemMetrics  [function; ce-only; CE 1.0..199, 5.0..699; Rapi.lib, rapi.lib] */
INT CeGetSystemMetrics(
 INT nIndex
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CeQueryInstructionSet  [function; ce-only; CE 5.0..699; Rapi.lib, rapi.lib] */
BOOL CeQueryInstructionSet(
 DWORD dwInstructionSet,
 LPDWORD lpdwCurrentInstructionSet
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* CeGetDiskFreeSpaceEx  [function; ce-only; CE 6.0..699; rapi.lib] */
int CeGetDiskFreeSpaceEx( 
 LPCTSTR _lpDirectoryName, 
 PULARGE_INTEGER lpFreeBytesAvailable, 
 PULARGE_INTEGER lpTotalNumberOfBytes, 
 PULARGE_INTEGER lpTotalNumberOfFreeBytes
);

/* CeSyncStart  [function; ce-only; CE 6.0..699; rapi.lib] */
HRESULT CeSyncStart(
 LPCWSTR szCommand
);

/* CeSyncStop  [function; ce-only; CE 6.0..699; rapi.lib] */
HRESULT CeSyncStop();
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
DWORD PegGetLastError(void);

#endif /* _RAPI_ */
