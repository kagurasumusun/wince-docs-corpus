/* Ethdbg.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 10 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ETHDBG_
#define _ETHDBG_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define EDBG_BOOTLOAD_FORCE_DOWNLOAD 0x0001
#define EDBG_CURRENT_BOOTME_VERSION 2

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* EDBG_BOOTME_DATA  [struct; ce-only] */
typedef struct _EDBG_BOOTME_DATA { 
UCHAR VersionMajor; 
UCHAR VersionMinor; 
USHORT MACAddr[3]; 
DWORD IPAddr; 
UCHAR PlatformId[EDBG_MAX_DEV_NAMELEN+1]; 
UCHAR DeviceName[EDBG_MAX_DEV_NAMELEN+1]; 
UCHAR CPUId; 
UCHAR uBootmeVer; 
DWORD dwBootFlags; 
USHORT wDownloadPort; 
USHORT wSvcPort; 
} EDBG_BOOTME_DATA, *PEDBG_BOOTME_DATA;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 3.0..399 */

/* EDBG_BOOT_CALLBACK_FUNC  [function; ce-only; CE 3.0..399] */
void EDBG_BOOT_CALLBACK_FUNC( 
PVOID pParam, 
PEDBG_BOOTME_DATA pBootmeData );

/* EdbgDeregisterClient  [function; ce-only; CE 3.0..399; Edbg.dll, Ethdbg.dll, Ethdbg.lib] */
BOOL EdbgDeregisterClient( 
UCHAR Id );

/* EdbgGetDeviceInfo  [function; ce-only; CE 3.0..399; Edbg.dll] */
BOOL EdbgGetDeviceInfo( 
char *DeviceName, 
UCHAR Id, 
EDBG_BOOTME_DATA *pBootMeData );

/* EdbgRecv  [function; ce-only; CE 3.0..399; Edbg.dll, Ethdbg.lib] */
BOOL EdbgRecv( 
UCHAR Id, 
UCHAR *pRecvBuf, 
DWORD *pdwLen, 
DWORD Timeout );

/* EdbgRegisterClient  [function; ce-only; CE 3.0..399; Edbg.dll, Ethdbg.lib] */
BOOL EdbgRegisterClient( 
UCHAR *pId, 
char *ServiceName, 
UCHAR Flags, 
char *EshellServer, 
char *DeviceName );

/* EdbgResetDevice  [function; ce-only; CE 3.0..399] */
BOOL EdbgResetDevice( 
CHAR *DeviceName, 
UCHAR Id, 
BOOL CleanBoot );

/* EdbgSend  [function; ce-only; CE 3.0..399; Edbg.dll, Ethdbg.lib] */
BOOL EdbgSend( 
UCHAR Id, 
UCHAR *pUserData , 
DWORD dwUserDataLen );
#endif /* _WIN32_WCE */

#endif /* _ETHDBG_ */
