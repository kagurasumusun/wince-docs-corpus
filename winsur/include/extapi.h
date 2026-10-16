/* extapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 26 constants, 43 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _EXTAPI_
#define _EXTAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define LINECAPSCLASS_ALL 0x000000FF
#define LINECAPSCLASS_ASYNCDATA 0x00000020
#define LINECAPSCLASS_DATA 0x00000002
#define LINECAPSCLASS_FAX 0x00000004
#define LINECAPSCLASS_PACKET 0x00000040
#define LINECAPSCLASS_PAD 0x00000080
#define LINECAPSCLASS_SMS 0x00000008
#define LINECAPSCLASS_SYNCDATA 0x00000010
#define LINECAPSCLASS_VOICE 0x00000001
#define LINEMUTESTATE_MUTEDISABLED 0x00000002
#define LINEMUTESTATE_MUTEENABLED 0x00000001
#define LINEOPFORMAT_ALPHALONG 0x00000002
#define LINEOPFORMAT_ALPHASHORT 0x00000001
#define LINEOPFORMAT_NONE 0x00000000
#define LINEOPFORMAT_NUMERIC 0x00000004
#define LINESYSTEMTYPE_1XEVDOPACKET 0x00000040
#define LINESYSTEMTYPE_1XEVDVPACKET 0x00000080
#define LINESYSTEMTYPE_1XRTTPACKET 0x00000004
#define LINESYSTEMTYPE_EDGE 0x00000020
#define LINESYSTEMTYPE_GPRS 0x00000010
#define LINESYSTEMTYPE_GSM 0x00000008
#define LINESYSTEMTYPE_HSDPA 0x00000200
#define LINESYSTEMTYPE_IS95A 0x00000001
#define LINESYSTEMTYPE_IS95B 0x00000002
#define LINESYSTEMTYPE_NONE 0x00000000
#define LINESYSTEMTYPE_UMTS 0x00000100

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* LINE_CURRENTLINECHANGE  [macro; ce-only] */
#define LINE_CURRENTLINECHANGE
 dwParam1 = LINE_CURRENTLINECHANGE;
 dwParam2;
 dwParam3;

/* LINE_CURRENTSYSTEMCHANGE  [macro; ce-only] */
#define LINE_CURRENTSYSTEMCHANGE
 dwParam1 = LINE_CURRENTSYSTEMCHANGE;
 dwParam2;
 dwParam3;

/* LINE_GPRSCLASS  [macro; ce-only] */
#define LINE_GPRSCLASS
 dwParam1 = LINE_GPRSCLASS;
 dwParam2;
 dwParam3;

/* LINE_GPRSREGISTERSTATE  [macro; ce-only] */
#define LINE_GPRSREGISTERSTATE
 dwParam1 = LINE_GPRSREGISTERSTATE;
 dwParam2;
 dwParam3;

/* LINE_RADIOPRESENCE  [macro; ce-only] */
#define LINE_RADIOPRESENCE
 dwParam1 = LINE_RADIOPRESENCE;
 dwParam2;
 dwParam3;

/* LINE_REGISTERSTATE  [macro; ce-only] */
#define LINE_REGISTERSTATE
 dwParam1 = LINE_REGISTERSTATE;
 dwParam2;
 dwParam3;

/* LINE_USSD  [macro; ce-only] */
#define LINE_USSD
 dwParam1 = LINE_USSD;
 dwParam2;
 dwParam3;

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* LINEGENERALINFO  [struct; ce-only] */
typedef struct linegeneralinfo_tag {
 DWORD dwTotalSize;
 DWORD dwNeededSize;
 DWORD dwUsedSize;
 DWORD dwManufacturerSize;
 DWORD dwManufacturerOffset;
 DWORD dwModelSize;
 DWORD dwModelOffset;
 DWORD dwRevisionSize;
 DWORD dwRevisionOffset;
 DWORD dwSerialNumberSize;
 DWORD dwSerialNumberOffset;
 DWORD dwSubscriberNumberSize;
 DWORD dwSubscriberNumberOffset;
} LINEGENERALINFO, * LPLINEGENERALINFO;

/* LINEOPERATORSTATUS  [struct; ce-only] */
typedef struct lineoperatorstatus_tag {
 DWORD dwTotalSize;
 DWORD dwNeededSize;
 DWORD dwUsedSize;
 DWORD dwPreferredCount;
 DWORD dwPreferredSize;
 DWORD dwPreferredOffset;
 DWORD dwAvailableCount;
 DWORD dwAvailableSize;
 DWORD dwAvailableOffset;
} LINEOPERATORSTATUS, * LPLINEOPERATORSTATUS;

#endif /* _EXTAPI_ */
