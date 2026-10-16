/* Celog.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 32 constants, 94 declarations, 1 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _CELOG_
#define _CELOG_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define BOOT_TIME_DEV_ACTIVATE 20
#define BOOT_TIME_DEV_FINISHED 21
#define BOOT_TIME_FS_DB_INITIALIZED 14
#define BOOT_TIME_FS_FILES_INITIALIZED 12
#define BOOT_TIME_FS_INITED 10
#define BOOT_TIME_FS_LAUNCH 15
#define BOOT_TIME_FS_OBJ_STORE_INITIALIZED 11
#define BOOT_TIME_FS_REG_INITIALIZED 13
#define BOOT_TIME_GWES_FINISHED 30
#define BOOT_TIME_LAUNCHING_FS 01
#define BOOT_TIME_SYSTEM_STARTED 40
#define CELZONE_ALWAYSON 0x40000000
#define CELZONE_BOOT_TIME 0x00010000
#define CELZONE_CRITSECT 0x00000100
#define CELZONE_DEBUG 0x00800000
#define CELZONE_DEMANDPAGE 0x00000010
#define CELZONE_HEAP 0x00000800
#define CELZONE_INTERRUPT 0x00000001
#define CELZONE_KCALL 0x00400000
#define CELZONE_LOADER 0x00004000
#define CELZONE_MEMTRACKING 0x00008000
#define CELZONE_MIGRATE 0x00000004
#define CELZONE_MISC 0x80000000
#define CELZONE_PRIORITYINV 0x00000080
#define CELZONE_PROCESS 0x00000040
#define CELZONE_RESCHEDULE 0x00000002
#define CELZONE_RESERVED1 0x20000000
#define CELZONE_RESERVED2 0x10000000
#define CELZONE_SYNCH 0x00000200
#define CELZONE_THREAD 0x00000020
#define CELZONE_TLB 0x00000008
#define CELZONE_VIRTMEM 0x00001000

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CEL_EXTRA_PROCESS_INFO  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CEL_BOOT_TIME  [struct; ce-only] */
typedef struct _CEL_BOOT_TIME {
 DWORD dwAction;
 WCHAR szName[0];
} CEL_BOOT_TIME, *PCEL_BOOT_TIME;

/* CEL_CRITSEC_DELETE  [struct; ce-only] */
typedef struct __CEL_CRITSEC_DELETE {
 HANDLE hCS;
} CEL_CRITSEC_DELETE, *PCEL_CRITSEC_DELETE;

/* CEL_CRITSEC_ENTER  [struct; ce-only] */
typedef struct __CEL_CRITSEC_ENTER {
 HANDLE hCS; 
 HANDLE hOwnerThread; 
} CEL_CRITSEC_ENTER, *PCEL_CRITSEC_ENTER;

/* CEL_CRITSEC_INIT  [struct; ce-only] */
typedef struct __CEL_CRITSEC_INIT {
 HANDLE hCS; 
} CEL_CRITSEC_INIT, *PCEL_CRITSEC_INIT;

/* CEL_CRITSEC_LEAVE  [struct; ce-only] */
typedef struct __CEL_CRITSEC_LEAVE {
 HANDLE hCS;
 HANDLE hOwnerThread; 
} CEL_CRITSEC_LEAVE, *PCEL_CRITSEC_LEAVE;

/* CEL_DATA_LOSS  [struct; ce-only] */
typedef struct __CEL_DATA_LOSS {
 DWORD dwBytes;
} CEL_DATA_LOSS, *PCEL_DATA_LOSS;

/* CEL_EVENT_CLOSE  [struct; ce-only] */
typedef struct __CEL_EVENT_CLOSE {
 HANDLE hEvent;
} CEL_EVENT_CLOSE, *PCEL_EVENT_CLOSE;

/* CEL_EVENT_DELETE  [struct; ce-only] */
typedef struct __CEL_EVENT_DELETE {
 HANDLE hEvent; 
} CEL_EVENT_DELETE, *PCEL_EVENT_DELETE;

/* CEL_EVENT_PULSE  [struct; ce-only] */
typedef struct __CEL_EVENT_PULSE { 
 HANDLE hEvent;
} CEL_EVENT_PULSE, *PCEL_EVENT_PULSE;

/* CEL_EVENT_RESET  [struct; ce-only] */
typedef struct __CEL_EVENT_RESET { 
 HANDLE hEvent; 
} CEL_EVENT_RESET, *PCEL_EVENT_RESET;

/* CEL_EVENT_SET  [struct; ce-only] */
typedef struct __CEL_EVENT_SET { 
 HANDLE hEvent; 
} CEL_EVENT_SET, *PCEL_EVENT_SET;

/* CEL_EXTRA_MODULE_INFO  [struct; ce-only] */
typedef struct __CEL_EXTRA_MODULE_INFO {
 HANDLE hModule;
 DWORD dwVMLen;
 DWORD dwModuleFlags;
 DWORD dwOID;
 WCHAR szFullPath[0];
} CEL_EXTRA_MODULE_INFO, *PCEL_EXTRA_MODULE_INFO;

/* CEL_HEADER  [struct; ce-only] */
typedef struct __CEL_HEADER {
 DWORD Length:16;
 DWORD ID:14;
 DWORD Reserved:1;
 DWORD fTimeStamp:1;
} CEL_HEADER, *PCEL_HEADER;

/* CEL_HEAP_ALLOC  [struct; ce-only] */
typedef struct __CEL_HEAP_ALLOC {
 HANDLE hHeap;
 DWORD dwFlags;
 DWORD dwBytes;
 DWORD lpMem;
 DWORD dwTID;
 DWORD dwPID;
 DWORD dwCallerPID;
 DWORD adwStackTrace[0];
} CEL_HEAP_ALLOC, *PCEL_HEAP_ALLOC;

/* CEL_HEAP_CREATE  [struct; ce-only] */
typedef struct __CEL_HEAP_CREATE {
 DWORD dwOptions;
 DWORD dwInitSize;
 DWORD dwMaxSize;
 HANDLE hHeap;
 DWORD dwTID;
 DWORD dwPID;
} CEL_HEAP_CREATE, *PCEL_HEAP_CREATE;

/* CEL_HEAP_DESTROY  [struct; ce-only] */
typedef struct __CEL_HEAP_DESTROY {
 HANDLE hHeap;
 DWORD dwTID;
 DWORD dwPID;
} CEL_HEAP_DESTROY, *PCEL_HEAP_DESTROY;

/* CEL_HEAP_FREE  [struct; ce-only] */
typedef struct __CEL_HEAP_FREE {
 HANDLE hHeap;
 DWORD dwFlags;
 DWORD lpMem;
 DWORD dwTID;
 DWORD dwPID;
 DWORD dwCallerPID;
 DWORD adwStackTrace[0];
} CEL_HEAP_FREE, *PCEL_HEAP_FREE;

/* CEL_HEAP_REALLOC  [struct; ce-only] */
typedef struct __CEL_HEAP_REALLOC {
 HANDLE hHeap;
 DWORD dwFlags;
 DWORD dwBytes;
 DWORD lpMemOld;
 DWORD lpMem;
 DWORD dwTID;
 DWORD dwPID;
 DWORD dwCallerPID;
 DWORD adwStackTrace[0];
} CEL_HEAP_REALLOC, *PCEL_HEAP_REALLOC;

/* CEL_INT_DATA  [typedef; ce-only] */
typedef __CEL_INT_DATA {
 DWORD dwTimeStamp;
 WORD wSysIntr;
 WORD wNestingLevel;
} CEL_INT_DATA, *PCEL_INT_DATA;

/* CEL_INTERRUPTS  [struct; ce-only] */
typedef struct __CEL_INTERRUPTS {
 DWORD dwDiscarded;
 CEL_INT_DATA IntData[0];
} CEL_INTERRUPTS, *PCEL_INTERRUPTS;

/* CEL_LOG_MARKER  [struct; ce-only] */
typedef struct __CEL_LOG_MARKER {
 DWORD dwFrequency;
 DWORD dwDefaultQuantum;
 DWORD dwVersion;
} CEL_LOG_MARKER, *PCEL_LOG_MARKER;

/* CEL_MAPFILE_CREATE  [struct; ce-only] */
typedef struct __CEL_MAPFILE_CREATE { 
 HANDLE hMap;
 DWORD flProtect;
 DWORD dwMapFlags;
 DWORD dwMaxSize;
 WCHAR szName[0];
} CEL_MAPFILE_CREATE, *PCEL_MAPFILE_CREATE;

/* CEL_MAPFILE_DESTROY  [struct; ce-only] */
typedef struct __CEL_MAPFILE_DESTROY { 
 HANDLE hMap;
} CEL_MAPFILE_DESTROY , *PCEL_MAPFILE_DESTROY ;

/* CEL_MAPFILE_FLUSH  [struct; ce-only] */
typedef struct __CEL_MAPFILE_FLUSH { 
 LPVOID lpBaseAddress;
 DWORD dwLen;
 WORD wFlushFlags;
 WORD wNumPages;
} CEL_MAPFILE_FLUSH, *PCEL_MAPFILE_FLUSH;

/* CEL_MAPFILE_VIEW_CLOSE  [struct; ce-only] */
typedef struct __CEL_MAPFILE_VIEW_CLOSE { 
 HANDLE hMap;
 LPVOID lpBaseAddress;
} CEL_MAPFILE_VIEW_CLOSE, *CEL_MAPFILE_VIEW_CLOSE;
typedef CEL_MAPFILE_VIEW_CLOSE *PCEL_MAPFILE_VIEW_CLOSE, *LPCEL_MAPFILE_VIEW_CLOSE;

/* CEL_MAPFILE_VIEW_OPEN  [struct; ce-only] */
typedef struct __CEL_MAPFILE_VIEW_OPEN { 
 HANDLE hMap;
 HANDLE hProcess;
 DWORD dwDesiredAccess;
 DWORD dwFileOffset;
 DWORD dwLen;
 LPVOID lpBaseAddress;
} CEL_MAPFILE_VIEW_OPEN, *CEL_MAPFILE_VIEW_OPEN;
typedef CEL_MAPFILE_VIEW_OPEN *PCEL_MAPFILE_VIEW_OPEN, *LPCEL_MAPFILE_VIEW_OPEN;

/* CEL_MAPFLUSH_TYPE  [enum; ce-only] */
typedef enum {
 CEL_INVALID_MAPFLUSH = 0,
 CEL_FlushMapSimple = 1,
 CEL_FlushMapAtomic = 2,
 CEL_ValidateFile = 3,
 CEL_FlushMapGather = 4,
 CEL_NUM_MAPFLUSH_TYPES
} CEL_MAPFLUSH_TYPE;
typedef CEL_MAPFLUSH_TYPE *PCEL_MAPFLUSH_TYPE, *LPCEL_MAPFLUSH_TYPE;

/* CEL_MEMTRACK_BASELINE  [struct; ce-only] */
typedef struct __CEL_MEMTRACK_BASELINE {
 DWORD dwReserved;
} CEL_MEMTRACK_BASELINE, *PCEL_MEMTRACK_BASELINE;

/* CEL_MODULE_FREE  [typedef; ce-only] */
typedef __CEL_MODULE_FREE {
 HANDLE hProcess;
 HANDLE hModule;
} CEL_MODULE_FREE, *PCEL_MODULE_FREE;

/* CEL_MODULE_LOAD  [typedef; ce-only] */
typedef __CEL_MODULE_LOAD {
 HANDLE hProcess;
 HANDLE hModule;
 DWORD dwBase;
 WCHAR szName[0];
} CEL_MODULE_LOAD, *PCEL_MODULE_LOAD;

/* CEL_MUTEX_CLOSE  [struct; ce-only] */
typedef struct __CEL_MUTEX_CLOSE {
 HANDLE hMutex;
} CEL_MUTEX_CLOSE, *PCEL_MUTEX_CLOSE;

/* CEL_MUTEX_CREATE  [struct; ce-only] */
typedef struct __CEL_MUTEX_CREATE {
 HANDLE hMutex;
 WCHAR szName[0];
} CEL_MUTEX_CREATE, *PCEL_MUTEX_CREATE;

/* CEL_MUTEX_DELETE  [struct; ce-only] */
typedef struct __CEL_MUTEX_DELETE {
 HANDLE hMutex;
} CEL_MUTEX_DELETE, *PCEL_MUTEX_DELETE;

/* CEL_MUTEX_RELEASE  [typedef; ce-only] */
typedef __CEL_MUTEX_RELEASE {
 HANDLE hMutex;
} CEL_MUTEX_RELEASE, *PCEL_MUTEX_RELEASE;

/* CEL_PROCESS_CLOSE  [struct; ce-only] */
typedef struct __CEL_PROCESS_CLOSE {
 HANDLE hProcess;
} CEL_PROCESS_CLOSE, *PCEL_PROCESS_CLOSE;

/* CEL_PROCESS_CREATE  [struct; ce-only] */
typedef struct __CEL_PROCESS_CREATE {
 HANDLE hProcess;
 DWORD dwVMBase;
 WCHAR szName[0];
} CEL_PROCESS_CREATE, *PCEL_PROCESS_CREATE;

/* CEL_PROCESS_DELETE  [struct; ce-only] */
typedef struct __CEL_PROCESS_DELETE {
 HANDLE hProcess;
} CEL_PROCESS_DELETE, *PCEL_PROCESS_DELETE;

/* CEL_PROCESS_REFCOUNT  [struct; ce-only] */
typedef struct __CEL_PROCESS_REFCOUNT {
 HANDLE hProcess;
 DWORD dwRefCount
} CEL_PROCESS_REFCOUNT, *PCEL_PROCESS_REFCOUNT;

/* CEL_PROCESS_TERMINATE  [struct; ce-only] */
typedef struct __CEL_PROCESS_TERMINATE {
 HANDLE hProcess;
} CEL_PROCESS_TERMINATE, *PCEL_PROCESS_TERMINATE;

/* CEL_SEM_CLOSE  [struct; ce-only] */
typedef struct __CEL_SEM_CLOSE {
 HANDLE hSem;
} CEL_SEM_CLOSE, *PCEL_SEM_CLOSE;

/* CEL_SEM_CREATE  [struct; ce-only] */
typedef struct __CEL_SEM_CREATE {
 HANDLE hSem;
 DWORD dwInitCount;
 DWORD dwMaxCount;
 WCHAR szName[0];
} CEL_SEM_CREATE, *PCEL_SEM_CREATE;

/* CEL_SEM_DELETE  [struct; ce-only] */
typedef struct __CEL_SEM_DELETE {
 HANDLE hSem;
} CEL_SEM_DELETE, *PCEL_SEM_DELETE;

/* CEL_SEM_RELEASE  [struct; ce-only] */
typedef struct __CEL_SEM_RELEASE {
 HANDLE hSem;
 DWORD dwReleaseCount;
 DWORD dwPreviousCount;
} CEL_SEM_RELEASE, *PCEL_SEM_RELEASE;

/* CEL_SLEEP  [struct; ce-only] */
typedef struct __CEL_SLEEP {
 DWORD dwTimeout;
} CEL_SLEEP, *PCEL_SLEEP;

/* CEL_SYSTEM_INVERT  [typedef; ce-only] */
typedef __CEL_SYSTEM_INVERT {
 HANDLE hThread;
 int nPriority;
} CEL_SYSTEM_INVERT, *PCEL_SYSTEM_INVERT;

/* CEL_SYSTEM_PAGE  [typedef; ce-only] */
typedef __CEL_SYSTEM_PAGE {
 DWORD dwAddress;
 DWORD fReadWrite:1;
 DWORD fEndPageIn:1;
 DWORD fSuccess: 1
 DWORD dwReserved: 29
} CEL_SYSTEM_PAGE, *PCEL_SYSTEM_PAGE;

/* CEL_SYSTEM_TLB  [typedef; ce-only] */
typedef __CEL_SYSTEM_TLB {
 DWORD dwCount;
} CEL_SYSTEM_TLB, *PCEL_SYSTEM_TLB;

/* CEL_THREAD_CLOSE  [struct; ce-only] */
typedef struct __CEL_THREAD_CLOSE {
 HANDLE hThread;
} CEL_THREAD_CLOSE, *PCEL_THREAD_CLOSE;

/* CEL_THREAD_CREATE  [struct; ce-only] */
typedef struct __CEL_THREAD_CREATE {
 HANDLE hThread;
 HANDLE hProcess;
 HANDLE hModule;
 DWORD dwStartAddr;
 int nPriority;
 WCHAR szName[0];
} CEL_THREAD_CREATE, *PCEL_THREAD_CREATE;

/* CEL_THREAD_DELETE  [struct; ce-only] */
typedef struct __CEL_THREAD_DELETE {
 HANDLE hThread;
} CEL_THREAD_DELETE, *PCEL_THREAD_DELETE;

/* CEL_THREAD_MIGRATE  [typedef; ce-only] */
typedef __CEL_THREAD_MIGRATE {
 HANDLE hProcess;
 DWORD dwReserved;
} CEL_THREAD_MIGRATE, *PCEL_THREAD_MIGRATE;

/* CEL_THREAD_PRIORITY  [typedef; ce-only] */
typedef __CEL_THREAD_PRIORITY {
 HANDLE hThread;
 int nPriority;
} CEL_THREAD_PRIORITY, *PCEL_THREAD_PRIORITY;

/* CEL_THREAD_QUANTUM  [typedef; ce-only] */
typedef __CEL_THREAD_QUANTUM {
 HANDLE hThread;
 DWORD dwQuantum;
} CEL_THREAD_QUANTUM, *PCEL_THREAD_QUANTUM;

/* CEL_THREAD_RESUME  [struct; ce-only] */
typedef struct __CEL_THREAD_RESUME {
 HANDLE hThread; 
} CEL_THREAD_RESUME, *PCEL_THREAD_RESUME;

/* CEL_THREAD_SUSPEND  [struct; ce-only] */
typedef struct __CEL_THREAD_SUSPEND {
 HANDLE hThread; 
} CEL_THREAD_SUSPEND, *PCEL_THREAD_SUSPEND;

/* CEL_THREAD_SWITCH  [struct; ce-only] */
typedef struct __CEL_THREAD_SWITCH {
 HANDLE hThread;
} CEL_THREAD_SWITCH, *PCEL_THREAD_SWITCH;

/* CEL_THREAD_TERMINATE  [struct; ce-only] */
typedef struct __CEL_THREAD_TERMINATE {
 HANDLE hThread;
} CEL_THREAD_TERMINATE, *PCEL_THREAD_TERMINATE;

/* CEL_VIRTUAL_ALLOC  [struct; ce-only] */
typedef struct __CEL_VIRTUAL_ALLOC {
 DWORD dwResult;
 DWORD dwAddress;
 DWORD dwSize;
 DWORD dwType;
 DWORD dwProtect;
 BYTE bReserved[0];
} CEL_VIRTUAL_ALLOC, *PCEL_VIRTUAL_ALLOC;

/* CEL_VIRTUAL_COPY  [struct; ce-only] */
typedef struct __CEL_VIRTUAL_COPY {
 DWORD dwDest;
 DWORD dwSource;
 DWORD dwSize;
 DWORD dwProtect;
} CEL_VIRTUAL_COPY, *PCEL_VIRTUAL_COPY;

/* CEL_VIRTUAL_FREE  [struct; ce-only] */
typedef struct __CEL_VIRTUAL_FREE {
 DWORD dwAddress;
 DWORD dwSize;
 DWORD dwType;
 BYTE bReserved[0];
} CEL_VIRTUAL_FREE, *PCEL_VIRTUAL_FREE;

/* CEL_WAIT_MULTI  [struct; ce-only] */
typedef struct __CEL_WAIT_MULTI {
 DWORD dwTimeout;
 DWORD fWaitAll:1;
 DWORD dwReserved:31;
 HANDLE hHandles[0];
} CEL_WAIT_MULTI, *PCEL_WAIT_MULTI;

/* CEL_MODULE_REFERENCES  [struct; ce-only] */
typedef struct __CEL_MODULE_REFERENCES {
 HANDLE hModule;
 CEL_PROCESS_REFCOUNT ref[1];
} CEL_MODULE_REFERENCES, *PCEL_MODULE_REFERENCES;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 3.0..399 */

/* CeLogInit  [function; ce-only; CE 3.0..399] */
void CeLogInit (void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* CeLogData  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
void CeLogData(
 BOOL fTimeStamp, 
 WORD wID, 
 PVOID pData, 
 WORD wLen, 
 DWORD dwZoneUser, 
 DWORD dwZoneCE, 
 WORD wFlag, 
 BOOL fFlagged 
);

/* CeLogReSync  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.dll, coredll.lib] */
BOOL CeLogReSync (void);

/* CeLogSetZones  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
void CeLogSetZones(
 DWORD dwZoneUser, 
 DWORD dwZoneCE, 
 DWORD dwZoneProcess 
);

/* OEMCertifyModule  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib; heuristic-prefix] */
DWORD OEMCertifyModule(
 LPBYTE lpData, 
 DWORD cbData 
);

/* OEMCertifyModuleInit  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib; heuristic-prefix] */
BOOL OEMCertifyModuleInit( 
 LPTSTR lpModuleName 
);

/* OEMIdle  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void OEMIdle(
 DWORD dwIdleParam 
);

/* OEMInterruptHandler  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
int OEMInterruptHandler(
 unsigned int ra 
);

/* OEMInterruptHandlerFIQ  [function; ce-only; CE 3.0..399, 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void OEMInterruptHandlerFIQ (void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x600)) /* CE 3.0..599 */

/* CeLogThreadMigrate  [function; ce-only; CE 3.0..599; Coredll.lib] */
void CeLogThreadMigrate( 
 HANDLE hProcess, 
 DWORD dwReserved 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* CeLogInterrupt  [function; ce-only; CE 3.0..699; Coredll.lib, coredll.lib] */
void CeLogInterrupt(
 DWORD dwlogvalue
);

/* PerfCountSinceTick  [function; ce-only; CE 3.0..699; Nk.lib; heuristic-prefix] */
DWORD PerfCountSinceTick (void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* CeLogQueryZones  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib; heuristic-prefix] */
BOOL CeLogQueryZones(
 LPDWORD lpdwZoneUser,
 LPDWORD lpdwZoneCE,
 LPDWORD ldpwZoneProcess
);

/* InitClock  [function; ce-only; CE 4.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void InitClock (void);

/* lpNKHaltSystem  [function; ce-only; CE 4.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
extern void (*lpNKHaltSystem)(void);

/* OEMDataAbortHandler  [function; ce-only; CE 4.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void OEMDataAbortHandler(void);

/* OEMRestoreCoProcRegister  [function; ce-only; CE 4.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void OEMRestoreCoProcRegister(
 LPBYTE pArea
);

/* OEMRestoreVFPCtrlRegs  [function; ce-only; CE 4.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void OEMRestoreVFPCtrlRegs(
 LPDWORD lpExtra,
 int nMaxRegs
);

/* OEMSaveCoProcRegister  [function; ce-only; CE 4.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void OEMSaveCoProcRegister(
 LPBYTE pArea
);

/* OEMSaveVFPCtrlRegs  [function; ce-only; CE 4.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void OEMSaveVFPCtrlRegs(
 LPDWORD lpExtra,
 int nMaxRegs
);

/* pNotifyForceCleanboot  [function; ce-only; CE 4.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void pNotifyForceCleanboot(
 DWORD dwReserved1,
 DWORD dwReserved2,
 DWORD dwReserved3,
 DWORD dwReserved4
);

/* StartUp  [function; ce-only; CE 4.0..699; Nk.lib; heuristic-prefix] */
void StartUp(void);

/* TLBClear  [function; ce-only; CE 4.0..699; Nk.lib, Nkstub.lib; heuristic-prefix] */
void TLBClear(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CeLogGetZones  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeLogGetZones(
 LPDWORD lpdwZoneUser, 
 LPDWORD lpdwZoneCE, 
 LPDWORD lpdwZoneProcess,
 LPDWORD lpdwAvailableZones 
);

/* CeLogMsg  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
void CeLogMsg(
 WCHAR* format [, argument]
);

/* OEMInitCoProcRegisterSavedArea  [function; ce-only; CE 5.0..699; Nk.lib, OEMMain.lib, OEMMain_StaticKITL.lib; heuristic-prefix] */
void OEMInitCoProcRegisterSavedArea( 
 LPBYTE pArea
);

/* OEMIntrOccurs  [function; ce-only; CE 5.0..699; Nk.lib; heuristic-prefix] */
DWORD OEMIntrOccurs( 
 DWORD dwSysIntr 
);

/* OEMReschedule  [function; ce-only; CE 5.0..699; Nk.lib; heuristic-prefix] */
void OEMReschedule( 
 DWORD dwThrdId, 
 DWORD dwPrio, 
 DWORD dwQuantum, 
 DWORD dwFlags 
);
#endif /* _WIN32_WCE */

#endif /* _CELOG_ */
