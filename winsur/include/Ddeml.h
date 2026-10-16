/* Ddeml.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 134 constants, 4 declarations, 0 outlines, 4 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DDEML_
#define _DDEML_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define APPCLASS_MASK 0xFL
#define APPCLASS_MONITOR 1L
#define APPCLASS_STANDARD 0
#define APPCMD_CLIENTONLY 0x10L
#define APPCMD_FILTERINITS 0x20L
#define APPCMD_MASK 0xFF0L
#define CADV_LATEACK 0xFFFF
#define CBF_FAIL_ADVISES 0x4000
#define CBF_FAIL_ALLSVRXACTIONS 0x3f000
#define CBF_FAIL_CONNECTIONS 0x2000
#define CBF_FAIL_EXECUTES 0x8000
#define CBF_FAIL_POKES 0x10000
#define CBF_FAIL_REQUESTS 0x20000
#define CBF_FAIL_SELFCONNECTIONS 0x1000
#define CBF_SKIP_ALLNOTIFICATIONS 0x3c0000
#define CBF_SKIP_CONNECT_CONFIRMS 0x40000
#define CBF_SKIP_DISCONNECTS 0x200000
#define CBF_SKIP_REGISTRATIONS 0x80000
#define CBF_SKIP_UNREGISTRATIONS 0x100000
#define CBR_BLOCK ((HDDEDATA)0xffffffff)
#define CP_WINANSI 1004
#define CP_WINUNICODE 1200
#define DDE_FACK 0x8000
#define DDE_FACKREQ 0x8000
#define DDE_FACKRESERVED (~(DDE_FACK|DDE_FBUSY|DDE_FAPPSTATUS))
#define DDE_FADVRESERVED (~(DDE_FACKREQ|DDE_FDEFERUPD))
#define DDE_FAPPSTATUS 0x00ff
#define DDE_FBUSY 0x4000
#define DDE_FDATRESERVED (~(DDE_FACKREQ|DDE_FRELEASE|DDE_FREQUESTED))
#define DDE_FDEFERUPD 0x4000
#define DDE_FNOTPROCESSED 0
#define DDE_FPOKRESERVED (~DDE_FRELEASE)
#define DDE_FRELEASE 0x2000
#define DDE_FREQUESTED 0x1000
#define DMLERR_ADVACKTIMEOUT 0x4000
#define DMLERR_BUSY 0x4001
#define DMLERR_DATAACKTIMEOUT 0x4002
#define DMLERR_DLL_NOT_INITIALIZED 0x4003
#define DMLERR_DLL_USAGE 0x4004
#define DMLERR_EXECACKTIMEOUT 0x4005
#define DMLERR_FIRST 0x4000
#define DMLERR_INVALIDPARAMETER 0x4006
#define DMLERR_LAST 0x4011
#define DMLERR_LOW_MEMORY 0x4007
#define DMLERR_MEMORY_ERROR 0x4008
#define DMLERR_NO_CONV_ESTABLISHED 0x400a
#define DMLERR_NO_ERROR 0
#define DMLERR_NOTPROCESSED 0x4009
#define DMLERR_POKEACKTIMEOUT 0x400b
#define DMLERR_POSTMSG_FAILED 0x400c
#define DMLERR_REENTRANCY 0x400d
#define DMLERR_SERVER_DIED 0x400e
#define DMLERR_SYS_ERROR 0x400f
#define DMLERR_UNADVACKTIMEOUT 0x4010
#define DMLERR_UNFOUND_QUEUE_ID 0x4011
#define DNS_FILTEROFF 8
#define DNS_FILTERON 4
#define DNS_REGISTER 1
#define DNS_UNREGISTER 2
#define EC_DISABLE ST_BLOCKED
#define EC_ENABLEALL 0
#define EC_ENABLEONE ST_BLOCKNEXT
#define EC_QUERYWAITING 2
#define EXPENTRY CALLBACK
#define HDATA_APPOWNED 1
#define MAX_MONITORS 4
#define MF_MASK 0xFF000000
#define MH_CLEANUP 4
#define MH_CREATE 1
#define MH_DELETE 3
#define MH_KEEP 2
#define MSGF_DDEMGR 0x8001
#define QID_SYNC 0xFFFFFFFF
#define ST_ADVISE 2
#define ST_BLOCKED 8
#define ST_BLOCKNEXT 128
#define ST_CLIENT 16
#define ST_CONNECTED 1
#define ST_INLIST 64
#define ST_ISLOCAL 4
#define ST_ISSELF 256
#define ST_TERMINATED 32
#define SZDDE_ITEM_ITEMLIST L"TopicItemList"
#define SZDDESYS_ITEM_FORMATS L"Formats"
#define SZDDESYS_ITEM_HELP L"Help"
#define SZDDESYS_ITEM_RTNMSG L"ReturnMessage"
#define SZDDESYS_ITEM_STATUS L"Status"
#define SZDDESYS_ITEM_SYSITEMS L"SysItems"
#define SZDDESYS_ITEM_TOPICS L"Topics"
#define SZDDESYS_TOPIC L"System"
#define TIMEOUT_ASYNC 0xFFFFFFFF
#define XCLASS_BOOL 0x1000
#define XCLASS_DATA 0x2000
#define XCLASS_FLAGS 0x4000
#define XCLASS_MASK 0xFC00
#define XCLASS_NOTIFICATION 0x8000
#define XST_ADVACKRCVD 13
#define XST_ADVDATAACKRCVD 16
#define XST_ADVDATASENT 15
#define XST_ADVSENT 11
#define XST_CONNECTED 2
#define XST_DATARCVD 6
#define XST_EXECACKRCVD 10
#define XST_EXECSENT 9
#define XST_INCOMPLETE 1
#define XST_INIT1 3
#define XST_INIT2 4
#define XST_NULL 0
#define XST_POKEACKRCVD 8
#define XST_POKESENT 7
#define XST_REQSENT 5
#define XST_UNADVACKRCVD 14
#define XST_UNADVSENT 12
#define XTYP_ADVDATA (16|XCLASS_FLAGS)
#define XTYP_ADVREQ (32|XCLASS_DATA|XTYPF_NOBLOCK)
#define XTYP_ADVSTART (0x30|XCLASS_BOOL)
#define XTYP_ADVSTOP (0x0040|XCLASS_NOTIFICATION)
#define XTYP_CONNECT (0x0060|XCLASS_BOOL|XTYPF_NOBLOCK)
#define XTYP_CONNECT_CONFIRM (0x0070|XCLASS_NOTIFICATION|XTYPF_NOBLOCK)
#define XTYP_DISCONNECT (0x00C0|XCLASS_NOTIFICATION|XTYPF_NOBLOCK)
#define XTYP_ERROR (XCLASS_NOTIFICATION|XTYPF_NOBLOCK)
#define XTYP_EXECUTE (0x0050|XCLASS_FLAGS)
#define XTYP_MASK 0xF0
#define XTYP_MONITOR (XCLASS_NOTIFICATION|XTYPF_NOBLOCK|0xF0)
#define XTYP_POKE (0x0090|XCLASS_FLAGS)
#define XTYP_REGISTER (0x00A0|XCLASS_NOTIFICATION|XTYPF_NOBLOCK)
#define XTYP_REQUEST (0x00B0|XCLASS_DATA)
#define XTYP_SHIFT 4
#define XTYP_UNREGISTER (0x00D0|XCLASS_NOTIFICATION|XTYPF_NOBLOCK)
#define XTYP_WILDCONNECT (0x00E0|XCLASS_DATA|XTYPF_NOBLOCK)
#define XTYP_XACT_COMPLETE (0x0080|XCLASS_NOTIFICATION)
#define XTYPF_ACKREQ 8
#define XTYPF_NOBLOCK 0x0002
#define XTYPF_NODATA 4

/* ==================================================================
 * base types -- fundamental Windows type definitions
 * CE-specific types are marked; verify sizes for your platform
 * ================================================================ */

/* HCOLORSPACE
 * source: win32/common/windows-data-types.md */
typedef HANDLE HCOLORSPACE;

/* HCONV
 * source: win32/common/windows-data-types.md */
typedef HANDLE HCONV;

/* HDC
 * source: win32/common/windows-data-types.md */
typedef HANDLE HDC;

/* HRSRC
 * source: win32/common/windows-data-types.md */
typedef HANDLE HRSRC;

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* HCONVLIST  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE HCONVLIST;

/* HDDEDATA  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE HDDEDATA;

/* HSZ  [typedef; shared; entity-headers; win32-reference] */
typedef HANDLE HSZ;

#endif /* _DDEML_ */
