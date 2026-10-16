/* Natedit.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 19 declarations, 1 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _NATEDIT_
#define _NATEDIT_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* IPRcvBuf  [struct; ce-only; Coredll.dll] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* IP_NAT_DIRECTION  [enum; ce-only; Coredll.dll] */
enum IP_NAT_DIRECTION {
 NatInboundDirection,
 NatOutboundDirection
};

/* NatOutboundDirection  [extra enum] */
enum IP_NAT_DIRECTION {  NatInboundDirection,  NatOutboundDirection};

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* CreateHandler  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.dll, coredll.dll] */
NTSTATUS CreateHandler( 
 PVOID EditorContext, 
 ULONG PrivateAddress, 
 USHORT PrivatePort, 
 ULONG PublicAddress, 
 USHORT PublicPort, 
 ULONG RemoteAddress, 
 USHORT RemotePort, 
 PVOID* EditorSessionContextp 
);

/* CreateTicket  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.dll, coredll.dll] */
NTSTATUS CreateTicket( 
 PVOID InterfaceHandle, 
 UCHAR Protocol, 
 ULONG PrivateAddress, 
 USHORT PrivatePort, 
 ULONG RemoteAddress, 
 USHORT RemotePort, 
 PULONG PublicAddress, 
 PUSHORT PublicPort 
);

/* DeleteHandler  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.dll, coredll.dll] */
NTSTATUS DeleteHandler( 
 PVOID InterfaceHandle, 
 PVOID SessionHandle, 
 PVOID EditorContext, 
 PVOID EditorSessionContext 
);

/* DeleteTicket  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.dll, coredll.dll] */
NTSTATUS DeleteTicket( 
 PVOID InterfaceHandle, 
 ULONG PublicAddress, 
 UCHAR Protocol, 
 USHORT PublicPort, 
 ULONG RemoteAddress, 
 USHORT RemotePort 
);

/* DisassociateSession  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.dll, coredll.dll] */
NTSTATUS DisassociateSession( 
 PVOID EditorHandle, 
 PVOID SessionHandle 
);

/* EditorDeregister  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.dll, coredll.dll] */
NTSTATUS EditorDeregister( 
 PVOID EditorHandle 
);

/* TimeoutSession  [function; ce-only; CE 3.0..399, 5.0..699; Coredll.dll, coredll.dll] */
NTSTATUS TimeoutSession( 
 PVOID EditorHandle, 
 PVOID SessionHandle 
);
#endif /* _WIN32_WCE */

#endif /* _NATEDIT_ */
