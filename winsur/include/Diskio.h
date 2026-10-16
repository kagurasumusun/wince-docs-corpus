/* Diskio.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 6 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DISKIO_
#define _DISKIO_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* SG_REQ  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DELETE_SECTOR_INFO  [struct; ce-only] */
typedef struct _DELETE_SECTOR_INFO {
 DWORD cbSize;
 DWORD startsector;
 DWORD numsectors;
} DELETE_SECTOR_INFO, *PDELETE_SECTOR_INFO;

/* DISK_COPY_EXTERNAL  [struct; ce-only] */
typedef struct _DISK_COPY_EXTERNAL {
 DWORD cbSize; 
 DWORD dwDirection; 
 PVOID pUserData; 
 DWORD cbUserDataSize; 
 TCHAR szCancelEventName[MAX_PATH];
 ULARGE_INTEGER ulFileSize;
 HANDLE hCallerProc;
 DWORD cbSectorListSize;
} DISK_COPY_EXTERNAL, *PDISK_COPY_EXTERNAL;

/* DISK_INFO  [struct; ce-only] */
typedef struct _DISK_INFO {
 DWORD di_total_sectors;
 DWORD di_bytes_per_sect;
 DWORD di_cylinders;
 DWORD di_heads;
 DWORD di_sectors;
 DWORD di_flags;
} DISK_INFO, *PDISK_INFO;

/* SECTOR_LIST_ENTRY  [struct; ce-only] */
typedef struct _SECTOR_LIST_ENTRY {
 DWORD dwStartSector; 
 DWORD dwNumSectors; 
} SECTOR_LIST_ENTRY, *PSECTOR_LIST_ENTRY;

/* SG_BUF  [struct; ce-only] */
typedef struct _SG_BUF {
 PUCHAR sb_buf;
 DWORD sb_len;
} SG_BUF, *PSG_BUF;

/* STORAGE_IDENTIFICATION  [struct; ce-only] */
typedef struct _STORAGE_IDENTIFICATION {
 DWORD dwSize;
 DWORD dwFlags;
 DWORD dwManufactureIDOffset;
 DWORD dwSerialNumOffset;
} STORAGE_IDENTIFICATION, *PSTORAGE_IDENTIFICATION;

#endif /* _DISKIO_ */
