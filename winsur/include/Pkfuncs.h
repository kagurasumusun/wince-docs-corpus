/* Pkfuncs.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 19 constants, 118 declarations, 1 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _PKFUNCS_
#define _PKFUNCS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define INTA 1
#define INTB 2
#define INTC 3
#define INTD 4
#define KD_IOCTL_CLEAR_CBP 0x00000002
#define KD_IOCTL_CLEAR_DBP 0x00000011
#define KD_IOCTL_DMPGEN_END 0x00000051
#define KD_IOCTL_DMPGEN_START 0x00000050
#define KD_IOCTL_ENUM_CBP 0x00000004
#define KD_IOCTL_ENUM_DBP 0x00000013
#define KD_IOCTL_INIT 0x00000000
#define KD_IOCTL_JIT_NOTIF 0x00000040
#define KD_IOCTL_MAP_EXCEPTION 0x00000020
#define KD_IOCTL_MEMORY_INACCESSIBLE 0x00000060
#define KD_IOCTL_QUERY_CBP 0x00000003
#define KD_IOCTL_QUERY_DBP 0x00000012
#define KD_IOCTL_RESET 0x00000030
#define KD_IOCTL_SET_CBP 0x00000001
#define KD_IOCTL_SET_DBP 0x00000010

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* IsInPwrHdlr  [macro; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CacheInfo  [struct; ce-only] */
typedef struct _CacheInfo {
 DWORD dwL1Flags;
 DWORD dwL1ICacheSize;
 DWORD dwL1ICacheLineSize;
 DWORD dwL1ICacheNumWays;
 DWORD dwL1DCacheSize;
 DWORD dwL1DCacheLineSize;
 DWORD dwL1DCacheNumWays;
 DWORD dwL2Flags;
 DWORD dwL2ICacheSize;
 DWORD dwL2ICacheLineSize;
 DWORD dwL2ICacheNumWays;
 DWORD dwL2DCacheSize;
 DWORD dwL2DCacheLineSize;
 DWORD dwL2DCacheNumWays;
} CacheInfo, *PCacheInfo;

/* CallSnapshot  [struct; ce-only] */
typedef struct _CallSnapshot {
 DWORD dwReturnAddr;
} CallSnapshot;
typedef CallSnapshot *PCallSnapshot, *LPCallSnapshot;

/* CallSnapshot3  [struct; ce-only] */
typedef struct _CallSnapshot3 {
 DWORD dwReturnAddr;
 DWORD dwFramePtr;
 DWORD dwActvProc;
 DWORD dwVMProc;
 DWORD dwParams[4];
} CallSnapshot3;
typedef CallSnapshot3 *PCallSnapshot3, *LPCallSnapshot3;

/* CallSnapshotEx  [struct; ce-only] */
typedef struct _CallSnapshotEx {
 DWORD dwReturnAddr;
 DWORD dwFramePtr;
 DWORD dwCurProc;
 DWORD dwParams[4];
} CallSnapshotEx;
typedef CallSnapshotEx *PCallSnapshotEx, *LPCallSnapshotEx;

/* CeLogImportTable  [struct; ce-only] */
typedef struct _CeLogImportTable {
 DWORD dwVersion;
 FARPROC pCreateEventW;
 FARPROC pEventModify;
 FARPROC pCreateFileMappingW;
 FARPROC pMapViewOfFile;
 FARPROC pUnmapViewOfFile;
 FARPROC pCloseHandle;
 FARPROC pLockPages;
 FARPROC pUnlockPages;
 FARPROC pVirtualAlloc;
 FARPROC pVirtualFree;
 FARPROC pMapPtrToProcess;
 FARPROC pQueryPerformanceCounter;
 FARPROC pQueryPerformanceFrequency;
 FARPROC pNKDbgPrintfW;
 FARPROC pCeLogReSync;
 FARPROC pGetLastError;
 FARPROC pSetLastError;
 FARPROC pGetThreadCallStack;
 FARPROC pInSysCall;
 DWORD* pdwCeLogTLBMiss;
 DWORD dwCeLogLargeBuf;
 DWORD dwCeLogSmallBuf;
 DWORD dwDefaultThreadQuantum;
} CeLogImportTable;
typedef CeLogImportTable *PCeLogImportTable, *LPCeLogImportTable;

/* DEVICE_ID  [struct; ce-only] */
typedef struct _DEVICE_ID {
 DWORD dwSize;
 DWORD dwPresetIDOffset;
 DWORD dwPresetIDBytes;
 DWORD dwPlatformIDOffset;
 DWORD dwPlatformIDBytes;
} DEVICE_ID, *PDEVICE_ID;

/* DEVICE_LOCATION  [struct; ce-only] */
typedef struct _DEVICE_LOCATION {
 DWORD IfcType;
 DWORD BusNumber;
 DWORD LogicalLoc;
 PVOID PhysicalLoc;
 DWORD Pin;
} DEVICE_LOCATION, *PDEVICE_LOCATION;

/* DEVICE_PSL_NOTIFY  [struct; ce-only] */
typedef struct _DEVICE_PSL_NOTIFY {
 DWORD dwSize;
 DWORD dwFlags;
 HANDLE hProc;
 HANDLE hThread;
} DEVICE_PSL_NOTIFY, *PDEVICE_PSL_NOTIFY;

/* KD_BPINFO  [struct; ce-only] */
typedef struct _KD_BPINFO {
 int nVersion; 
 ULONG ulFlags; 
 ULONG ulAddress; 
 ULONG ulHandle; 
 ULONG ulCount;
} KD_BPINFO, *PKD_BPINFO;

/* KD_EXCEPTION_INFO  [struct; ce-only] */
typedef struct _KD_EXCEPTION_INFO {
 int nVersion; 
 ULONG ulFlags; 
 ULONG ulAddress; 
 ULONG ulExceptionCode; 
} KD_EXCEPTION_INFO, *PKD_EXCEPTION_INFO;

/* NKPagePoolParameters  [struct; ce-only] */
typedef struct {
 WORD NKVersion;
 WORD OEMVersion;
 PagePoolParameters Loader;
 PagePoolParameters File;
} NKPagePoolParameters;
typedef NKPagePoolParameters *PNKPagePoolParameters, *LPNKPagePoolParameters;

/* NKPagePoolState  [struct; ce-only] */
typedef struct {
 WORD Version;
 WORD Reserved;
 PagePoolParameters LoaderParams;
 PagePoolState LoaderState;
 PagePoolParameters FileParams;
 PagePoolState FileState;
} NKPagePoolState;
typedef NKPagePoolState *PNKPagePoolState, *LPNKPagePoolState;

/* PagePoolParameters  [struct; ce-only] */
typedef struct {
 DWORD Target;
 DWORD Maximum;
 DWORD ReleaseIncrement;
 DWORD CriticalIncrement;
 WORD NormalPriority256;
 WORD CriticalPriority256;
} PagePoolParameters;
typedef PagePoolParameters *PPagePoolParameters, *LPPagePoolParameters;

/* PagePoolState  [struct; ce-only] */
typedef struct {
 DWORD CurrentSize;
 DWORD TrimCount;
 DWORD TrimTime;
 DWORD CriticalCount;
 DWORD CriticalTime;
 DWORD FailCount;
} PagePoolState;
typedef PagePoolState *PPagePoolState, *LPPagePoolState;

/* PHYSICAL_BASIC_INFORMATION  [struct; ce-only] */
typedef struct _PHYSICAL_BASIC_INFORMATION { 
 PVOID lpBaseAddress; 
 DWORD dwRegionSize; 
 DWORD dwType; 
} PHYSICAL_BASIC_INFORMATION; 
typedef PHYSICAL_BASIC_INFORMATION* PPHYSICAL_BASIC_INFORMATION;
typedef PHYSICAL_BASIC_INFORMATION *PPHYSICAL_BASIC_INFORMATION, *LPPHYSICAL_BASIC_INFORMATION;

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* PFNAPIERRHANDLER  [callback; ce-only; CE 6.0..699; coredll.lib] */
typedef DWORD (*PFNAPIERRHANDLER)(DWORD);
DWORD pfnHandler(DWORD iMethod);
#endif /* _WIN32_WCE */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* CacheSync  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
VOID CacheSync(
 int flags
);

/* CeGetRandomSeed  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib, Nk.lib] */
__int64 CeGetRandomSeed (void);

/* ForcePageout  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
VOID ForcePageout (void);

/* GetCurrentPermissions  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD GetCurrentPermissions (void);

/* GetOwnerProcess  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
HANDLE GetOwnerProcess (void);

/* InterruptDisable  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
VOID InterruptDisable(
 DWORD idInt
);

/* InterruptDone  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
VOID InterruptDone(
 DWORD idInt
);

/* InterruptInitialize  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL InterruptInitialize(
 DWORD idInt,
 HANDLE hEvent,
 LPVOID pvData,
 DWORD cbData
);

/* KernelIoControl  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL KernelIoControl(
 DWORD dwIoControlCode,
 LPVOID lpInBuf,
 DWORD nInBufSize,
 LPVOID lpOutBuf,
 DWORD nOutBufSize,
 LPDWORD lpBytesReturned
);

/* LoadDriver  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
HINSTANCE LoadDriver(
 LPCWSTR lpszFileName
);

/* LockPages  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL LockPages(
 LPVOID lpvAddress,
 DWORD cbSize,
 PDWORD pPFNs,
 int fOptions
);

/* MapPtrToProcess  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LPVOID MapPtrToProcess(
 LPVOID lpv,
 HANDLE hProc
);

/* SetKMode  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL SetKMode(
 BOOL fMode
);

/* SetProcPermissions  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD SetProcPermissions(
 DWORD newperms
);

/* SetStoreQueueBase  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LPVOID SetStoreQueueBase(
 DWORD dwPhysPage
);

/* UnlockPages  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL UnlockPages(
 LPVOID lpvAddress,
 DWORD cbSize
);

/* UnMapPtr  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LPVOID UnMapPtr(
 LPVOID lpv
);

/* VirtualCopy  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL VirtualCopy(
 LPVOID lpvDest,
 LPVOID lpvSrc,
 DWORD cbSize,
 DWORD fdwProtect
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* OEMKDIoControl  [function; ce-only; CE 3.0..699; Nk.lib] */
BOOL OEMKDIoControl(
 DWORD dwIoControlCode, 
 LPVOID lpBuf, 
 DWORD nBufSize 
);

/* ReadRegistryFromOEM  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
DWORD ReadRegistryFromOEM(
 DWORD dwFlags, 
 LPBYTE lpData, 
 DWORD cbData 
);

/* SetCleanRebootFlag  [function; ce-only; CE 3.0..699; Coredll.lib, coredll.lib] */
void SetCleanRebootFlag(void);

/* SetOOMEvent  [function; ce-only; CE 3.0..699; Coredll.lib, coredll.lib] */
void SetOOMEvent(
 HANDLE hEvent,
 DWORD cpLow,
 DWORD cpCritical,
 DWORD cpLowBlockSize,
 DWORD cpCriticalBlockSize 
);

/* VirtualSetPageFlags  [function; ce-only; CE 3.0..699; Coredll.lib, coredll.lib] */
BOOL VirtualSetPageFlags(
 LPVOID lpvAddress, 
 DWORD cbSize, 
 DWORD dwFlags, 
 LPDWORD lpdwOldFlags 
);

/* WriteRegistryToOEM  [function; ce-only; CE 3.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL WriteRegistryToOEM( 
 DWORD dwFlags, 
 LPBYTE lpData, 
 DWORD cbData 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* FreeIntChainHandler  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
BOOL FreeIntChainHandler(
 HANDLE hInstance
);

/* LoadKernelLibrary  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
HANDLE LoadKernelLibrary(
 LPCWSTR lpszFileName
);

/* NKCreateStaticMapping  [function; ce-only; CE 4.0..699; Coredll.lib, Nkstub.lib] */
LPVOID NKCreateStaticMapping(
 DWORD dwPhysBase,
 DWORD dwSize
);

/* NKForceCleanBoot  [function; ce-only; CE 4.0..699; Coredll.lib, Nkstub.lib] */
VOID NKForceCleanBoot(void);

/* PowerOffSystem  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
void PowerOffSystem(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* AllocPhysMem  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
LPVOID AllocPhysMem(
 DWORD cbSize,
 DWORD fdwProtect,
 DWORD dwAlignmentMask,
 DWORD dwFlags,
 PULONG pPhysicalAddress
);

/* CacheRangeFlush  [function; ce-only; CE 5.0..699; Coredll.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
void CacheRangeFlush(
 LPVOID pAddr,
 DWORD dwLength,
 DWORD dwFlags
);

/* CaptureDumpFileOnDevice  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CaptureDumpFileOnDevice(
 DWORD dwProcessId,
 DWORD dwThreadId, 
 LPCWSTR pwzExtraFilesPath
);

/* CeGetCacheInfo  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeGetCacheInfo(
 DWORD cbSize,
 PCacheInfo pCacheInfo
);

/* CeSetMemoryAttributes  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeSetMemoryAttributes(
 LPVOID pVirtualAddr,
 LPVOID pShiftedPhysAddr,
 DWORD cbSize,
 DWORD dwAttributes
);

/* CeVirtualSharedAlloc  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
LPVOID CeVirtualSharedAlloc(
 LPVOID lpvAddr,
 DWORD cbSize,
 DWORD fdwAction
);

/* CreateStaticMapping  [function; ce-only; CE 5.0..699; Coredll.lib, Nkstub.lib] */
LPVOID CreateStaticMapping(
 DWORD dwPhysBase,
 DWORD dwSize
);

/* CreateWatchDogTimer  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HANDLE CreateWatchDogTimer(
 LPCWSTR pszWatchDogName,
 DWORD dwPeriod,
 DWORD dwWait,
 DWORD dwDfltAction,
 DWORD dwParam,
 DWORD dwFlags
);

/* DrWatsonClear  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL DrWatsonClear(void);

/* DrWatsonFlush  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL DrWatsonFlush(void);

/* DrWatsonGetSize  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD DrWatsonGetSize(void);

/* DrWatsonReadData  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD DrWatsonReadData(
 DWORD dwOffset,
 LPVOID pData,
 DWORD cbSize
);

/* DrWatsonWriteData  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD DrWatsonWriteData(
 DWORD dwOffset,
 LPVOID pData,
 DWORD cbSize
);

/* FreePhysMem  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL FreePhysMem(
 LPVOID lpvAddress
);

/* GetCallerProcess  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HANDLE GetCallerProcess(void);

/* GetEventData  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
DWORD GetEventData(
 HANDLE hEvent
);

/* GetThreadCallStack  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
ULONG GetThreadCallStack(
 HANDLE hThrd,
 ULONG dwMaxFrames,
 LPVOID lpFrames[],
 DWORD dwFlags,
 DWORD dwSkip
);

/* InterruptMask  [function; ce-only; CE 5.0..699; Coredll.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
VOID InterruptMask(
 DWORD idInt,
 BOOL fDisable
);

/* IsNamedEventSignaled  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL IsNamedEventSignaled(
 LPCWSTR pszName,
 DWORD dwFlags
);

/* KernelLibIoControl  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL KernelLibIoControl(
 HANDLE hModule,
 DWORD dwIoControlCode,
 LPVOID lpInBuf,
 DWORD nInBufSize,
 LPVOID lpOutBuf,
 DWORD nOutBufSize,
 LPDWORD lpBytesReturned
);

/* KLibAllocShareMem  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL KLibAllocShareMem(
 DWORD nPages,
 BOOL fNoCache,
 LPVOID* pVa,
 LPVOID* pPa
);

/* KLibFreeShareMem  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL KLibFreeShareMem(
 DWORD nPages,
 LPVOID pVa,
 LPVOID pPa
);

/* LoadIntChainHandler  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HANDLE LoadIntChainHandler(
 LPCWSTR lpFilename,
 LPCWSTR lpszFunctionName,
 BYTE bIRQ
);

/* MapCallerPtr  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
LPVOID MapCallerPtr(
 LPVOID ptr,
 DWORD dwLen
);

/* NKRegCloseKey  [function; ce-only; CE 5.0..699; Coredll.lib, Nkstub.lib] */
LONG NKRegCloseKey(
 HKEY hKey
);

/* NKRegQueryValueEx  [function; ce-only; CE 5.0..699; Coredll.lib, Nkstub.lib] */
LONG NKRegQueryValueEx(
 HKEY hKey, 
 LPCWSTR lpValueName, 
 LPDWORD lpReserved, 
 LPDWORD lpType, 
 LPBYTE lpData, 
 LPDWORD lpcbData
);

/* NKRegSetValueEx  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
LONG NKRegSetValueEx(
 HKEY hKey, 
 LPCWSTR lpValueName, 
 DWORD dwReserved, 
 DWORD dwType, 
 LPBYTE lpData, 
 DWORD cbData
);

/* NKVirtualSetAttributes  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL NKVirtualSetAttributes(
 LPVOID lpvAddress,
 DWORD cbSize,
 DWORD dwNewFlags,
 DWORD dwMask,
 LPDWORD lpdwOldFlags
);

/* OpenWatchDogTimer  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HANDLE OpenWatchDogTimer(
 LPCWSTR pszWatchDogName,
 DWORD dwFlags
);

/* PageOutModule  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL PageOutModule(
 HANDLE hModule,
 DWORD dwFlags
);

/* RefreshWatchDogTimer  [function; ce-only; CE 5.0..699; Coredll.lib, OEMMain.lib, OEMMain_StaticKITL.lib] */
BOOL RefreshWatchDogTimer(
 HANDLE hWatchDog,
 DWORD dwFlags
);

/* SetEventData  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL SetEventData(
 HANDLE hEvent,
 DWORD dwData
);

/* SetJITDebuggerPath  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL SetJITDebuggerPath(
 LPCWSTR pszDbgrPath 
);

/* SleepTillTick  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
void SleepTillTick();

/* StartWatchDogTimer  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL StartWatchDogTimer(
 HANDLE hWatchDog,
 DWORD dwFlags
);

/* StopWatchDogTimer  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL StopWatchDogTimer(
 HANDLE hWatchDog,
 DWORD dwFlags
);

/* VirtualSetAttributes  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL VirtualSetAttributes(
 LPVOID lpvAddress,
 DWORD cbSize,
 DWORD dwNewFlags,
 DWORD dwMask,
 LPDWORD lpdwOldFlags
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* CeAllocAsynchronousBuffer  [function; ce-only; CE 6.0..699; coredll.lib] */
HRESULT CeAllocAsynchronousBuffer(
 PVOID * ppDestAsyncMarshalled,
 PVOID pSrcSyncMarshalled,
 DWORD cbSrc,
 DWORD ArgumentDescriptor
);

/* CeAllocDuplicateBuffer  [function; ce-only; CE 6.0..699; coredll.lib] */
HRESULT CeAllocDuplicateBuffer(
 PVOID * ppDestDuplicate,
 PVOID pSrcMarshalled,
 DWORD cbSrc,
 DWORD ArgumentDescriptor
);

/* CeCallUserProc  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeCallUserProc(
 LPCWSTR pszDllName,
 LPCWSTR pszFuncName,
 LPVOID lpInBuffer,
 DWORD nInBufferSize,
 LPVOID lpOutBuffer,
 DWORD nOutBufferSize,
 LPDWORD lpBytesReturned
);

/* CeCloseCallerBuffer  [function; ce-only; CE 6.0..699; coredll.lib] */
HRESULT CeCloseCallerBuffer(
 PVOID pDestMarshalled,
 PVOID pSrcUnmarshalled,
 DWORD cbSrc,
 DWORD ArgumentDescriptor
);

/* CeFlushAsynchronousBuffer  [function; ce-only; CE 6.0..699; coredll.lib] */
HRESULT CeFlushAsynchronousBuffer(
 PVOID pDestAsyncMarshalled,
 PVOID pSrcSyncMarshalled,
 PVOID pSrcUnmarshalled,
 DWORD cbSrc,
 DWORD ArgumentDescriptor
);

/* CeFreeAsynchronousBuffer  [function; ce-only; CE 6.0..699; coredll.lib] */
HRESULT CeFreeAsynchronousBuffer(
 PVOID pDestAsyncMarshalled,
 PVOID pSrcSyncMarshalled,
 DWORD cbSrc,
 DWORD ArgumentDescriptor
);

/* CeFreeDuplicateBuffer  [function; ce-only; CE 6.0..699; coredll.lib] */
HRESULT CeFreeDuplicateBuffer(
 PVOID pDestDuplicate,
 PVOID pSrcMarshalled,
 DWORD cbSrc,
 DWORD ArgumentDescriptor
);

/* CeGetRawTime  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeGetRawTime(
 ULONGLONG * pui64Millsec
);

/* CeGetRawTimeOffset  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeGetRawTimeOffset(
 LONGLONG * pi64Offset
);

/* CeImpersonateCurrentProcess  [function; ce-only; CE 6.0..699; coredll.dll] */
BOOL CeImpersonateCurrentProcess (
 void
);

/* CeRemoteHeapCreate  [function; ce-only; CE 6.0..699; coredll.lib] */
HANDLE CeRemoteHeapCreate (
 DWORD dwProcessId,
 DWORD dwFlags
);

/* CeRemoteHeapTranslatePointer  [function; ce-only; CE 6.0..699; coredll.lib] */
LPVOID CeRemoteHeapTranslatePointer(
 HANDLE hHeap,
 DWORD dwFlags,
 LPVOID ptr
);

/* CreateAPIHandle  [function; ce-only; CE 6.0..699; coredll.lib] */
HANDLE CreateAPIHandle(
 HANDLE hASet,
 LPVOID pvData
);

/* DeleteStaticMapping  [function; ce-only; CE 6.0..699; Nkstub.lib] */
BOOL DeleteStaticMapping(
 LPVOID pVirtBase,
 DWORD dwSize
);

/* ForwardDeviceIoControl  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL ForwardDeviceIoControl (
 HANDLE hDevice,
 DWORD dwIoControlCode,
 LPVOID lpInBuf,
 DWORD nInBufSize,
 LPVOID lpOutBuf,
 DWORD nOutBufSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);

/* GetCallerVMProcessId  [function; ce-only; CE 6.0..699; coredll.lib] */
DWORD GetCallerVMProcessId (void);

/* GetDirectCallerProcessId  [function; ce-only; CE 6.0..699; coredll.lib] */
DWORD GetDirectCallerProcessId (void);

/* KLibUnalignedAccessEnable  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL KLibUnalignedAccessEnable (
 BOOL fEnable
);

/* NKDeleteStaticMapping  [function; ce-only; CE 6.0..699; Nkstub.lib] */
BOOL NKDeleteStaticMapping (
 LPVOID pVirtAddr,
 DWORD dwSize
);

/* RegisterAPISet  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL RegisterAPISet(
 HANDLE hASet,
 DWORD dwSetID
);

/* SetAPIErrorHandler  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL SetAPIErrorHandler(
 HANDLE hApiSet,
 PFNAPIERRHANDLER pfnHandler
);

/* VirtualAllocCopyEx  [function; ce-only; CE 6.0..699; coredll.lib] */
LPVOID VirtualAllocCopyEx (
 HANDLE hSrcProc,
 HANDLE hDstProc,
 LPVOID pAddr,
 DWORD cbSize,
 DWORD dwProtect
);

/* VirtualCopyEx  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL VirtualCopyEx(
 HANDLE hDstProc,
 LPVOID lpvDest,
 HANDLE hSrcProc,
 LPVOID lpvSrc,
 DWORD cbSize,
 DWORD fdwProtect
);
#endif /* _WIN32_WCE */

#endif /* _PKFUNCS_ */
