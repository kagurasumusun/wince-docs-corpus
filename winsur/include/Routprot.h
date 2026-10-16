/* Routprot.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 23 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ROUTPROT_
#define _ROUTPROT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define IPRTRMGR_PID 10000
#define IPX_PROTOCOL_BASE 0x0001FFFF
#define IPX_PROTOCOL_NLSP 0x00020002
#define IPX_PROTOCOL_RIP 0x00020000
#define IPX_PROTOCOL_SAP 0x00020001
#define PROTO_IP_BBN 0x0000000C
#define PROTO_IP_BGP 0x0000000E
#define PROTO_IP_BOOTP 0x0000270F
#define PROTO_IP_CISCO 0x0000000B
#define PROTO_IP_EGP 0x00000005
#define PROTO_IP_ES_IS 0x0000000A
#define PROTO_IP_GGP 0x00000006
#define PROTO_IP_HELLO 0x00000007
#define PROTO_IP_ICMP 0x00000004
#define PROTO_IP_IS_IS 0x00000009
#define PROTO_IP_LOCAL 0x00000002
#define PROTO_IP_NETMGMT 0x00000003
#define PROTO_IP_NT_AUTOSTATIC 0x00002712
#define PROTO_IP_NT_STATIC 0x00002716
#define PROTO_IP_NT_STATIC_NON_DOD 0x00002717
#define PROTO_IP_OSPF 0x0000000D
#define PROTO_IP_OTHER 0x00000001
#define PROTO_IP_RIP 0x00000008

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MIB_BEST_IF  [struct; shared] */
typedef struct _MIB_BEST_IF {
 DWORD dwDestAddr; 
 DWORD dwIfIndex; 
} MIB_BEST_IF*, PMIB_BEST_IF;

#endif /* _ROUTPROT_ */
