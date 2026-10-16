/* Fsdmgr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 11 constants, 85 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _FSDMGR_
#define _FSDMGR_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define FDI_CHS_UNCERTAIN 0x00000002
#define FDI_MBR 0x00000001
#define FDI_PAGEABLE 0x00000008
#define FDI_READONLY 0x00000010
#define FDI_RESERVED 0xffffffe0
#define FDI_UNFORMATTED 0x00000004
#define FSD_FLAG_LOCKFILE_SUPPORTED 0x8
#define FSD_FLAG_NETWORK 0x10
#define FSD_FLAG_TRANSACT_WRITES 0x2
#define FSD_FLAG_TRANSACTION_SAFE 0x1
#define FSD_FLAG_WFSC_SUPPORTED 0x4

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FILELOCKSTATE  [struct; ce-only; Fsdmgr.lib] */
typedef struct _FILELOCKSTATE {
 DWORD dwPosLow;
 DWORD dwPosHigh;
 DWORD dwAccess;
 LPCRITICAL_SECTION lpcs;
 BOOL fTerminal;
 HANDLE hevUnlock;
 DWORD cQueue;
 PVOID pvLockContainer;
} FILELOCKSTATE, * PFILELOCKSTATE;

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* PEMPTYLOCKCONTAINER  [callback; ce-only; CE 5.0..699; Fsdmgr.lib] */
typedef VOID(*PEMPTYLOCKCONTAINER)(
 PFILELOCKSTATE pFileLockState
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* FSDMGR_CachedRead  [function; ce-only; unified-kb; unified-kb] */
DWORD FSDMGR_CachedRead(
 DWORD dwCacheId,
 DWORD dwBlockNum,
 DWORD dwNumBlocks,
 PVOID pBuffer,
 DWORD dwReadFlags
);

/* FSDMGR_CachedWrite  [function; ce-only; unified-kb; unified-kb] */
DWORD FSDMGR_CachedWrite(
 DWORD dwCacheId,
 DWORD dwBlockNum,
 DWORD dwNumBlocks,
 PVOID pBuffer,
 DWORD dwWriteFlags
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CachedRead  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
DWORD CachedRead(
 DWORD dwCacheId, 
 DWORD dwBlockNum,
 DWORD dwNumBlocks,
 PVOID pBuffer,
 DWORD dwReadFlags
);

/* CachedWrite  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
DWORD CachedWrite(
 DWORD dwCacheId, 
 DWORD dwBlockNum,
 DWORD dwNumBlocks,
 PVOID pBuffer,
 DWORD dwWriteFlags
);

/* CacheIoControl  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
BOOL CacheIoControl(
 DWORD dwCacheId, 
 DWORD dwIoControlCode,
 LPVOID lpInbuf,
 DWORD nInBufSize,
 LPVOID lpOutBuf,
 DWORD nOutBufSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);

/* CreateCache  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
DWORD CreateCache(
 HANDLE hDsk, 
 DWORD dwStart,
 DWORD dwEnd,
 DWORD dwCacheSize,
 DWORD dwBlockSize,
 DWORD dwCreateFlags
);

/* DeleteCache  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
DWORD DeleteCache(
 DWORD dwCacheId 
);

/* FSDMGR_EmptyLockContainer  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
BOOL MyFSD_EmptyLockContainer(
 PFILELOCKSTATE pFileLockState
);

/* MyFSD_FsIoControl  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
BOOL MyFSD_FsIoControl( 
 DWORD pVol,
 DWORD dwIoControlCode,
 LPVOID lpInBuffer,
 DWORD nInBufferSize,
 LPVOID lpOutBuffer,
 DWORD nOutBufferSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);

/* MyFSD_UnLockFileEx  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
BOOL MyFSD_UnlockFileEx(
 DWORD dwFile,
 DWORD dwReserved,
 DWORD nNumberOfBytesToUnlockLow,
 DWORD nNumberOfBytesToUnlockHigh,
 LPOVERLAPPED lpOverlapped
);

/* ResizeCache  [function; ce-only; CE 5.0..699; Fsdmgr.lib] */
DWORD ResizeCache(
 DWORD dwCacheId, 
 DWORD dwSize,
 DWORD dwResizeFlags
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* FSDMGR_CacheIoControl  [function; ce-only; CE 6.0..699; Fsdmgr.lib] */
BOOL FSDMGR_CacheIoControl(
 DWORD dwCacheId,
 DWORD dwIoControlCode,
 LPVOID lpInBuf,
 DWORD nInBufSize,
 LPVOID lpOutBuf,
 DWORD nOutBufSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);

/* FSDMGR_DeleteCache  [function; ce-only; CE 6.0..699; Fsdmgr.lib] */
DWORD FSDMGR_DeleteCache(
 DWORD dwCacheId
);

/* FSDMGR_ResizeCache  [function; ce-only; CE 6.0..699; Fsdmgr.lib] */
DWORD FSDMGR_ResizeCache(
 DWORD dwCacheId,
 DWORD dwSize,
 DWORD dwResizeFlags
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL MyFSD_EmptyLockContainer( PFILELOCKSTATE pFileLockState );

#endif /* _FSDMGR_ */
