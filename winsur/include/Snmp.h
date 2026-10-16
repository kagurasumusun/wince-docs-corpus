/* Snmp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 114 constants, 37 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _SNMP_
#define _SNMP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ASN_APPLICATION 0x40
#define ASN_BITS (ASN_UNIVERSAL
#define ASN_CONSTRUCTOR 0x20
#define ASN_CONTEXT 0x80
#define ASN_CONTEXTSPECIFIC ASN_CONTEXT
#define ASN_COUNTER32 (ASN_APPLICATION
#define ASN_COUNTER64 (ASN_APPLICATION
#define ASN_GAUGE32 (ASN_APPLICATION
#define ASN_INTEGER (ASN_UNIVERSAL
#define ASN_INTEGER32 ASN_INTEGER
#define ASN_IPADDRESS (ASN_APPLICATION
#define ASN_NULL (ASN_UNIVERSAL
#define ASN_OBJECTIDENTIFIER (ASN_UNIVERSAL
#define ASN_OCTETSTRING (ASN_UNIVERSAL
#define ASN_OPAQUE (ASN_APPLICATION
#define ASN_PRIMATIVE ASN_PRIMITIVE
#define ASN_PRIMITIVE 0x00
#define ASN_PRIVATE 0xC0
#define ASN_RFC1155_COUNTER ASN_COUNTER32
#define ASN_RFC1155_GAUGE ASN_GAUGE32
#define ASN_RFC1155_IPADDRESS ASN_IPADDRESS
#define ASN_RFC1155_OPAQUE ASN_OPAQUE
#define ASN_RFC1155_TIMETICKS ASN_TIMETICKS
#define ASN_RFC1157_GETNEXTREQUEST SNMP_PDU_GETNEXT
#define ASN_RFC1157_GETREQUEST SNMP_PDU_GET
#define ASN_RFC1157_GETRESPONSE SNMP_PDU_RESPONSE
#define ASN_RFC1157_SETREQUEST SNMP_PDU_SET
#define ASN_RFC1157_TRAP SNMP_PDU_V1TRAP
#define ASN_RFC1213_DISPSTRING ASN_OCTETSTRING
#define ASN_SEQUENCE (ASN_UNIVERSAL
#define ASN_SEQUENCEOF ASN_SEQUENCE
#define ASN_TIMETICKS (ASN_APPLICATION
#define ASN_UNIVERSAL 0x00
#define ASN_UNSIGNED32 (ASN_APPLICATION
#define DEFAULT_SNMP_PORT_IPX 36879
#define DEFAULT_SNMP_PORT_UDP 161
#define DEFAULT_SNMPTRAP_PORT_IPX 36880
#define DEFAULT_SNMPTRAP_PORT_UDP 162
#define SNMP_ACCESS_NONE 0
#define SNMP_ACCESS_NOTIFY 1
#define SNMP_ACCESS_READ_CREATE 4
#define SNMP_ACCESS_READ_ONLY 2
#define SNMP_ACCESS_READ_WRITE 3
#define SNMP_AUTHAPI_INVALID_MSG_TYPE 31
#define SNMP_AUTHAPI_INVALID_VERSION 30
#define SNMP_AUTHAPI_TRIV_AUTH_FAILED 32
#define SNMP_BERAPI_INVALID_LENGTH 10
#define SNMP_BERAPI_INVALID_OBJELEM 14
#define SNMP_BERAPI_INVALID_TAG 11
#define SNMP_BERAPI_OVERFLOW 12
#define SNMP_BERAPI_SHORT_BUFFER 13
#define SNMP_ERRORSTATUS_AUTHORIZATIONERROR 16
#define SNMP_ERRORSTATUS_BADVALUE 3
#define SNMP_ERRORSTATUS_COMMITFAILED 14
#define SNMP_ERRORSTATUS_GENERR 5
#define SNMP_ERRORSTATUS_INCONSISTENTNAME 18
#define SNMP_ERRORSTATUS_INCONSISTENTVALUE 12
#define SNMP_ERRORSTATUS_NOACCESS 6
#define SNMP_ERRORSTATUS_NOCREATION 11
#define SNMP_ERRORSTATUS_NOERROR 0
#define SNMP_ERRORSTATUS_NOSUCHNAME 2
#define SNMP_ERRORSTATUS_NOTWRITABLE 17
#define SNMP_ERRORSTATUS_READONLY 4
#define SNMP_ERRORSTATUS_RESOURCEUNAVAILABLE 13
#define SNMP_ERRORSTATUS_TOOBIG 1
#define SNMP_ERRORSTATUS_UNDOFAILED 15
#define SNMP_ERRORSTATUS_WRONGENCODING 9
#define SNMP_ERRORSTATUS_WRONGLENGTH 8
#define SNMP_ERRORSTATUS_WRONGTYPE 7
#define SNMP_ERRORSTATUS_WRONGVALUE 10
#define SNMP_EXCEPTION_ENDOFMIBVIEW (ASN_CONTEXT
#define SNMP_EXCEPTION_NOSUCHINSTANCE (ASN_CONTEXT
#define SNMP_EXCEPTION_NOSUCHOBJECT (ASN_CONTEXT
#define SNMP_EXTENSION_GET SNMP_PDU_GET
#define SNMP_EXTENSION_GET_BULK SNMP_PDU_GETBULK
#define SNMP_EXTENSION_GET_NEXT SNMP_PDU_GETNEXT
#define SNMP_EXTENSION_SET_CLEANUP (ASN_PRIVATE
#define SNMP_EXTENSION_SET_COMMIT SNMP_PDU_SET
#define SNMP_EXTENSION_SET_TEST (ASN_PRIVATE
#define SNMP_EXTENSION_SET_UNDO (ASN_PRIVATE
#define SNMP_GENERICTRAP_AUTHFAILURE 4
#define SNMP_GENERICTRAP_COLDSTART 0
#define SNMP_GENERICTRAP_EGPNEIGHLOSS 5
#define SNMP_GENERICTRAP_ENTERSPECIFIC 6
#define SNMP_GENERICTRAP_LINKDOWN 2
#define SNMP_GENERICTRAP_LINKUP 3
#define SNMP_GENERICTRAP_WARMSTART 1
#define SNMP_LOG_ERROR 2
#define SNMP_LOG_FATAL 1
#define SNMP_LOG_SILENT 0
#define SNMP_LOG_TRACE 4
#define SNMP_LOG_VERBOSE 5
#define SNMP_LOG_WARNING 3
#define SNMP_MAX_OID_LEN 128
#define SNMP_MEM_ALLOC_ERROR 1
#define SNMP_OUTPUT_TO_CONSOLE 1
#define SNMP_OUTPUT_TO_DEBUGGER 8
#define SNMP_OUTPUT_TO_EVENTLOG 4
#define SNMP_OUTPUT_TO_LOGFILE 2
#define SNMP_PDU_GET (ASN_CONTEXT
#define SNMP_PDU_GETBULK (ASN_CONTEXT
#define SNMP_PDU_GETNEXT (ASN_CONTEXT
#define SNMP_PDU_INFORM (ASN_CONTEXT
#define SNMP_PDU_REPORT (ASN_CONTEXT
#define SNMP_PDU_RESPONSE (ASN_CONTEXT
#define SNMP_PDU_SET (ASN_CONTEXT
#define SNMP_PDU_TRAP (ASN_CONTEXT
#define SNMP_PDU_V1TRAP (ASN_CONTEXT
#define SNMP_PDUAPI_INVALID_ES 21
#define SNMP_PDUAPI_INVALID_GT 22
#define SNMP_PDUAPI_UNRECOGNIZED_PDU 20
#define SNMPAPI_ERROR FALSE
#define SNMPAPI_NOERROR TRUE
#define WINSNMPAPI WINAPI

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* AsnAny  [struct, typedef; shared; snmp.lib] */
typedef struct {
 BYTE asnType;
 union {
 AsnInteger32 number;
 AsnUnsigned32 unsigned32;
 AsnCounter64 counter64;
 AsnOctetString string;
 AsnBits bits;
 AsnObjectIdentifier object;
 AsnSequence sequence;
 AsnIPAdress address;
 AsnCounter32 counter32;
 AsnGauge32 gauge;
 AsnTimeTicks ticks;
 AsnOpaque arbitrary;
 } asnValue;
} AsnAny;
typedef AsnAny *PAsnAny, *LPAsnAny;

/* AsnCounter64  [struct, typedef; ce-only; snmp.lib] */
typedef struct {
 ULONG LowPart;
 ULONG HighPart;
} AsnCounter64;
typedef AsnCounter64 *PAsnCounter64, *LPAsnCounter64;

/* AsnObjectIdentifier  [struct, typedef; shared; snmp.lib] */
typedef struct {
 UINT idLength;
 UINT* ids;
} AsnObjectIdentifier;
typedef AsnObjectIdentifier *PAsnObjectIdentifier, *LPAsnObjectIdentifier;

/* AsnOctetString  [struct, typedef; shared; snmp.lib] */
typedef struct {
 BYTE* stream;
 UINT length;
 BOOL dynamic;
} AsnOctetString;
typedef AsnOctetString *PAsnOctetString, *LPAsnOctetString;

/* SnmpVarBind  [struct, typedef; shared; snmp.lib] */
typedef struct {
 AsnObjectName name;
 AsnObjectSyntax value;
}SnmpVarBind;
typedef SnmpVarBind *PSnmpVarBind, *LPSnmpVarBind;

/* SnmpVarBindList  [struct, typedef; shared; snmp.lib] */
typedef struct {
 SnmpVarBind* list;
 UINT len;
}SnmpVarBindList;
typedef SnmpVarBindList *PSnmpVarBindList, *LPSnmpVarBindList;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* SnmpExtensionClose  [function; shared; CE 3.0..699; Snmp.lib, snmp.lib] */
VOID SnmpExtensionClose();

/* SnmpExtensionInitEx  [function; shared; CE 3.0..699; Snmp.lib, snmp.lib] */
BOOL SnmpExtensionInitEx(
 AsnObjectIdentifier* pNextSupportedRegion 
);

/* SnmpExtensionQuery  [function; shared; CE 3.0..699; Snmp.lib, snmp.lib] */
BOOL SnmpExtensionQuery( 
 BYTE bPduType, 
 SnmpVarBindList pVarBindList, 
 AsnInteger32 pErrorStatus, 
 AsnInteger32 pErrorIndex 
);

/* SnmpExtensionQueryEx  [function; shared; CE 3.0..699; Snmp.lib, snmp.lib] */
BOOL SnmpExtensionQueryEx(
 DWORD dwRequestType, 
 DWORD dwTransactionId, 
 SnmpVarBindList pVarBindList, 
 AsnOctetString pContextInfo, 
 AsnInteger32 pErrorStatus, 
 AsnInteger32 pErrorIndex 
);

/* SnmpExtensionTrap  [function; shared; CE 3.0..699; Snmp.lib, snmp.lib] */
BOOL SnmpExtensionTrap(
 AsnObjectIdentifier pEnterpriseOid, 
 AsnInteger32 pGenericTrapId, 
 AsnInteger32 pSpecificTrapId, 
 AsnTimeticks pTimeStamp, 
 SnmpVarBindList pVarBindList 
);

/* SnmpSvcGetUptime  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
DWORD SnmpSvcGetUptime();

/* SnmpSvcSetLogLevel  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
DWORD SnmpSvcSetLogLevel(
 INT nLogLevel 
);

/* SnmpSvcSetLogType  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
DWORD SnmpSvcSetLogType(
 INT nLogType 
);

/* SnmpUtilDbgPrint  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilDbgPrint(
 INT nLogLevel, 
 LPSTR szFormat 
);

/* SnmpUtilIdsToA  [function; shared; CE 3.0..699; Snmpapi.lib, snmpapi.lib] */
LPSTR SnmpUtilIdsToA(
 UINT Ids, 
 UINT IdLength 
);

/* SnmpUtilIdsToW  [function; ce-only; CE 3.0..699; Snmpapi.lib, snmpapi.lib] */
LPTSTR SnmpUtilIdsToW(
 UINT Ids, 
 UINT IdLength 
);

/* SnmpUtilMemFree  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilMemFree(
 LPVOID pMem 
);

/* SnmpUtilMemReAlloc  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
LPVOID SnmpUtilMemReAlloc(
 LPVOID pmem, 
 UINT nBytes 
);

/* SnmpUtilOctetsFree  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilOctetsFree(
 AsnOctetString* pOctetsDst 
);

/* SnmpUtilOidFree  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilOidFree(
 AsnObjectIdentifier* pOid 
);

/* SnmpUtilOidNCmp  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilOidFree(
 AsnObjectIdentifier* pOid1, 
 AsnObjectIdentifier* pOid2, 
 UINT nSubIds 
);

/* SnmpUtilOidToA  [function; shared; CE 3.0..699; Snmpapi.lib, snmpapi.lib] */
LPSTR SnmpUtilOidToA(
 AsnObjectIdentifier Oid 
);

/* SnmpUtilOidToW  [function; ce-only; CE 3.0..699; Snmpapi.lib, snmpapi.lib] */
LPTSTR SnmpUtilOidToW(
 AsnObjectIdentifier Oid 
);

/* SnmpUtilPrintToStrAsnAny  [function; ce-only; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilPrintToStrAsnAny(
 OUT TCHAR *szOut,
 AsnAny *pAny 
);

/* SnmpUtilVarBindCpy  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilVarBindCpy(
 SnmpVarBind* pVbDest, 
 SnmpVarBind* pVbSrc 
);

/* SnmpUtilVarBindFree  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilVarBindFree(
 SnmpVarBind* pVb 
);

/* SnmpUtilVarBindListCpy  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilVarBindListCpy(
 SnmpVarBindList* pVblDst,
 SnmpVarBindList* pVblSrc 
);

/* SnmpUtilVarBindListFree  [function; shared; CE 3.0..699; snmp.lib, Snmpapi.lib, snmpapi.lib] */
VOID SnmpUtilVarBindListFree(
 SnmpVarBindList* pVbl 
);
#endif /* _WIN32_WCE */

#endif /* _SNMP_ */
