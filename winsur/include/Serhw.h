/* Serhw.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 37 declarations, 1 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _SERHW_
#define _SERHW_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* HW_VTBL  [struct; ce-only] */
#ifdef USE_NEW_SERIAL_MODEL
typedef struct __HWOBJ HWOBJ, *PHWOBJ;
typedef struct __HW_VTBL {
 PVOID (*HWInit)(ULONG Identifier, PVOID pMDDContext, PHWOBJ pHWObj);
 BOOL (*HWPostInit)(PVOID pHead);
 ULONG (*HWDeinit)(PVOID pHead);
 BOOL (*HWOpen)(PVOID pHead);
 ULONG (*HWClose)(PVOID pHead);
 INTERRUPT_TYPE (*HWGetIntrType)(PVOID pHead);
 ULONG (*HWRxIntrHandler)(PVOID pHead, PUCHAR pTarget, PULONG pBytes);
 VOID (*HWTxIntrHandler)(PVOID pHead, PUCHAR pSrc, PULONG pBytes);
 VOID (*HWModemIntrHandler)(PVOID pHead);
 VOID (*HWLineIntrHandler)(PVOID pHead);
 ULONG (*HWGetRxBufferSize)(PVOID pHead);
 BOOL (*HWPowerOff)(PVOID pHead);
 BOOL (*HWPowerOn)(PVOID pHead);
 VOID (*HWClearDTR)(PVOID pHead);
 VOID (*HWSetDTR)(PVOID pHead);
 VOID (*HWClearRTS)(PVOID pHead);
 VOID (*HWSetRTS)(PVOID pHead);
 BOOL (*HWEnableIR)(PVOID pHead, ULONG BaudRate);
 BOOL (*HWDisableIR)(PVOID pHead);
 VOID (*HWClearBreak)(PVOID pHead);
 VOID (*HWSetBreak)(PVOID pHead);
 BOOL (*HWXmitComChar)(PVOID pHead, UCHAR ComChar);
 ULONG (*HWGetStatus)(PVOID pHead, LPCOMSTAT lpStat);
 VOID (*HWReset)(PVOID pHead);
 VOID (*HWGetModemStatus)(PVOID pHead, PULONG pModemStatus);
 VOID (*HWGetCommProperties)(PVOID pHead, LPCOMMPROP pCommProp);
 VOID (*HWPurgeComm)(PVOID pHead, DWORD fdwAction);
 BOOL (*HWSetDCB)(PVOID pHead, LPDCB pDCB);
 BOOL (*HWSetCommTimeouts)(PVOID pHead, LPCOMMTIMEOUTS lpCommTO);
 BOOL (*HWIoctl)(PVOID pHead, DWORD dwCode,PBYTE pBufIn,DWORD dwLenIn, PBYTE pBufOut,DWORD dwLenOut,PDWORD pdwActualOut);
} HW_VTBL, *PHW_VTBL;
#else
typedef struct __HW_VTBL {
 PVOID (*HWInit)(ULONG Identifier, PVOID pMDDContext);
 ULONG (*HWDeinit)(PVOID pHead);
 BOOL (*HWOpen)(PVOID pHead);
 ULONG (*HWClose)(PVOID pHead);
 ULONG (*HWGetBytes)(PVOID pHead, PUCHAR pTarget, PULONG pBytes);
 PVOID (*HWGetRxStart)(PVOID pHead);
 INTERRUPT_TYPE (*HWGetIntrType)(PVOID pHead);
 VOID (*HWOtherIntrHandler)(PVOID pHead);
 VOID (*HWLineIntrHandler)(PVOID pHead);
 ULONG (*HWGetRxBufferSize)(PVOID pHead);
 VOID (*HWTxIntrHandler)(PVOID pHead);
 ULONG (*HWPutBytes)(PVOID pHead, PUCHAR pSrc, ULONG NumBytes, PULONG pBytesSent);
 BOOL (*HWPowerOff)(PVOID pHead);
 BOOL (*HWPowerOn)(PVOID pHead);
 VOID (*HWClearDTR)(PVOID pHead);
 VOID (*HWSetDTR)(PVOID pHead);
 VOID (*HWClearRTS)(PVOID pHead);
 VOID (*HWSetRTS)(PVOID pHead);
 BOOL (*HWEnableIR)(PVOID pHead, ULONG BaudRate);
 BOOL (*HWDisableIR)(PVOID pHead);
 VOID (*HWClearBreak)(PVOID pHead);
 VOID (*HWSetBreak)(PVOID pHead);
 BOOL (*HWXmitComChar)(PVOID pHead, UCHAR ComChar);
 ULONG (*HWGetStatus)(PVOID pHead, LPCOMSTAT lpStat);
 VOID (*HWReset)(PVOID pHead);
 VOID (*HWGetModemStatus)(PVOID pHead, PULONG pModemStatus);
 VOID (*HWGetCommProperties)(PVOID pHead, LPCOMMPROP pCommProp);
 VOID (*HWPurgeComm)(PVOID pHead, DWORD fdwAction);
 BOOL (*HWSetDCB)(PVOID pHead, LPDCB pDCB);
 BOOL (*HWSetCommTimeouts)(PVOID pHead, LPCOMMTIMEOUTS lpCommTO);
 BOOL (*HWIoctl)(PVOID pHead, DWORD dwCode,PBYTE pBufIn, DWORD dwLenIn, PBYTE pBufOut,DWORD dwLenOut,PDWORD pdwActualOut);
} HW_VTBL, *PHW_VTBL;
#endif

/* HWOBJ  [struct; ce-only] */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 2.11..2.12, 3.0..399 */

/* HWGetBytes  [function; ce-only; CE 2.11..2.12, 3.0..399] */
ULONG HWGetBytes( 
PVOID pContext, 
PUCHAR pTargetBuffer, 
PULONG pByteNumber );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* HWClearBreak  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWClearBreak(
 PVOID pContext 
);

/* HWClearDTR  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWClearDTR(
 PVOID pContext 
);

/* HWClearRTS  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWClearRTS(
 PVOID pContext 
);

/* HWClose  [function; ce-only; CE 2.11..2.12, 3.0..699] */
ULONG HWClose(
 PVOID pContext 
);

/* HWDeinit  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWDeinit(
 PVOID pContext 
);

/* HWDisableIR  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWDisableIR(
 PVOID pContext 
);

/* HWEnableIR  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWEnableIR(
 PVOID pContext,
 ULONG BaudRate 
);

/* HWGetModemStatus  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWGetModemStatus(
 PVOID pContext,
 PULONG pModemStatus 
);

/* HWGetRxBufferSize  [function; ce-only; CE 2.11..2.12, 3.0..699] */
ULONG HWGetRxBufferSize(
 PVOID pContext 
);

/* HWGetRxStart  [function; ce-only; CE 2.11..2.12, 3.0..699] */
PVOID HWGetRxStart(
 PVOID pContext 
);

/* HWGetStatus  [function; ce-only; CE 2.11..2.12, 3.0..699] */
ULONG HWGetStatus(
 PVOID pContext,
 LPCOMSTAT lpStat 
);

/* HWIoctl  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWIoctl(
 DWORD dwOpenData,
 DWORD dwCode,
 PBYTE pBufIn,
 DWORD dwLenIn,
 PBYTE pBufOut,
 DWORD dwLenOut,
 PDWORD pdwActualOut 
);

/* HWOpen  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWOpen(
 PVOID pContext 
);

/* HWPowerOff  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWPowerOff(
 PVOID pContext 
);

/* HWPowerOn  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWPowerOn(
 PVOID pContext 
);

/* HWPurgeComm  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWPurgeComm(
 PVOID pContext,
 DWORD fdwAction 
);

/* HWPutBytes  [function; ce-only; CE 2.11..2.12, 3.0..699] */
ULONG HWPutBytes(
 PVOID pContext,
 PUCHAR pSrc,
 ULONG NumberOfBytes,
 PULONG pBytesSent 
);

/* HWReset  [function; ce-only; CE 2.11..2.12, 3.0..699] */
void HWReset(
 PVOID pContext 
);

/* HWSetBreak  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWSetBreak(
 PVOID pContext 
);

/* HWSetCommTimeouts  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWSetCommTimeouts(
 PVOID pContext,
 LPCOMMTIMEOUTS lpCommTO 
);

/* HWSetDCB  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWSetDCB(
 PVOID pContext,
 LPDCB pDCB 
);

/* HWSetDTR  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWSetDTR(
 PVOID pContext 
);

/* HWSetRTS  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWSetRTS(
 PVOID pContext 
);

/* HWTxIntrHandler  [function; ce-only; CE 2.11..2.12, 3.0..699] */
VOID HWTxIntrHandler(
 PVOID pContext, 
 PUCHAR pSourceBuffer, 
 PULONG pByteNumber 
);

/* HWXmitComChar  [function; ce-only; CE 2.11..2.12, 3.0..699] */
BOOL HWXmitComChar(
 PVOID pContext,
 UCHAR ComChar 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* HWLineIntrHandler  [function; ce-only; CE 3.0..699] */
VOID HWLineIntrHandler(
 PVOID pContext
);

/* HWModemIntrHandler  [function; ce-only; CE 3.0..699] */
VOID HWModemIntrHandler(
 PVOID pContext
);

/* HWOtherIntrHandler  [function; ce-only; CE 3.0..699] */
VOID HWOtherHandler(
 PVOID pContext
);

/* HWPostInit  [function; ce-only; CE 3.0..699] */
BOOL HWPostInit(
 PVOID pContext 
);

/* HWRxIntrHandler  [function; ce-only; CE 3.0..699] */
ULONG HWRxIntrHandler(
 PVOID pContext,
 PUCHAR pTargetBuffer,
 PULONG pByteNumber 
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
VOID HWOtherHandler(PVOID pContext);

#endif /* _SERHW_ */
