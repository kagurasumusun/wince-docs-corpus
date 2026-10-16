/* Iprtrmib.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 26 constants, 19 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _IPRTRMIB_
#define _IPRTRMIB_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define MAX_INTERFACE_NAME_LEN 256
#define MAXLEN_IFDESCR 256
#define MAXLEN_PHYSADDR 8
#define MIB_IPNET_TYPE_DYNAMIC 3
#define MIB_IPNET_TYPE_INVALID 2
#define MIB_IPNET_TYPE_OTHER 1
#define MIB_IPNET_TYPE_STATIC 4
#define MIB_TCP_MAXCONN_DYNAMIC ((DWORD)-1)
#define MIB_TCP_RTO_CONSTANT 2
#define MIB_TCP_RTO_OTHER 1
#define MIB_TCP_RTO_RSRE 3
#define MIB_TCP_RTO_VANJ 4
#define MIB_TCP_STATE_CLOSE_WAIT 8
#define MIB_TCP_STATE_CLOSED 1
#define MIB_TCP_STATE_CLOSING 9
#define MIB_TCP_STATE_DELETE_TCB 12
#define MIB_TCP_STATE_ESTAB 5
#define MIB_TCP_STATE_FIN_WAIT1 6
#define MIB_TCP_STATE_FIN_WAIT2 7
#define MIB_TCP_STATE_LAST_ACK 10
#define MIB_TCP_STATE_LISTEN 2
#define MIB_TCP_STATE_SYN_RCVD 4
#define MIB_TCP_STATE_SYN_SENT 3
#define MIB_TCP_STATE_TIME_WAIT 11
#define MIB_USE_CURRENT_FORWARDING ((DWORD)-1)
#define MIB_USE_CURRENT_TTL ((DWORD)-1)

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MIB_IFROW  [struct; shared] */
typedef struct _MIB_IFROW {
 WCHAR wszName[MAX_INTERFACE_NAME_LEN];
 DWORD dwIndex; 
 DWORD dwType; 
 DWORD dwMtu; 
 DWORD dwSpeed; 
 DWORD dwPhysAddrLen; 
 BYTE bPhysAddr[MAXLEN_PHYSADDR]; 
 DWORD dwAdminStatus; 
 DWORD dwOperStatus; 
 DWORD dwLastChange; 
 DWORD dwInOctets; 
 DWORD dwInUcastPkts; 
 DWORD dwInNUcastPkts; 
 DWORD dwInDiscards; 
 DWORD dwInErrors; 
 DWORD dwInUnknownProtos; 
 DWORD dwOutOctets; 
 DWORD dwOutUcastPkts; 
 DWORD dwOutNUcastPkts; 
 DWORD dwOutDiscards; 
 DWORD dwOutErrors; 
 DWORD dwOutQLen; 
 DWORD dwDescrLen; 
 BYTE bDescr[MAXLEN_IFDESCR]; 
} MIB_IFROW, *PMIB_IFROW;

/* MIB_IPADDRROW  [struct; ce-only] */
typedef struct _MIB_IPADDRROW {
 DWORD dwAddr; 
 DWORD dwIndex; 
 DWORD dwMask; 
 DWORD dwBCastAddr; 
 DWORD dwReasmSize; 
 unsigned short unused1; 
 unsigned short unused2; 
} MIB_IPADDRROW, *PMIB_IPADDRROW;

/* MIB_IPFORWARDROW  [struct; shared] */
typedef struct _MIB_IPFORWARDROW {
 DWORD dwForwardDest; 
 DWORD dwForwardMask; 
 DWORD dwForwardPolicy; 
 DWORD dwForwardNextHop; 
 DWORD dwForwardIfIndex; 
 DWORD dwForwardType; 
 DWORD dwForwardProto; 
 DWORD dwForwardAge; 
 DWORD dwForwardNextHopAS; 
 DWORD dwForwardMetric1; 
 DWORD dwForwardMetric2; 
 DWORD dwForwardMetric3; 
 DWORD dwForwardMetric4; 
 DWORD dwForwardMetric5; 
} MIB_IPFORWARDROW, *PMIB_IPFORWARDROW;

/* MIB_IPNETROW  [struct; ce-only] */
typedef struct _MIB_IPNETROW {
 DWORD dwIndex; 
 DWORD dwPhysAddrLen; 
 BYTE bPhysAddr[MAXLEN_PHYSADDR]; 
 DWORD dwAddr; 
 DWORD dwType; 
} MIB_IPNETROW, *PMIB_IPNETROW;

/* MIB_IPSTATS  [struct; ce-only] */
typedef struct _MIB_IPSTATS {
 DWORD dwForwarding; 
 DWORD dwDefaultTTL; 
 DWORD dwInReceives; 
 DWORD dwInHdrErrors; 
 DWORD dwInAddrErrors; 
 DWORD dwForwDatagrams; 
 DWORD dwInUnknownProtos; 
 DWORD dwInDiscards; 
 DWORD dwInDelivers; 
 DWORD dwOutRequests; 
 DWORD dwRoutingDiscards; 
 DWORD dwOutDiscards; 
 DWORD dwOutNoRoutes; 
 DWORD dwReasmTimeout; 
 DWORD dwReasmReqds; 
 DWORD dwReasmOks; 
 DWORD dwReasmFails; 
 DWORD dwFragOks; 
 DWORD dwFragFails; 
 DWORD dwFragCreates; 
 DWORD dwNumIf; 
 DWORD dwNumAddr; 
 DWORD dwNumRoutes; 
} MIB_IPSTATS, *PMIB_IPSTATS;

/* MIB_PROXYARP  [struct; shared] */
typedef struct _MIB_PROXYARP {
 DWORD dwAddress; 
 DWORD dwMask; 
 DWORD dwIfIndex; 
} MIB_PROXYARP, *PMIB_PROXYARP;

/* MIB_TCPROW  [struct; ce-only] */
typedef struct _MIB_TCPROW {
 DWORD dwState; 
 DWORD dwLocalAddr; 
 DWORD dwLocalPort; 
 DWORD dwRemoteAddr; 
 DWORD dwRemotePort; 
} MIB_TCPROW, *PMIB_TCPROW;

/* MIB_TCPSTATS  [struct; ce-only] */
typedef struct _MIB_TCPSTATS {
 DWORD dwRtoAlgorithm; 
 DWORD dwRtoMin; 
 DWORD dwRtoMax; 
 DWORD dwMaxConn; 
 DWORD dwActiveOpens; 
 DWORD dwPassiveOpens; 
 DWORD dwAttemptFails; 
 DWORD dwEstabResets; 
 DWORD dwCurrEstab; 
 DWORD dwInSegs; 
 DWORD dwOutSegs; 
 DWORD dwRetransSegs; 
 DWORD dwInErrs; 
 DWORD dwOutRsts; 
 DWORD dwNumConns; 
} MIB_TCPSTATS, *PMIB_TCPSTATS;

/* MIB_UDPROW  [struct; shared] */
typedef struct _MIB_UDPROW {
 DWORD dwLocalAddr; 
 DWORD dwLocalPort; 
} MIB_UDPROW, *PMIB_UDPROW;

/* MIB_UDPSTATS  [struct; shared] */
typedef struct _MIB_UDPSTATS {
 DWORD dwInDatagrams; 
 DWORD dwNoPorts; 
 DWORD dwInErrors; 
 DWORD dwOutDatagrams; 
 DWORD dwNumAddrs; 
} MIB_UDPSTATS, *PMIB_UDPSTATS;

/* MIBICMPSTATS  [struct; shared] */
typedef struct _MIBICMPSTATS {
 DWORD dwMsgs; 
 DWORD dwErrors; 
 DWORD dwDestUnreachs; 
 DWORD dwTimeExcds; 
 DWORD dwParmProbs; 
 DWORD dwSrcQuenchs; 
 DWORD dwRedirects; 
 DWORD dwEchos; 
 DWORD dwEchoReps; 
 DWORD dwTimestamps; 
 DWORD dwTimestampReps; 
 DWORD dwAddrMasks; 
 DWORD dwAddrMaskReps; 
} MIBICMPSTATS;
typedef MIBICMPSTATS *PMIBICMPSTATS, *LPMIBICMPSTATS;

/* MIBICMPINFO  [struct; shared] */
typedef struct _MIBICMPINFO {
 MIBICMPSTATS icmpInStats; 
 MIBICMPSTATS icmpOutStats; 
} MIBICMPINFO;
typedef MIBICMPINFO *PMIBICMPINFO, *LPMIBICMPINFO;

/* MIB_ICMP  [struct, typedef; shared] */
typedef struct _MIB_ICMP {
 MIBICMPINFO stats; 
} MIB_ICMP, *PMIB_ICMP;

#endif /* _IPRTRMIB_ */
