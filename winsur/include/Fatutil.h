/* Fatutil.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 3 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _FATUTIL_
#define _FATUTIL_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* DEFRAG_PARAMS  [struct; ce-only] */

/* FORMAT_PARAMS  [struct; ce-only] */

/* SCAN_PARAMS  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FORMAT_OPTIONS  [struct; ce-only] */
typedef struct _FORMAT_OPTIONS {
 DWORD dwClusSize;
 DWORD dwRootEntries;
 DWORD dwFatVersion;
 DWORD dwNumFats;
 DWORD dwFlags;
} FORMAT_OPTIONS;
typedef FORMAT_OPTIONS *PFORMAT_OPTIONS, *LPFORMAT_OPTIONS;

/* FORMAT_RESULTS  [struct; ce-only] */
typedef struct _FORMAT_RESULTS{
 DWORD dwSectorsPerFat;
 DWORD dwReservedSectors;
 DWORD dwSectorsPerCluster;
 DWORD dwRootSectors;
 DWORD dwTotalSectors;
 DWORD dwNumFats;
 DWORD dwFatVersion;
} FORMAT_RESULTS, *PFORMAT_RESULTS;

/* SCAN_RESULTS  [struct; ce-only] */
typedef struct _SCAN_RESULTS {
 DWORD dwLostClusters;
 DWORD dwInvalidClusters;
 DWORD dwLostChains;
 DWORD dwInvalidDirs;
 DWORD dwInvalidFiles;
 DWORD dwTotalErrors;
 DWORD dwPercentFrag;
 BOOL fConsistentFats;
 BOOL fErrorNotFixed;
} SCAN_RESULTS, *PSCAN_RESULTS;

/* DEFRAG_RESULTS  [struct; ce-only] */
typedef struct _DEFRAG_RESULTS {
 SCAN_RESULTS sr;
} DEFRAG_RESULTS, *PDEFRAG_RESULTS;

#endif /* _FATUTIL_ */
