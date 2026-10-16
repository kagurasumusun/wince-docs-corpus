/* ipxrtdef.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 13 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _IPXRTDEF_
#define _IPXRTDEF_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define IPX_ADAPTER_INFO_TYPE 0x0007
#define IPX_GLOBAL_INFO_TYPE 0x0009
#define IPX_IN_TRAFFIC_FILTER_GLOBAL_INFO_TYPE 0x000B
#define IPX_IN_TRAFFIC_FILTER_INFO_TYPE 0x0006
#define IPX_INTERFACE_INFO_TYPE 0x0001
#define IPX_OUT_TRAFFIC_FILTER_GLOBAL_INFO_TYPE 0x000D
#define IPX_OUT_TRAFFIC_FILTER_INFO_TYPE 0x000C
#define IPX_ROUTE_FILTER_INFO_TYPE 0x0005
#define IPX_SERVICE_FILTER_INFO_TYPE 0x0004
#define IPX_STATIC_NETBIOS_NAME_INFO_TYPE 0x000A
#define IPX_STATIC_ROUTE_INFO_TYPE 0x0002
#define IPX_STATIC_SERVICE_INFO_TYPE 0x0003
#define IPXWAN_INTERFACE_INFO_TYPE 0x0008

#endif /* _IPXRTDEF_ */
