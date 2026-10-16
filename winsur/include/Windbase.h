/* Windbase.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 7 constants, 47 declarations, 13 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _WINDBASE_
#define _WINDBASE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CEDB_NOCOMPRESS 0x00010000
#define CEDB_VALIDCREATE 0x0017
#define CEDB_VALIDDBFLAGS 0x0010
#define CEDB_VALIDMODTIME 0x0008
#define CEDB_VALIDNAME 0x0001
#define CEDB_VALIDSORTSPEC 0x0004
#define CEDB_VALIDTYPE 0x0002

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CEVT_AUTO_I4  [typedef; ce-only; heuristic-prefix] */

/* CEVT_AUTO_I8  [typedef; ce-only; heuristic-prefix] */

/* CEVT_BLOB  [typedef; ce-only; heuristic-prefix] */

/* CEVT_BOOL  [typedef; ce-only; heuristic-prefix] */

/* CEVT_FILETIME  [typedef; ce-only; heuristic-prefix] */

/* CEVT_I2  [typedef; ce-only; heuristic-prefix] */

/* CEVT_I4  [typedef; ce-only; heuristic-prefix] */

/* CEVT_LPWSTR  [typedef; ce-only; heuristic-prefix] */

/* CEVT_R8  [typedef; ce-only; heuristic-prefix] */

/* CEVT_RECID  [typedef; ce-only; heuristic-prefix] */

/* CEVT_STREAM  [typedef; ce-only; heuristic-prefix] */

/* CEVT_UI2  [typedef; ce-only; heuristic-prefix] */

/* CEVT_UI4  [typedef; ce-only; heuristic-prefix] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CENOTIFYREQUEST  [struct; ce-only] */
typedef struct _CENOTIFYREQUEST {
 DWORD dwSize;
 HWND hwnd; 
 DWORD dwFlags;
 HANDLE hHeap;
 DWORD dwParam;
} CENOTIFYREQUEST;
typedef CENOTIFYREQUEST *PCENOTIFYREQUEST, *LPCENOTIFYREQUEST;

/* CEPROPSPEC  [struct; ce-only; Coredll.lib, coredll.lib] */
typedef struct CEPROPSPEC {
 WORD wVersion;
 CEPROPID propid;
 DWORD dwFlags;
 LPWSTR pwszPropName;
 DWORD cchPropName;
} CEPROPSPEC;
typedef CEPROPSPEC *PCEPROPSPEC, *LPCEPROPSPEC;

/* CEVOLUMEOPTIONS  [struct; ce-only; Coredll.lib, coredll.lib] */
typedef struct CEVOLUMEOPTIONS {
 WORD wVersion;
 DWORD cbBufferPool;
 DWORD dwAutoShrinkPercent;
 DWORD dwFlushInterval;
 DWORD cMaxNotifyChanges;
 DWORD dwDefaultTimeout;
 WCHAR wszPassword[CCH_MAX_PASSWORD + 1];
 DWORD dwFlags;
} CEVOLUMEOPTIONS;
typedef CEVOLUMEOPTIONS *PCEVOLUMEOPTIONS, *LPCEVOLUMEOPTIONS;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* CeSeekDatabaseEx  [function; ce-only; CE 4.0..699; Coredll.lib, coredll.lib] */
CEOID CeSeekDatabaseEx(
 HANDLE hDatabase,
 DWORD dwSeekType, 
 DWORD dwValue, 
 WORD wNumVals,
 LPDWORD lpdwIndex
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CeEndTransaction  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeEndTransaction(
 HANDLE hSession,
 BOOL fCommit
);

/* CeGetDatabaseProps  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeGetDatabaseProps (
 HANDLE hDatabase,
 LPWORD lpcPropID,
 CEPROPID* prgPropID,
 CEPROPSPEC* prgProps
);

/* CeGetDatabaseSession  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HANDLE CeGetDatabaseSession(
 HANDLE hDatabase
);

/* CeOpenStream  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
HANDLE CeOpenStream(
 HANDLE hDatabase,
 CEPROPID propid,
 DWORD dwMode
);

/* CeSetSessionOption  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeSetSessionOption(
 HANDLE hSession,
 ULONG ulOptionId,
 DWORD dwValue
);

/* CeStreamRead  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeStreamRead(
 HANDLE hStream,
 LPBYTE lprgbBuffer,
 DWORD cbRead,
 LPDWORD lpcbRead
);

/* CeStreamSaveChanges  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeStreamSaveChanges(
 HANDLE hStream
);

/* CeStreamSeek  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeStreamSeek(
 HANDLE hStream,
 DWORD cbMove,
 DWORD dwOrigin,
 LPDWORD lpcbNewOffset
);

/* CeStreamSetSize  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeStreamSetSize(
 HANDLE hStream,
 DWORD cbSize
);

/* CeStreamWrite  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeStreamWrite(
 HANDLE hStream,
 LPBYTE lprgbBuffer,
 DWORD cbWrite,
 LPDWORD lpcbWritten
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* CeAttachCustomTrackingData  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeAttachCustomTrackingData(
 HANDLE hChangeEnum,
 CEOID oidChangeRecord,
 BYTE* rgbData,
 DWORD ccb
);

/* CeEndSyncSession  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeEndSyncSession(
 HANDLE hSession,
 DWORD dwOutcome
);

/* CeFindNextChangedRecord  [function; ce-only; CE 6.0..699; coredll.lib] */
CEOID CeFindNextChangedRecord(
 HANDLE hChangeEnum
);

/* CeGetChangedRecordCnt  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeGetChangedRecordCnt(
 HANDLE hSession,
 CEOID oidDB,
 DWORD* pdwCnt
);

/* CeGetChangedRecords  [function; ce-only; CE 6.0..699; coredll.lib] */
HANDLE CeGetChangedRecords(
 HANDLE hSession,
 CEOID oidDB,
 DWORD dwChangeType
);

/* CeGetCustomTrackingData  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeGetCustomTrackingData(
 HANDLE hChangeEnum,
 CEOID oidChangeRecord,
 BYTE* rgbData,
 DWORD* pccb
);

/* CeGetPropChangeInfo  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeGetPropChangeInfo(
 HANDLE hChangeEnum,
 CEOID oidChangeRecord,
 CEPROPID propid,
 BOOL* pfPropChanged
);

/* CeMarkRecord  [function; ce-only; CE 6.0..699; coredll.lib] */
BOOL CeMarkRecord(
 HANDLE hChangeEnum,
 CEOID oidChangeRecord,
 BOOL fChanged
);
#endif /* _WIN32_WCE */

#endif /* _WINDBASE_ */
