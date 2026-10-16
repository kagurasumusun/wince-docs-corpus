/* tsp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _TSP_
#define _TSP_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CALLER_ID_OPTIONS  [enum; ce-only] */
enum CALLER_ID_OPTIONS {
 CALLER_ID_DEFAULT,
 CALLER_ID_BLOCK,
 CALLER_ID_PRESENT,
};

/* CELLBEARERINFO  [struct; ce-only] */
typedef struct cellbearerinfo_tag {
 DWORD dwSpeed;
 DWORD dwService;
 DWORD dwConnectionElement;
} CELLBEARERINFO, *LPCELLBEARERINFO;

/* CELLDATACOMPINFO  [struct; ce-only] */
typedef struct celldatacompinfo_tag {
 DWORD dwDirection;
 BOOL dwRequired;
 DWORD dwMaxDictEntries;
 DWORD dwMaxStringLength;
} CELLDATACOMPINFO, *LPCELLDATACOMPINFO;

/* CELLGPRSQOSSETTINGS  [struct; ce-only] */
typedef struct cellgprsqossettings_tag {
 DWORD dwPrecedenceClass;
 DWORD dwDelayClass;
 DWORD dwReliabilityClass;
 DWORD dwPeakThruClass;
 DWORD dwMeanThruClass;
} CELLGPRSQOSSETTINGS, *LPCELLGPRSQOSSETTINGS;

/* CELLRADIOLINKINFO  [struct; ce-only] */
typedef struct cellradiolinkinfo_tag {
 DWORD dwVersion;
 DWORD dwIws;
 DWORD dwMws;
 DWORD dwAckTimer;
 DWORD dwRetransmitAttempts;
 DWORD dwResequenceTimer;
} CELLRADIOLINKINFO, *LPCELLRADIOLINKINFO;

/* LINECALLPARAMSDEVSPECIFIC  [struct; ce-only] */
typedef struct linecallparamsdevspecific_tag {
CALLER_ID_OPTIONS cidoOptions;
} LINECALLPARAMSDEVSPECIFIC, *LPLINECALLPARAMSDEVSPECIFIC;

/* CALLER_ID_PRESENT  [extra enum] */
enum CALLER_ID_OPTIONS {
  CALLER_ID_DEFAULT,
  CALLER_ID_BLOCK,
  CALLER_ID_PRESENT,
};

#endif /* _TSP_ */
