/* Fsioctl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _FSIOCTL_
#define _FSIOCTL_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CE_REGISTRY_INFO  [struct; ce-only] */
typedef struct _CE_REGISTRY_INFO{
 DWORD cbSize;
 HKEY hRootKey;
 DWORD dwFlags;
 TCHAR *pszFullKeyName;
 LPDWORD pdwKeyNameLen;
} CE_REGISTRY_INFO, *PCE_REGISTRY_INFO;

/* FILE_ALLOCATED_RANGE_BUFFER  [struct; shared] */
typedef struct _FILE_ALLOCATED_RANGE_BUFFER{
 LARGE_INTEGER FileOffset;
 LARGE_INTEGER Length;
} FILE_ALLOCATED_RANGE_BUFFER, *PFILE_ALLOCATED_RANGE_BUFFER;

/* FILE_COPY_EXTERNAL  [struct; ce-only] */
typedef struct _FILE_COPY_EXTERNAL {
 DWORD cbSize; 
 DWORD dwDirection; 
 PVOID pUserData; 
 DWORD cbUserDataSize; 
 TCHAR szCancelEventName[MAX_PATH];
} FILE_COPY_EXTERNAL, *PFILE_COPY_EXTERNAL;

/* FILE_ZERO_DATA_INFORMATION  [struct; shared] */
typedef struct _FILE_ZERO_DATA_INFORMATION{
 LARGE_INTEGER FileOffset;
 LARGE_INTEGER BeyondFinalZero;
} FILE_ZERO_DATA_INFORMATION, *PFILE_ZERO_DATA_INFORMATION;

#endif /* _FSIOCTL_ */
