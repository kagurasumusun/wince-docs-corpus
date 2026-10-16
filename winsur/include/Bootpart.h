/* Bootpart.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _BOOTPART_
#define _BOOTPART_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* PARTENTRY  [struct; ce-only] */
typedef struct _PARTENTRY { 
 BYTE Part_BootInd;
 BYTE Part_FirstHead;
 BYTE Part_FirstSector;
 BYTE Part_FirstTrack;
 BYTE Part_FileSystem;
 BYTE Part_LastHead; 
 BYTE Part_LastSector;
 BYTE Part_LastTrack;
 DWORD Part_StartSector;
 DWORD Part_TotalSectors;
} PARTENTRY;
typedef PARTENTRY *PPARTENTRY, *LPPARTENTRY;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* BP_GetPartitionInfo  [function; ce-only; CE 5.0..699; Bootpart.lib] */
PPARTENTRY BP_GetPartitionInfo(
 HANDLE hPartition, 
);

/* BP_LowLevelFormat  [function; ce-only; CE 5.0..699; Bootpart.lib] */
BOOL BP_LowLevelFormat(
 DWORD dwStartBlock,
 DWORD dwNumBlocks,
 DWORD dwFlags
);

/* BP_OpenPartition  [function; ce-only; CE 5.0..699; Bootpart.lib] */
HANDLE BP_OpenPartition(
 DWORD dwStartSector, 
 DWORD dwNumSectors,
 DWORD dwPartType,
 BOOL fActive,
 DWORD dwCreationFlags
);

/* BP_ReadData  [function; ce-only; CE 5.0..699; Bootpart.lib] */
BOOL BP_ReadData(
 HANDLE hPartition, 
 LPBYTE pbBuffer,
 DWORD dwLength
);

/* BP_SetDataPointer  [function; ce-only; CE 5.0..699; Bootpart.lib] */
BOOL BP_SetDataPointer(
 HANDLE hPartition, 
 DWORD dwAddress
);

/* BP_WriteData  [function; ce-only; CE 5.0..699; Bootpart.lib] */
BOOL BP_WriteData(
 HANDLE hPartition, 
 LPBYTE pbBuffer,
 DWORD dwLength
);
#endif /* _WIN32_WCE */

#endif /* _BOOTPART_ */
