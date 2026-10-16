/* Halether.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 21 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _HALETHER_
#define _HALETHER_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* EDBG_ADDR  [struct; ce-only] */
typedef struct _EDBG_ADDR{
 DWORD dwIP;
 USHORT wMAC[3];
 USHORT wPort;
} EDBG_ADDR;
typedef EDBG_ADDR *PEDBG_ADDR, *LPEDBG_ADDR;

/* EDBG_ADAPTER  [struct; ce-only] */
typedef struct { 
EDBG_ADDR Addr; 
DWORD SysIntrVal; 
DWORD DHCPLeaseTime; 
DWORD EdbgFlags;} 
EDBG_ADAPTER;
typedef EDBG_ADAPTER *PEDBG_ADAPTER, *LPEDBG_ADAPTER;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 3.0..399 */

/* EdbgInit  [function; ce-only; CE 3.0..399] */
BOOL EdbgInit(void);

/* EdbgOutputDebugString  [function; ce-only; CE 3.0..399] */
void EdbgOutputDebugString( 
const char * fmt, 
const char valist... );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 3.0..399, 5.0..599 */

/* OEMEthDisableInts  [function; ce-only; CE 3.0..399, 5.0..599; Hal.lib] */
void OEMEthDisableInts (void);

/* OEMEthEnableInts  [function; ce-only; CE 3.0..399, 5.0..599; Hal.lib] */
void OEMEthEnableInts (void);

/* OEMEthInit  [function; ce-only; CE 3.0..399, 5.0..599; Hal.lib] */
BOOL OEMEthInit(EDBG_ADAPTER* pAdapter );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* OEMEthGetSecs  [function; ce-only; CE 3.0..399, 5.0..699; Hal.lib, hal.lib] */
DWORD OEMEthGetSecs (void);

/* OEMEthISR  [function; ce-only; CE 3.0..399, 5.0..699; Hal.lib, hal.lib] */
void OEMEthISR (void);

/* OEMEthQueryClientInfo  [function; ce-only; CE 3.0..399, 5.0..699; Hal.lib, hal.lib] */
BOOL OEMEthQueryClientInfo(
 UCHAR Id, 
 EDBG_ADDR* pPeerAddr, 
 PUCHAR pWindowSize, 
 PUCHAR* ppBufferPool 
);

/* OEMEthSendFrame  [function; ce-only; CE 3.0..399, 5.0..699; Hal.lib, hal.lib] */
BOOL OEMEthSendFrame( 
 BYTE* pData, 
 DWORD dwLength 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x600)) /* CE 4.0..599 */

/* CallEdbgDeregisterClient  [function; ce-only; CE 4.0..599; Hal.lib] */
BOOL CallEdbgDeregisterClient(
 UCHAR Id
);

/* CallEdbgRecv  [function; ce-only; CE 4.0..599; Hal.lib] */
BOOL CallEdbgRecv(
 UCHAR Id,
 UCHAR* pRecvBuf,
 DWORD* pdwLen,
 DWORD Timeout
);

/* CallEdbgRegisterClient  [function; ce-only; CE 4.0..599; Hal.lib] */
BOOL CallEdbgRegisterClient(
 UCHAR* pId,
 char* ServiceName,
 UCHAR Flags,
 UCHAR WindowSize,
 UCHAR* pBufferPool
);

/* CallEdbgSend  [function; ce-only; CE 4.0..599; Hal.lib] */
BOOL CallEdbgSend(
 UCHAR Id,
 UCHAR* pUserData,
 DWORD dwUserDataLen
);

/* CallEdbgSetDebug  [function; ce-only; CE 4.0..599; Hal.lib] */
BOOL CallEdbgSetDebug(
 DWORD ZoneMask
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* EbootEtherReadData  [function; ce-only; CE 5.0..699; Hal.lib, hal.lib] */
BOOL EbootEtherReadData(
 DWORD cbData,
 LPBYTE pbData
);

/* EbootGetDHCPAddr  [function; ce-only; CE 5.0..699; Hal.lib, hal.lib] */
BOOL EbootGetDHCPAddr(
 EDBG_ADDR* pEdbgAddr,
 DWORD* pdwSubnetMask,
 EDBG_ADDR* pdwDHCPLeaseTime
);

/* EbootInitEtherTransport  [function; ce-only; CE 5.0..699; Hal.lib, hal.lib] */
BOOL EbootInitEtherTransport(
 EDBG_ADDR* pEdbgAddr,
 LPDWORD pdwSubnetMask,
 BOOL* pfJumping,
 DWORD* pdwDHCPLeaseTime,
 UCHAR VersionMajor,
 UCHAR VersionMinor,
 char* szPlatformString,
 char* szDeviceName,
 UCHAR CPUId,
 DWORD dwBootFlags
);
#endif /* _WIN32_WCE */

#endif /* _HALETHER_ */
