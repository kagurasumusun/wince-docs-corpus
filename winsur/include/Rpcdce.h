/* Rpcdce.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 62 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RPCDCE_
#define _RPCDCE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DCE_C_ERROR_STRING_LEN 256
#define PSEC_WINNT_AUTH_IDENTITY PSEC_WINNT_AUTH_IDENTITY_W
#define RPC_C_AUTHN_DCE_PRIVATE 1
#define RPC_C_AUTHN_DCE_PUBLIC 2
#define RPC_C_AUTHN_DEC_PUBLIC 4
#define RPC_C_AUTHN_DEFAULT 0xFFFFFFFF
#define RPC_C_AUTHN_LEVEL_CALL 3
#define RPC_C_AUTHN_LEVEL_CONNECT 2
#define RPC_C_AUTHN_LEVEL_DEFAULT 0
#define RPC_C_AUTHN_LEVEL_NONE 1
#define RPC_C_AUTHN_LEVEL_PKT 4
#define RPC_C_AUTHN_LEVEL_PKT_INTEGRITY 5
#define RPC_C_AUTHN_LEVEL_PKT_PRIVACY 6
#define RPC_C_AUTHN_NONE 0
#define RPC_C_AUTHN_WINNT 10
#define RPC_C_AUTHZ_DCE 2
#define RPC_C_AUTHZ_DEFAULT 0xFFFFFFFF
#define RPC_C_AUTHZ_NAME 1
#define RPC_C_AUTHZ_NONE 0
#define RPC_C_BIND_TO_ALL_NICS 1
#define RPC_C_BINDING_DEFAULT_TIMEOUT 5
#define RPC_C_BINDING_INFINITE_TIMEOUT 10
#define RPC_C_BINDING_MAX_TIMEOUT 9
#define RPC_C_BINDING_MIN_TIMEOUT 0
#define RPC_C_CANCEL_INFINITE_TIMEOUT (-1)
#define RPC_C_EP_ALL_ELTS 0
#define RPC_C_EP_MATCH_BY_BOTH 3
#define RPC_C_EP_MATCH_BY_IF 1
#define RPC_C_EP_MATCH_BY_OBJ 2
#define RPC_C_IMP_LEVEL_ANONYMOUS 1
#define RPC_C_IMP_LEVEL_DELEGATE 4
#define RPC_C_IMP_LEVEL_IDENTIFY 2
#define RPC_C_IMP_LEVEL_IMPERSONATE 3
#define RPC_C_LISTEN_MAX_CALLS_DEFAULT 1234
#define RPC_C_MGMT_INQ_IF_IDS 0
#define RPC_C_MGMT_INQ_PRINC_NAME 1
#define RPC_C_MGMT_INQ_STATS 2
#define RPC_C_MGMT_IS_SERVER_LISTEN 3
#define RPC_C_MGMT_STOP_SERVER_LISTEN 4
#define RPC_C_PARM_BUFFER_LENGTH 2
#define RPC_C_PARM_MAX_PACKET_LENGTH 1
#define RPC_C_PROTSEQ_MAX_REQS_DEFAULT 10
#define RPC_C_QOS_CAPABILITIES_DEFAULT 0
#define RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH 0x1
#define RPC_C_QOS_IDENTITY_DYNAMIC 1
#define RPC_C_QOS_IDENTITY_STATIC 0
#define RPC_C_STATS_CALLS_IN 0
#define RPC_C_STATS_CALLS_OUT 1
#define RPC_C_STATS_PKTS_IN 2
#define RPC_C_STATS_PKTS_OUT 3
#define RPC_C_USE_INTERNET_PORT 1
#define RPC_C_USE_INTRANET_PORT 2
#define RPC_C_VERS_ALL 1
#define RPC_C_VERS_COMPATIBLE 2
#define RPC_C_VERS_EXACT 3
#define RPC_C_VERS_MAJOR_ONLY 4
#define RPC_C_VERS_UPTO 5
#define RPC_IF_AUTOLISTEN 0x0001
#define RPC_IF_OLE 2
#define RPC_MGR_EPV void
#define RPC_PROTSEQ_VECTOR RPC_PROTSEQ_VECTORW
#define SEC_WINNT_AUTH_IDENTITY SEC_WINNT_AUTH_IDENTITY_W

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SEC_WINNT_AUTH_IDENTITY  [struct; ce-only] */
typedef struct _SEC_WINNT_AUTH_IDENTITY {
 unsigned short _RPC_FAR* User;
 unsigned long UserLength;
 unsigned short _RPC_FAR* Domain;
 unsigned long DomainLength;
 unsigned long _RPC_FAR* Password;
 unsigned long PasswordLength;
 unsigned long Flags;
} SEC_WINNT_AUTH_IDENTITY, *PSEC_WINNT_AUTH_IDENTITY;

#endif /* _RPCDCE_ */
