/* ipinfoid.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 13 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _IPINFOID_
#define _IPINFOID_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define IP_DEMAND_DIAL_FILTER_INFO 0xFFFF0009
#define IP_GLOBAL_INFO 0xFFFF0003
#define IP_IFFILTER_INFO 0xFFFF000D
#define IP_IN_FILTER_INFO 0xFFFF0001
#define IP_INTERFACE_STATUS_INFO 0xFFFF0004
#define IP_IPINIP_CFG_INFO 0xFFFF000C
#define IP_MCAST_BOUNDARY_INFO 0xFFFF000B
#define IP_MCAST_HEARBEAT_INFO 0xFFFF000A
#define IP_MCAST_LIMIT_INFO 0xFFFF000E
#define IP_OUT_FILTER_INFO 0xFFFF0002
#define IP_PROT_PRIORITY_INFO 0xFFFF0006
#define IP_ROUTE_INFO 0xFFFF0005
#define IP_ROUTER_DISC_INFO 0xFFFF0007

#endif /* _IPINFOID_ */
