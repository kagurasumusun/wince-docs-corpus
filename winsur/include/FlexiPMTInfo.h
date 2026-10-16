/* FlexiPMTInfo.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 39 constants, 4 declarations, 2 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _FLEXIPMTINFO_
#define _FLEXIPMTINFO_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define mfiName 0
#define mfiUserDefined -1
#define pfiBasePtr 4
#define pfiCmdLine 7
#define pfiCurDbgZoneMasks 5
#define pfiDefaultAccessKey 3
#define pfiHandle 9
#define pfiName 6
#define pfiProcessSlot 1
#define pfiStartOfAddrSpace 2
#define pfiStructAddr 0
#define pfiTlsUsageBitMaskH 11
#define pfiTlsUsageBitMaskL 10
#define pfiTrustLevel 8
#define pfiUserDefined -1
#define tfiAddrSpaceAccessKey 2
#define tfiBasePriority 8
#define tfiCreationTimeLSW 19
#define tfiCreationTimeMSW 18
#define tfiCurrentPriority 6
#define tfiHandle 14
#define tfiHandleCurrentProcessRunIn 3
#define tfiHandleOwnerProc 10
#define tfiInfo 7
#define tfiKernelTime 12
#define tfiLastError 15
#define tfiPC 22
#define tfiQuantum 20
#define tfiQuantumLeft 21
#define tfiRunState 1
#define tfiSleepCount 4
#define tfiStackBase 16
#define tfiStackLowBound 17
#define tfiStructAddr 0
#define tfiSuspendCount 5
#define tfiTlsPtr 11
#define tfiUserDefined -1
#define tfiUserTime 13
#define tfiWaitState 9

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* FLEXI_GETDATA_TYPE  [struct; ce-only] */

/* PTM_RAW_DATA  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MODULE_FIELD_IDS  [enum; ce-only] */
typedef enum _MODULE_FIELD_IDS {
 mfiName = 0,
 mfiBasePointer,
 mfiModuleSize,
 mfiRdWrDataStart,
 mfiRdWrDataEnd,
 mfiTimeStamp,
 mfiDllHandle,
 mfiInUse,
 mfiFlags,
 mfiTrustLevel,
 mfiUserDefined = (-1L)
} MODULE_FIELD_IDS;
typedef MODULE_FIELD_IDS *PMODULE_FIELD_IDS, *LPMODULE_FIELD_IDS;

/* PROC_FIELD_IDS  [enum; ce-only] */
typedef enum _PROC_FIELD_IDS {
 pfiStructAddr = (0L),
 pfiProcessSlot = (1L),
 pfiStartOfAddrSpace = (2L),
 pfiDefaultAccessKey = (3L),
 pfiBasePtr = (4L),
 pfiCurDbgZoneMasks = (5L),
 pfiName = (6L),
 pfiCmdLine = (7L),
 pfiTrustLevel = (8L),
 pfiHandle = (9L),
 pfiTlsUsageBitMaskL = (10L),
 pfiTlsUsageBitMaskH = (11L),
 pfiUserDefined = (-1L) 
} PROC_FIELD_IDS;
typedef PROC_FIELD_IDS *PPROC_FIELD_IDS, *LPPROC_FIELD_IDS;

/* THREAD_FIELD_IDS  [enum; ce-only] */
typedef enum _THREAD_FIELD_IDS {
 tfiStructAddr = (0L),
 tfiRunState = (1L),
 tfiAddrSpaceAccessKey = (2L),
 tfiHandleCurrentProcessRunIn = (3L),
 tfiSleepCount = (4L),
 tfiSuspendCount = (5L),
 tfiCurrentPriority = (6L),
 tfiInfo = (7L),
 tfiBasePriority = (8L),
 tfiWaitState = (9L),
 tfiHandleOwnerProc = (10L),
 tfiTlsPtr = (11L),
 tfiKernelTime = (12L),
 tfiUserTime = (13L),
 tfiHandle = (14L),
 tfiLastError = (15L),
 tfiStackBase = (16L),
 tfiStackLowBound = (17L),
 tfiCreationTimeMSW = (18L),
 tfiCreationTimeLSW = (19L),
 tfiQuantum = (20L),
 tfiQuantumLeft = (21L),
 tfiPC = (22L),
 tfiUserDefined = (-1L)
} THREAD_FIELD_IDS;
typedef THREAD_FIELD_IDS *PTHREAD_FIELD_IDS, *LPTHREAD_FIELD_IDS;

#endif /* _FLEXIPMTINFO_ */
