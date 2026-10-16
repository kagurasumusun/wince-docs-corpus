/* bt_api.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 12 constants, 67 declarations, 0 outlines, 0 base types, 0 extra macros, 3 extra decls
 */
#ifndef _BT_API_
#define _BT_API_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ACTIVE 0x00
#define BT_AVDTP_STATE_DISCONNECTED 0
#define BT_AVDTP_STATE_STREAMING 2
#define BT_AVDTP_STATE_SUSPENDED 1
#define BTE_CLASS_CONNECTIONS 1
#define BTE_CLASS_DEVICE 4
#define BTE_CLASS_PAIRING 2
#define BTE_CLASS_STACK 8
#define RFCOMM_PORT_FLAGS_AUTHENTICATE 0x00000004
#define RFCOMM_PORT_FLAGS_ENCRYPT 0x00000008
#define RFCOMM_PORT_FLAGS_KEEP_DCD 0x00000002
#define RFCOMM_PORT_FLAGS_REMOTE_DCB 0x00000001

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BT_DISCONNECT_EVENT  [struct; ce-only] */
typedef struct { 
 DWORD dwSize;
 USHORT hConnection;
 UCHAR ucReason;
} BT_DISCONNECT_EVENT, *PBT_DISCONNECT_EVENT;

/* BTEVENT  [struct; ce-only] */
typedef struct _BTEVENT {
 DWORD dwEventId;
 DWORD dwReserved;
 BYTE baEventData[64];
} BTEVENT, *PBTEVENT;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* BthCancelInquiry  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthCancelInquiry(void);

/* BthClearInquiryFilter  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthClearInquiryFilter(void);

/* BthCloseConnection  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthCloseConnection(
 unsigned short handle
);

/* BthGetBasebandHandles  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthGetBasebandHandles(
 int cHandles,
 unsigned short* pHandles,
 int* pcHandlesReturned
);

/* BthGetHardwareStatus  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthGetHardwareStatus(
 int* pistatus
);

/* BthNsLookupServiceEnd  [function; ce-only; CE 4.0..699; Btdrt.lib] */
INT BthNsLookupServiceEnd(
 HANDLE hLookup
);

/* BthReadAuthenticationEnable  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthReadAuthenticationEnable(
 unsigned char* pae
);

/* BthReadCOD  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthReadCOD(
 unsigned int* pcod
);

/* BthReadLocalVersion  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthReadLocalVersion(
 unsigned char* phci_version,
 unsigned short* phci_revision,
 unsigned char* plmp_version,
 unsigned short* plmp_subversion,
 unsigned short* pmanufacturer,
 unsigned char* plmp_features
);

/* BthReadPageTimeout  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthReadPageTimeout(
 unsigned short* ptimeout
);

/* BthReadScanEnableMask  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthReadScanEnableMask(
 unsigned char* pmask
);

/* BthSetSecurityUI  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthSetSecurityUI(
 HANDLE hEvent,
 DWORD dwStoreTimeout,
 DWORD dwProcTimeout
);

/* BthTerminateIdleConnections  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthTerminateIdleConnections(void);

/* BthWriteAuthenticationEnable  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthWriteAuthenticationEnable(
 unsigned char ae
);

/* BthWriteCOD  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthWriteCOD(
 unsigned int cod
);

/* BthWritePageTimeout  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthWritePageTimeout(
 unsigned short timeout
);

/* BthWriteScanEnableMask  [function; ce-only; CE 4.0..699; Btdrt.lib] */
int BthWriteScanEnableMask(
 unsigned char mask
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* BthAcceptSCOConnections  [function; ce-only; CE 5.0..699; Btdrt.lib] */
int BthAcceptSCOConnections ( BOOL fAccept);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* BthActivatePAN  [function; ce-only; CE 6.0..699; Btdrt.lib] */
int BthActivatePAN (
 BOOL fActivate
);

/* BthNotifyEvent  [function; ce-only; CE 6.0..699; heuristic-prefix] */
HANDLE BthNotifyEvent(
 PBTEVENT pbtEvent,
 DWORD dwEventClass
);

/* BthSetCODInquiryFilter  [function; ce-only; CE 6.0..699; Btdrt.lib] */
int BthSetCODInquiryFilter (
 unsigned int cod,
 unsigned int codMask
);

/* RequestBluetoothNotifications  [function; ce-only; CE 6.0..699; coredll.lib] */
HANDLE RequestBluetoothNotifications(
 DWORD dwClass,
 HANDLE hMsgQ
);

/* StopBluetoothNotifications  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL StopBluetoothNotifications(
 HANDLE h
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
DWORD BthAGNetworkHangupCall(DWORD dwFlags);
DWORD BthAgNetworkHoldCall(void);

#endif /* _BT_API_ */
