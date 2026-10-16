/* Partdrv.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 19 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PARTDRV_
#define _PARTDRV_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* PD_ClosePartition  [function; ce-only; CE 5.0..699] */
void PD_ClosePartition(
 DWORD dwPartitionId
);

/* PD_CloseStore  [function; ce-only; CE 5.0..699] */
void PD_CloseStore(
 DWORD dwStoreId
);

/* PD_DeletePartition  [function; ce-only; CE 5.0..699] */
DWORD PD_DeletePartition(
 DWORD dwStoreId, 
 LPCTSTR szPartName
);

/* PD_DeviceIoControl  [function; ce-only; CE 5.0..699] */
DWORD PD_DeviceIoControl(
 DWORD dwPartitionId, 
 DWORD dwCode, 
 PBYTE pInBuf, 
 DWORD nInBufSize, 
 PBYTE pOutBuf, 
 DWORD nOutBufSize, 
 PDWORD pBytesReturned
);

/* PD_FindPartitionClose  [function; ce-only; CE 5.0..699] */
void PD_FindPartitionClose(
 DWORD dwSearchId
);

/* PD_FindPartitionStart  [function; ce-only; CE 5.0..699] */
DWORD PD_FindPartitionStart(
 DWORD dwStoreId, 
 LPDWORD pdwSearchId
);

/* PD_FormatPartition  [function; ce-only; CE 5.0..699] */
DWORD PD_FormatPartition(
 DWORD dwStoreId, 
 LPCTSTR szPartName, 
 BYTE bPartType, 
 BOOL bAuto
);

/* PD_FormatStore  [function; ce-only; CE 5.0..699] */
DWORD PD_FormatStore(
 DWORD dwStoreId
);

/* PD_IsStoreFormatted  [function; ce-only; CE 5.0..699] */
DWORD PD_IsStoreFormatted(
 DWORD dwStoreId
);

/* PD_OpenPartition  [function; ce-only; CE 5.0..699] */
DWORD PD_OpenPartition(
 DWORD dwStoreId, 
 LPCTSTR szPartName, 
 LPDWORD pdwPartitionId
);

/* PD_OpenStore  [function; ce-only; CE 5.0..699] */
DWORD PD_OpenStore(
 HANDLE hDisk, 
 LPDWORD pdwStoreId
);

/* PD_RenamePartition  [function; ce-only; CE 5.0..699] */
DWORD PD_RenamePartition(
 DWORD dwStoreId, 
 LPCTSTR szOldName, 
 LPCTSTR szNewName
);

/* PD_SetPartitionAttrs  [function; ce-only; CE 5.0..699] */
DWORD PD_SetPartitionAttrs(
 DWORD dwStoreId, 
 LPCTSTR szPartName, 
 DWORD dwAttr
);
#endif /* _WIN32_WCE */

#endif /* _PARTDRV_ */
