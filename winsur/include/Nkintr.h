/* Nkintr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 32 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NKINTR_
#define _NKINTR_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MEMORY_SECTION  [struct; ce-only] */
typedef struct _MEMORY_SECTION {
 DWORD dwFlags;
 DWORD dwStart;
 DWORD dwLen;
} MEMORY_SECTION, *PMEMORY_SECTION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 3.0..399 */

/* OEMParallelPortGetByte  [function; ce-only; CE 3.0..399] */
int OEMParallelPortGetByte (void);

/* OEMParallelPortSendByte  [function; ce-only; CE 3.0..399] */
void OEMParallelPortSendByte ( 
BYTE ch );

/* SetKernelCommDev  [function; ce-only; CE 3.0..399] */
BOOL SetKernelCommDev( 
UCHAR Service, 
UCHAR CommDevice );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* HookInterrupt  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, Nkstub.lib] */
BOOL HookInterrupt(
 int hwIntNumber,
 FARPROC pfnHandler
);

/* INTERRUPTS_OFF  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib] */
VOID INTERRUPTS_OFF (void);

/* INTERRUPTS_ON  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib] */
VOID INTERRUPTS_ON (void);

/* KCompareFileTime  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, Nkstub.lib] */
LONG KCompareFileTime(
 LPFILETIME lpft1,
 LPFILETIME lpft2
);

/* KFileTimeToSystemTime  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, Nkstub.lib] */
BOOL KFileTimeToSystemTime(
 const FILETIME* lpft,
 LPSYSTEMTIME lpst
);

/* KSystemTimeToFileTime  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, Nkstub.lib] */
BOOL KSystemTimeToFileTime(
 LPSYSTEMTIME lpst,
 LPFILETIME lpft
);

/* OEMClearDebugCommError  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMClearDebugCommError (void);

/* OEMGetExtensionDRAM  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL OEMGetExtensionDRAM( 
 LPDWORD lpMemStart, 
 LPDWORD lpMemLen 
);

/* OEMGetRealTime  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL OEMGetRealTime(
 LPSYSTEMTIME lpst 
);

/* OEMInit  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMInit (void);

/* OEMInitDebugSerial  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMInitDebugSerial (void);

/* OEMInterruptDisable  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMInterruptDisable( 
 DWORD idInt 
);

/* OEMInterruptDone  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMInterruptDone( 
 DWORD idInt 
);

/* OEMInterruptEnable  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL OEMInterruptEnable(
 DWORD idInt, 
 LPVOID pvData, 
 DWORD cbData 
);

/* SetInterruptEvent  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, Nkstub.lib] */
BOOL SetInterruptEvent(
 DWORD idInt
);

/* UnhookInterrupt  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, Nkstub.lib] */
BOOL UnhookInterrupt(
 INT hwInterruptNumber,
 FARPROC pfnHandler
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* OEMPowerOff  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMPowerOff (void);

/* OEMReadDebugByte  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
int OEMReadDebugByte (void);

/* OEMSetAlarmTime  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL OEMSetAlarmTime(
 LPSYSTEMTIME lpst 
);

/* OEMSetRealTime  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL OEMSetRealTime( 
 LPSYSTEMTIME lpst 
);

/* OEMWriteDebugByte  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMWriteDebugByte(
 BYTE ch 
);

/* OEMWriteDebugLED  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMWriteDebugLED(
 WORD wIndex, 
 DWORD dwPattern 
);

/* OEMWriteDebugString  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void OEMWriteDebugString(
 unsigned short* str 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CeSetPowerOnEvent  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeSetPowerOnEvent(
 HANDLE hEvt
);

/* INTERRUPTS_ENABLE  [function; ce-only; CE 5.0..699; Nk.lib] */
BOOL INTERRUPTS_ENABLE(
 BOOL fEnable
);

/* NKCallIntChain  [function; ce-only; CE 5.0..699; Nk.lib, Nkstub.lib] */
DWORD NKCallIntChain(
 BYTE irq
);

/* NKIsSysIntrValid  [function; ce-only; CE 5.0..699; Nk.lib, Nkstub.lib] */
BOOL NKIsSysIntrValid( 
 DWORD idInt 
);

/* OEMEnumExtensionDRAM  [function; ce-only; CE 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
DWORD OEMEnumExtensionDRAM(
 PMEMORY_SECTION pMemSections,
 DWORD cMemSections
);
#endif /* _WIN32_WCE */

#endif /* _NKINTR_ */
