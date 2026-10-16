/* Msacmdrv.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 5 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MSACMDRV_
#define _MSACMDRV_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ACMDRVFORMATSUGGEST  [struct; ce-only] */
typedef struct { 
 DWORD cbStruct; 
 DWORD fdwSuggest; 
 LPWAVEFORMATEX pwfxSrc; 
 DWORD cbwfxSrc; 
 LPWAVEFORMATEX pwfxDst; 
 DWORD cbwfxDst;
} ACMDRVFORMATSUGGEST;
typedef ACMDRVFORMATSUGGEST *PACMDRVFORMATSUGGEST, *LPACMDRVFORMATSUGGEST;

/* ACMDRVSTREAMHEADER  [struct; ce-only] */
typedef struct {
 DWORD cbStruct; 
 DWORD fdwStatus; 
 DWORD dwUser; 
 LPBYTE pbSrc; 
 DWORD cbSrcLength; 
 DWORD cbSrcLengthUsed;
 DWORD dwSrcUser; 
 LPBYTE pbDst; 
 DWORD cbDstLength; 
 DWORD cbDstLengthUsed; 
 DWORD dwDstUser; 
 DWORD fdwConvert; 
 LPACMDRVSTREAMHEADER padshNext; 
 DWORD fdwDriver; 
 DWORD dwDriver; 
 DWORD fdwPrepared; 
 DWORD dwPrepared; 
 LPBYTE pbPreparedSrc; 
 DWORD cbPreparedSrcLength; 
 LPBYTE pbPreparedDst; 
 DWORD cbPreparedDstLength; 
} ACMDRVSTREAMHEADER;

/* ACMDRVSTREAMSIZE  [struct; ce-only] */
typedef struct {
 DWORD cbStruct;
 DWORD fdwSize;
 DWORD cbSrcLength;
 DWORD cbDstLength;
} ACMDRVSTREAMSIZE;
typedef ACMDRVSTREAMSIZE *PACMDRVSTREAMSIZE, *LPACMDRVSTREAMSIZE;

#endif /* _MSACMDRV_ */
