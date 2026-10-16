/* Ndis.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 342 declarations, 2 outlines, 0 base types, 2 extra macros, 18 extra decls
 */
#ifndef _NDIS_
#define _NDIS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define Ndis802_11RadioPowerState_Off 0
#define Ndis802_11RadioPowerState_On 1
#define NDIS_802_11_AUTH_REQUEST_GROUP_ERROR 0x0E
#define NDIS_802_11_AUTH_REQUEST_KEYUPDATE 0x02
#define NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR 0x06
#define NDIS_802_11_AUTH_REQUEST_REAUTH 0x01
#define NDIS_802_11_PMKID_CANDIDATE_PREAUTH_ENABLED 0x01
#define NDIS_ERROR_CODE ULONG
#define NdisRingStateOpened 1

/* ==================================================================
 * macros -- supplementary #define from CE pages
 * ================================================================ */
#define NDIS_INIT_FUNCTION(_F) message("NDIS_INIT_FUNCTION Ignored")
#define NDIS_SET_ORIGINAL_PACKET(_P, _OP) NDIS_PER_PACKET_INFO_FROM_PACKET(_P, OriginalPacketInfo) = _OP

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ETH_COPY_NETWORK_ADDRESS  [function, macro; ce-only] */
#define ETH_COPY_NETWORK_ADDRESS(_D, _S) \
{ \
 *((ULONG UNALIGNED *)(_D)) = *((ULONG UNALIGNED *)(_S)); \
 *((USHORT UNALIGNED *)((UCHAR *)(_D)+4)) = *((USHORT UNALIGNED *)((UCHAR *)(_S)+4)); \
}

/* NDIS_BUFFER_TO_SPAN_PAGES  [function, macro; ce-only] */
ULONG NDIS_BUFFER_TO_SPAN_PAGES( 
IN PNDIS_BUFFER Buffer );

/* NDIS_GET_ORIGINAL_PACKET  [macro, function; ce-only] */
PNDIS_PACKET NDIS_GET_ORIGINAL_PACKET(
 PNDIS_PACKET _P
);

/* NDIS_GET_PACKET_CANCEL_ID  [macro, function; ce-only] */
PVOID NDIS_GET_PACKET_CANCEL_ID(
 PNDIS_PACKET _P
);

/* NDIS_GET_PACKET_HEADER_SIZE  [macro, function; ce-only] */
#define NDIS_GET_PACKET_HEADER_SIZE(_Packet) \
((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) + \
(_Packet)->Private.NdisPacketOobOffset))->HeaderSize

/* NDIS_GET_PACKET_STATUS  [macro, function; ce-only] */
#define NDIS_GET_PACKET_STATUS(_Packet) \
 ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) + \
 (_Packet)->Private.NdisPacketOobOffset))->Status

/* NDIS_GET_PACKET_TIME_RECEIVED  [macro, function; ce-only] */
#define NDIS_GET_PACKET_TIME_RECEIVED(_Packet) \
 ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) + \
 (_Packet)->Private.NdisPacketOobOffset))->TimeReceived

/* NDIS_GET_PACKET_TIME_SENT  [macro, function; ce-only] */
ULONGLONG NDIS_GET_PACKET_TIME_SENT(
 PNDIS_PACKET _Packet
);

/* NDIS_GET_PACKET_TIME_TO_SEND  [function, macro; ce-only] */
#define NDIS_GET_PACKET_TIME_SENT(_Packet) \
 ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) + \
 (_Packet)->Private.NdisPacketOobOffset))->TimeSent

/* NDIS_OOB_DATA_FROM_PACKET  [macro, function; ce-only] */
PNDIS_PACKET_OOB_DATA NDIS_OOB_DATA_FROM_PACKET(
 PNDIS_PACKET _P
);

/* NDIS_PACKET_EXTENSION_FROM_PACKET  [macro, function; ce-only] */
PNDIS_PACKET_EXTENSION NDIS_PACKET_EXTENSION_FROM_PACKET(
 PNDIS_PACKET _P
);

/* NDIS_PHYSICAL_ADDRESS_CONST  [function, macro; ce-only] */
VOID NDIS_PHYSICAL_ADDRESS_CONST( 
IN ULONG Low, 
IN LONG High );

/* NDIS_SET_PACKET_CANCEL_ID  [macro, function; ce-only] */
ULONG_PTR NDIS_SET_PACKET_CANCEL_ID(
 PNDIS_PACKET _P,
 ULONG_PTR _cId
);

/* NDIS_WORK_ITEM  [struct; ce-only] */

/* TR_COMPARE_NETWORK_ADDRESSES  [macro, function; ce-only] */
#define TR_COMPARE_NETWORK_ADDRESSES(_A, _B, _Result) \
{ \
 if (*(ULONG UNALIGNED *)&(_A)[2] > \
 *(ULONG UNALIGNED *)&(_B)[2]) \
 { \
 *(_Result) = 1; \
 } \
 else if (*(ULONG UNALIGNED *)&(_A)[2] < \
 *(ULONG UNALIGNED *)&(_B)[2]) \
 { \
 *(_Result) = (UINT)-1; \
 } \
 else if (*(USHORT UNALIGNED *)(_A) > \
 *(USHORT UNALIGNED *)(_B)) \
 { \
 *(_Result) = 1; \
 } \
 else if (*(USHORT UNALIGNED *)(_A) < \
 *(USHORT UNALIGNED *)(_B)) \
 { \
 *(_Result) = (UINT)-1; \
 } \
 else \
 { \
 *(_Result) = 0; \
 } \
}

/* TR_COPY_NETWORK_ADDRESS  [macro, function; ce-only] */
VOID TR_COPY_NETWORK_ADDRESS(
 PCHAR _D,
 PCHAR _S
);

/* TR_IS_BROADCAST  [macro, function; ce-only] */
VOID TR_IS_BROADCAST(
 PUCHAR _Address,
 PBOOLEAN _Result
);

/* TR_IS_FUNCTIONAL  [macro, function; ce-only] */
VOID TR_IS_FUNCTIONAL(
 PUCHAR _Address,
 PBOOLEAN _Result
);

/* TR_IS_GROUP  [macro, function; ce-only] */
VOID TR_IS_GROUP(
 PUCHAR _Address,
 PBOOLEAN _Result
);

/* TR_IS_NOT_DIRECTED  [macro, function; ce-only] */
#define TR_IS_NOT_DIRECTED(_Address, _Result) \
{ \
 *(_Result) = (BOOLEAN)((_Address)[0] & 0x80); \
}

/* TR_IS_SOURCE_ROUTING  [macro, function; ce-only] */
#define TR_IS_SOURCE_ROUTING(_Address, _Result) \
{ \
 *(_Result) = (BOOLEAN)((_Address)[0] & 0x80); \
}

/* XXX_Init  [function, macro; ce-only; Ndislib.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* NDIS_HANDLE  [typedef; ce-only] */
typedef 
PVOID NDIS_HANDLE,
*PNDIS_HANDLE;

/* NDIS_INTERFACE_TYPE  [enum; ce-only] */
typedef enum _NDIS_INTERFACE_TYPE {
 NdisInterfaceInternal = Internal,
 NdisInterfaceIsa = Isa,
 NdisInterfaceEisa = Eisa,
 NdisInterfaceMca = MicroChannel,
 NdisInterfaceTurboChannel = TurboChannel,
 NdisInterfacePci = PCIBus,
 NdisInterfacePcMcia = PCMCIABus,
 NdisInterfaceCBus = CBus,
 NdisInterfaceMPIBus = MPIBus,
 NdisInterfaceMPSABus = MPSABus,
 NdisInterfaceProcessorInternal = ProcessorInternal,
 NdisInterfaceInternalPowerBus = InternalPowerBus,
 NdisInterfacePNPISABus = PNPISABus,
 NdisInterfacePNPBus = PNPBus,
 NdisMaximumInterfaceType,
} NDIS_INTERFACE_TYPE, *PNDIS_INTERFACE_TYPE;

/* NDIS_MAC_FRAGMENT  [struct; ce-only] */
typedef struct _NDIS_MAC_FRAGMENT {
 NDIS_HANDLE 
 NdisLinkContext
 ;
 ULONG
 Errors
 ;
 } NDIS_MAC_FRAGMENT, *PNDIS_MAC_FRAGMENT;

/* NDIS_MAC_LINE_DOWN  [struct; ce-only] */
typedef struct _NDIS_MAC_LINE_DOWN {
 NDIS_HANDLE NdisLinkContext;
} NDIS_MAC_LINE_DOWN, *PNDIS_MAC_LINE_DOWN;

/* NDIS_OID  [typedef; ce-only] */
typedef 
ULONG NDIS_OID, 
*PNDIS_OID;

/* NDIS_PACKET_EXTENSION  [struct; ce-only] */
typedef struct _NDIS_PACKET_EXTENSION {
 PVOID NdisPacketInfo[MaxPerPacketInfo];
} NDIS_PACKET_EXTENSION, *PNDIS_PACKET_EXTENSION;

/* NDIS_PACKET_STACK  [struct; ce-only] */
typedef struct _NDIS_PACKET_STACK {
 ULONG_PTR IMReserved[2];
 ULONG_PTR NdisReserved[4];
} NDIS_PACKET_STACK, *PNDIS_PACKET_STACK;

/* NDIS_PARAMETER_TYPE  [enum; ce-only] */
typedef enum _NDIS_PARAMETER_TYPE {
 NdisParameterInteger,
 NdisParameterHexInteger,
 NdisParameterString,
 NdisParameterMultiString,
 NdisParameterBinary,
} NDIS_PARAMETER_TYPE, *PNDIS_PARAMETER_TYPE;

/* NDIS_PHYSICAL_ADDRESS  [typedef; ce-only] */
typedef
PHYSICAL_ADDRESS NDIS_PHYSICAL_ADDRESS, 
*PNDIS_PHYSICAL_ADDRESS;

/* NDIS_PROC  [struct; ce-only] */
typedef
VOID (*NDIS_PROC) (
 struct _NDIS_WORK_ITEM *,
 PVOID
);

/* NDIS_STATUS  [typedef; ce-only] */
typedef 
int NDIS_STATUS, 
*PNDIS_STATUS;

/* NDIS_TASK_TCP_IP_CHECKSUM  [struct; ce-only] */
typedef struct _NDIS_TASK_TCP_IP_CHECKSUM {
 struct {
 ULONG IpOptionsSupported;
 ULONG TcpOptionsSupported;
 ULONG TcpChecksum;
 ULONG UdpChecksum;
 ULONG IpChecksum;
 } V4Transmit;
 struct {
 ULONG IpOptionsSupported;
 ULONG TcpOptionsSupported;
 ULONG TcpChecksum;
 ULONG UdpChecksum;
 ULONG IpChecksum;
 } V4Receive;
 struct {
 ULONG IpOptionsSupported;
 ULONG TcpOptionsSupported;
 ULONG TcpChecksum;
 ULONG UdpChecksum;
 } V6Transmit;
 struct {
 ULONG IpOptionsSupported;
 ULONG TcpOptionsSupported;
 ULONG TcpChecksum;
 ULONG UdpChecksum;
 } V6Receive;
} NDIS_TASK_TCP_IP_CHECKSUM, *PNDIS_TASK_TCP_IP_CHECKSUM;

/* NDIS_TASK_TCP_LARGE_SEND  [struct; ce-only] */
typedef struct _NDIS_TASK_TCP_LARGE_SEND {
 ULONG Version;
 ULONG MaxOffLoadSize;
 ULONG MinSegmentCount;
 BOOLEAN TcpOptions;
 BOOLEAN IpOptions;
} NDIS_TASK_TCP_LARGE_SEND, *PNDIS_TASK_TCP_LARGE_SEND;

/* NDIS_TCP_IP_CHECKSUM_PACKET_INFO  [struct; ce-only] */
typedef struct _NDIS_TCP_IP_CHECKSUM_PACKET_INFO {
union {
 struct { 
 ULONG NdisPacketChecksumV4:1;
 ULONG NdisPacketChecksumV6:1;
 ULONG NdisPacketTcpChecksum:1;
 ULONG NdisPacketUdpChecksum:1;
 ULONG NdisPacketIpChecksum:1;
 } Transmit;
 struct {
 ULONG NdisPacketTcpChecksumFailed:1;
 ULONG NdisPacketUdpChecksumFailed:1;
 ULONG NdisPacketIpChecksumFailed:1;
 ULONG NdisPacketTcpChecksumSucceeded:1;
 ULONG NdisPacketUdpChecksumSucceeded:1;
 ULONG NdisPacketIpChecksumSucceeded:1;
 ULONG NdisPacketLoopback:1;
 } Receive;
 ULONG Value;
};
} NDIS_TCP_IP_CHECKSUM_PACKET_INFO, *PNDIS_TCP_IP_CHECKSUM_PACKET_INFO;

/* NDIS_WAN_COMPRESS_INFO  [struct; ce-only] */
typedef struct _NDIS_WAN_COMPRESS_INFO { 
 UCHAR SessionKey[8]; 
 ULONG MSCompType; 
 UCHAR CompType; 
 USHORT CompLength; 
 union { 
 struct { 
 UCHAR CompOUI[3]; 
 UCHAR CompSubType; 
 UCHAR CompValues[32]; 
 } Proprietary; 
 struct { 
 UCHAR CompValues[32]; 
 } Public; 
 }; 
} NDIS_WAN_COMPRESS_INFO;
typedef NDIS_WAN_COMPRESS_INFO *PNDIS_WAN_COMPRESS_INFO, *LPNDIS_WAN_COMPRESS_INFO;

/* NDIS_WAN_GET_COMP_INFO  [struct; ce-only] */
typedef struct _NDIS_WAN_GET_COMP_INFO { 
 NDIS_HANDLE NdisLinkHandle; 
 NDIS_WAN_COMPRESS_INFO SendCapabilities; 
 NDIS_WAN_COMPRESS_INFO RecvCapabilities; 
} NDIS_WAN_GET_COMP_INFO, *PNDIS_WAN_GET_COMP_INFO;

/* NDIS_WAN_GET_LINK_INFO  [struct; ce-only] */
typedef struct _NDIS_WAN_GET_LINK_INFO { 
 NDIS_HANDLE NdisLinkHandle; 
 ULONG MaxSendFrameSize; 
 ULONG MaxRecvFrameSize; 
 ULONG HeaderPadding; 
 ULONG TailPadding; 
 ULONG SendFramingBits; 
 ULONG RecvFramingBits; 
 ULONG SendCompressionBits; 
 ULONG RecvCompressionBits; 
 ULONG SendACCM; 
 ULONG RecvACCM; 
} NDIS_WAN_GET_LINK_INFO, *PNDIS_WAN_GET_LINK_INFO;

/* NDIS_WAN_GET_STATS_INFO  [struct; ce-only] */
typedef struct _NDIS_WAN_GET_STATS_INFO { 
 NDIS_HANDLE NdisLinkHandle; 
 ULONG BytesSent; 
 ULONG BytesRcvd; 
 ULONG FramesSent; 
 ULONG FramesRcvd; 
 ULONG CRCErrors; 
 ULONG TimeoutErrors; 
 ULONG AlignmentErrors; 
 ULONG SerialOverrunErrors; 
 ULONG FramingErrors; 
 ULONG BufferOverrunErrors; 
 ULONG BytesTransmittedUncompressed; 
 ULONG BytesReceivedUncompressed; 
 ULONG BytesTransmittedCompressed; 
 ULONG BytesReceivedCompressed; 
} NDIS_WAN_GET_STATS_INFO, *PNDIS_WAN_GET_STATS_INFO;

/* NDIS_WAN_INFO  [struct; ce-only] */
typedef struct _NDIS_WAN_INFO {
 ULONG MaxFrameSize; 
 ULONG MaxTransmit; 
 ULONG HeaderPadding; 
 ULONG TailPadding; 
 ULONG Endpoints; 
 UINT MemoryFlags; 
 NDIS_PHYSICAL_ADDRESS HighestAcceptableAddress; 
 ULONG FramingBits; 
 ULONG DesiredACCM; 
} NDIS_WAN_INFO, *PNDIS_WAN_INFO;

/* NDIS_WAN_LINE_DOWN  [struct; ce-only] */
typedef struct _NDIS_WAN_LINE_DOWN {
 UCHAR RemoteAddress[6];
 UCHAR LocalAddress[6];
} NDIS_WAN_LINE_DOWN, *PNDIS_WAN_LINE_DOWN;

/* NDIS_WAN_SET_COMP_INFO  [struct; ce-only] */
typedef struct _NDIS_WAN_SET_COMP_INFO { 
 NDIS_HANDLE NdisLinkHandle; 
 NDIS_WAN_COMPRESS_INFO SendCapabilities; 
 NDIS_WAN_COMPRESS_INFO RecvCapabilities; 
} NDIS_WAN_SET_COMP_INFO, *PNDIS_WAN_SET_COMP_INFO;

/* NDIS_WAN_SET_LINK_INFO  [struct; ce-only] */
typedef struct _NDIS_WAN_SET_LINK_INFO { 
 NDIS_HANDLE NdisLinkHandle; 
 ULONG MaxSendFrameSize; 
 ULONG MaxRecvFrameSize; 
 ULONG HeaderPadding; 
 ULONG TailPadding; 
 ULONG SendFramingBits; 
 ULONG RecvFramingBits; 
 ULONG SendCompressionBits; 
 ULONG RecvCompressionBits; 
 ULONG SendACCM; 
 ULONG RecvACCM; 
} NDIS_WAN_SET_LINK_INFO, *PNDIS_WAN_SET_LINK_INFO;

/* NETWORK_ADDRESS  [struct; ce-only] */
typedef struct _NETWORK_ADDRESS {
 USHORT AddressLength; 
 USHORT AddressType; 
 UCHAR Address[1]; 
} NETWORK_ADDRESS, *PNETWORK_ADDRESS;

/* NETWORK_ADDRESS_LIST  [struct; ce-only] */
typedef struct _NETWORK_ADDRESS_LIST {
 LONG AddressCount; 
 USHORT AddressType; 
 NETWORK_ADDRESS Address[1]; 
} NETWORK_ADDRESS_LIST, *PNETWORK_ADDRESS_LIST;

/* TRANSPORT_HEADER_OFFSET  [struct; ce-only] */
typedef struct _TRANSPORT_HEADER_OFFSET {
 USHORT ProtocolType; 
 USHORT HeaderOffset; 
} TRANSPORT_HEADER_OFFSET, *PTRANSPORT_HEADER_OFFSET;

/* NDIS_PACKET_OOB_DATA  [struct; ce-only] */
typedef struct _NDIS_PACKET_OOB_DATA {
 union {
 ULONGLONG TimeToSend;
 ULONGLONG TimeSent;
 };
 ULONGLONG TimeReceived;
 UINT HeaderSize;
 UINT SizeMediaSpecificInfo;
 PVOID MediaSpecificInformation;
 NDIS_STATUS Status;
} NDIS_PACKET_OOB_DATA, *PNDIS_PACKET_OOB_DATA;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210)) /* CE 2.0..209 */

/* NdisMInitizlizeWrapper  [function; ce-only; CE 2.0..209] */
VOID NdisMInitializeWrapper(OUT PNDIS_HANDLE NdisWrapperHandle, IN PVOID SystemSpecific1, IN PVOID SystemSpecific2, 
IN PVOID SystemSpecific3);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 2.0..209, 2.11..2.12, 3.0..399 */

/* ARGUMENT_PRESENT  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399] */
BOOLEAN ARGUMENT_PRESENT( 
IN (CHAR *) ArgumentPointer );

/* KdBreakPoint  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399] */
VOID KdBreakPoint();

/* KdPrint  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399] */
VOID KdPrint(LPSTR *lpszString);

/* NdisQueryMapRegisterCount  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399; Ndislib.lib] */
NDIS_STATUS NdisQueryMapRegisterCount( 
IN NDIS_INTERFACE_TYPE BusType, 
OUT PUINT MapRegisterCount );

/* NdisResetComplete  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399] */
VOID NdisReset(OUT PNDIS_STATUS Status, 
IN NDIS_HANDLE NdisBindingHandle );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699 */

/* NdisMDeregisterIoPortRange  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMDeregisterIoPortRange(
 NDIS_HANDLE MiniportAdapterHandle,
 UINT InitialPort,
 UINT NumberOfPorts,
 PVOID PortOffset
);

/* NdisMMapIoSpace  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
NDIS_STATUS NdisMMapIoSpace(
 PVOID* VirtualAddress,
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_PHYSICAL_ADDRESS PhysicalAddress,
 UINT Length
);

/* NdisMQueryInformationComplete  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMQueryInformationComplete(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_STATUS Status
);

/* NdisMRegisterIoPortRange  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
NDIS_STATUS NdisMRegisterIoPortRange(
 PVOID* PortOffset,
 NDIS_HANDLE MiniportAdapterHandle,
 UINT InitialPort,
 UINT NumberOfPorts
);

/* NdisMResetComplete  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMResetComplete(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_STATUS Status,
 BOOLEAN AddressingReset
);

/* NdisMSendResourcesAvailable  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMSendResourcesAvailable(
 NDIS_HANDLE MiniportAdapterHandle
);

/* NdisMSetAttributes  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMSetAttributes(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_HANDLE MiniportAdapterContext,
 BOOLEAN BusMaster,
 NDIS_INTERFACE_TYPE AdapterType
);

/* NdisMSetAttributesEx  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMSetAttributesEx(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_HANDLE MiniportAdapterContext,
 UINT CheckForHangTimeInSeconds,
 ULONG AttributeFlags,
 NDIS_INTERFACE_TYPE AdapterType
);

/* NdisMSetInformationComplete  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMSetInformationComplete(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_STATUS Status
);

/* NdisMSleep  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMSleep(
 ULONG MicrosecondsToSleep
);

/* NdisMUnmapIoSpace  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMUnmapIoSpace(
 NDIS_HANDLE MiniportAdapterHandle,
 PVOID VirtualAddress,
 UINT Length
);

/* NdisMUpdateSharedMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMUpdateSharedMemory(
 NDIS_HANDLE MiniportAdapterHandle,
 ULONG Length,
 PVOID VirtualAddress,
 NDIS_PHYSICAL_ADDRESS PhysicalAddress
);

/* NdisOpenConfiguration  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisOpenConfiguration(
 PNDIS_STATUS Status,
 PNDIS_HANDLE ConfigurationHandle,
 NDIS_HANDLE WrapperConfigurationContext
);

/* NdisRawReadPortBufferUchar  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawReadPortBufferUchar(
 ULONG Port,
 PUCHAR Buffer,
 ULONG Length
);

/* NdisRawReadPortBufferUlong  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawReadPortBufferUlong(
 ULONG Port,
 PULONG Buffer,
 ULONG Length
);

/* NdisRawReadPortBufferUshort  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawReadPortBufferUshort(
 ULONG Port,
 PUSHORT Buffer,
 ULONG Length
);

/* NdisRawReadPortUchar  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawReadPortUchar(
 ULONG Port,
 PUCHAR Data
);

/* NdisRawReadPortUlong  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawReadPortUlong(
 ULONG Port,
 PULONG Data
);

/* NdisRawReadPortUshort  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawReadPortUshort(
 ULONG Port,
 PUSHORT Data
);

/* NdisRawWritePortBufferUchar  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawWritePortBufferUchar(
 ULONG Port,
 PUCHAR Buffer,
 ULONG Length
);

/* NdisRawWritePortBufferUlong  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawWritePortBufferUlong(
 ULONG Port,
 PULONG Buffer,
 ULONG Length
);

/* NdisRawWritePortBufferUshort  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawWritePortBufferUshort(
 ULONG Port,
 PUSHORT Buffer,
 ULONG Length
);

/* NdisRawWritePortUchar  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawWritePortUchar(
 ULONG Port,
 UCHAR Data
);

/* NdisRawWritePortUlong  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawWritePortUlong(
 ULONG Port,
 ULONG Data
);

/* NdisRawWritePortUshort  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisRawWritePortUshort(
 ULONG Port,
 USHORT Data
);

/* NdisReadNetworkAddress  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisReadNetworkAddress(
 PNDIS_STATUS Status,
 PVOID* NetworkAddress,
 PUINT NetworkAddressLength,
 NDIS_HANDLE ConfigurationHandle
);

/* NdisReadPciSlotInformation  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
ULONG NdisReadPciSlotInformation(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG SlotNumber,
 ULONG Offset,
 PVOID Buffer,
 ULONG Length
);

/* NdisReset  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisReset(
 PNDIS_STATUS Status,
 NDIS_HANDLE NdisBindingHandle
);

/* NdisSetPhysicalAddressHigh  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisSetPhysicalAddressHigh(
 NDIS_PHYSICAL_ADDRESS PhysicalAddress,
 ULONG Value
);

/* NdisSetPhysicalAddressLow  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisSetPhysicalAddressLow(
 NDIS_PHYSICAL_ADDRESS PhysicalAddress,
 ULONG Value
);

/* NdisStallExecution  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisStallExecution(
 UINT MicrosecondsToStall
);

/* NdisTerminateWrapper  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisTerminateWrapper(
 NDIS_HANDLE NdisWrapperHandle,
 PVOID SystemSpecific
);

/* NdisWritePciSlotInformation  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
ULONG NdisWritePciSlotInformation(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG SlotNumber,
 ULONG Offset,
 PVOID Buffer,
 ULONG Length
);

/* NdisZeroMappedMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisZeroMappedMemory(
 PVOID Destination,
 ULONG Length
);

/* NdisZeroMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..399, 5.0..699; Ndislib.lib] */
VOID NdisZeroMemory(
 PVOID Destination,
 ULONG Length
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x200 && _WIN32_WCE < 0x210) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.0..209, 2.11..2.12, 3.0..699 */

/* NdisAllocateBufferPool  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
VOID NdisAllocateBufferPool(
 PNDIS_STATUS Status,
 PNDIS_HANDLE PoolHandle,
 UINT NumberOfDescriptors
);

/* NdisAllocateMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
NDIS_STATUS NdisAllocateMemory(
 PVOID* VirtualAddress,
 UINT Length,
 UINT MemoryFlags,
 NDIS_PHYSICAL_ADDRESS HighestAcceptableAddress
);

/* NdisAllocatePacketPool  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
VOID NdisAllocatePacketPool(
 PNDIS_STATUS Status,
 PNDIS_HANDLE PoolHandle,
 UINT NumberOfDescriptors,
 UINT ProtocolReservedLength
);

/* NdisCloseAdapter  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
VOID NdisCloseAdapter(
 PNDIS_STATUS Status,
 NDIS_HANDLE NdisBindingHandle
);

/* NdisCloseConfiguration  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
VOID NdisCloseConfiguration(
 NDIS_HANDLE ConfigurationHandle
);

/* NdisDeregisterProtocol  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
VOID NdisDeregisterProtocol(
 PNDIS_STATUS Status,
 NDIS_HANDLE NdisProtocolHandle
);

/* NdisFreeBufferPool  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
VOID NdisFreeBufferPool(
 NDIS_HANDLE PoolHandle
);

/* NdisFreeMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
VOID NdisFreeMemory(
 PVOID VirtualAddress,
 UINT Length,
 UINT MemoryFlags
);

/* NdisFreePacketPool  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
VOID NdisFreePacketPool(
 NDIS_HANDLE PoolHandle
);

/* NdisGetPhysicalAddressHigh  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
ULONG NdisGetPhysicalAddressHigh(
 NDIS_PHYSICAL_ADDRESS PhysicalAddress
);

/* NdisGetPhysicalAddressLow  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
ULONG NdisGetPhysicalAddressLow(
 NDIS_PHYSICAL_ADDRESS PhysicalAddress
);

/* NdisMDeregisterAdapterShutdownHandler  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMDeregisterAdapterShutdownHandler(
 NDIS_HANDLE MiniportHandle
);

/* NdisMEthIndicateReceive  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMEthIndicateReceive(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_HANDLE MiniportReceiveContext,
 PVOID HeaderBuffer,
 UINT HeaderBufferSize,
 PVOID LookaheadBuffer,
 UINT LookaheadBufferSize,
 UINT PacketSize
);

/* NdisMEthIndicateReceiveComplete  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMEthIndicateReceiveComplete(
 NDIS_HANDLE MiniportAdapterHandle
);

/* NdisMIndicateStatus  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMIndicateStatus(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_STATUS GeneralStatus,
 PVOID StatusBuffer,
 UINT StatusBufferSize
);

/* NdisMIndicateStatusComplete  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMIndicateStatusComplete(
 NDIS_HANDLE MiniportAdapterHandle
);

/* NdisMoveFromMappedMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMoveFromMappedMemory(
 PVOID Destination,
 PVOID Source,
 ULONG Length
);

/* NdisMoveMappedMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMoveMappedMemory(
 PVOID Destination,
 PVOID Source,
 ULONG Length
);

/* NdisMoveMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMoveMemory(
 PVOID Destination,
 PVOID Source,
 ULONG Length
);

/* NdisMoveToMappedMemory  [function; ce-only; CE 2.0..209, 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMoveToMappedMemory(
 PVOID Destination,
 PVOID Source,
 ULONG Length
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 2.11..2.12, 3.0..399, 5.0..599 */

/* NdisIMRevertBack  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..599; Ndis.lib, Ndislib.lib] */
VOID NdisIMRevertBack( 
IN NDIS_HANDLE MiniportAdapterHandle, 
IN NDIS_HANDLE SwitchHandle );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* NdisIMSwitchToMiniport  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
BOOLEAN NdisIMSwitchToMiniport(
IN NDIS_HANDLE MiniportAdapterHandle, 
OUT PNDIS_HANDLE SwitchHandle );
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* NdisMFreeMapRegisters  [function; ce-only; CE 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMFreeMapRegisters(
 NDIS_HANDLE MiniportAdapterHandle
);

/* NdisMInitializeWrapper  [function; ce-only; CE 2.11..2.12, 3.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMInitializeWrapper(
 PNDIS_HANDLE NdisWrapperHandle,
 PVOID SystemSpecific1,
 PVOID SystemSpecific2,
 PVOID SystemSpecific3
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* DriverEntry  [function; ce-only; CE 3.0..399, 5.0..699] */
NDIS_STATUS DriverEntry(
 PVOID Argument1,
 PVOID Argument2 
);

/* NdisMTrIndicateReceive  [function; ce-only; CE 3.0..399, 5.0..699; Ndis.dll, ndis.dll] */
VOID NdisMTrIndicateReceive(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_HANDLE MiniportReceiveContext,
 PVOID HeaderBuffer,
 UINT HeaderBufferSize,
 PVOID LookaheadBuffer,
 UINT LookaheadBufferSize,
 UINT PacketSize
);

/* NdisMTrIndicateReceiveComplete  [function; ce-only; CE 3.0..399, 5.0..699; Ndis.dll, ndis.dll] */
VOID NdisMTrIndicateReceiveComplete(
 NDIS_HANDLE MiniportAdapterHandle
);

/* NdisMWanIndicateReceive  [function; ce-only; CE 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMWanIndicateReceive(
 PNDIS_STATUS Status,
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_HANDLE NdisLinkContext,
 PUCHAR PacketBuffer,
 UINT PacketSize
);

/* NdisMWanIndicateReceiveComplete  [function; ce-only; CE 3.0..399, 5.0..699; Ndis.dll, ndis.dll, Ndislib.lib] */
VOID NdisMWanIndicateReceiveComplete(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_HANDLE NdisLinkContext
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* NdisIMDeInitializeDeviceInstance  [function; ce-only; CE 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
NDIS_STATUS NdisIMDeInitializeDeviceInstance(
 NDIS_HANDLE NdisMiniportHandle
);

/* NdisIMGetDeviceContext  [function; ce-only; CE 3.0..699; Ndis.lib, ndis.lib, Ndislib.lib] */
NDIS_HANDLE NdisIMGetDeviceContext(
 NDIS_HANDLE MiniportAdapterHandle
);

/* ProtocolCloseAdapterComplete  [function; ce-only; CE 3.0..699; Ndislib.lib] */
VOID ProtocolCloseAdapterComplete(
 NDIS_HANDLE ProtocolBindingContext,
 NDIS_STATUS Status
);

/* ProtocolOpenAdapterComplete  [function; ce-only; CE 3.0..699; Ndislib.lib] */
VOID ProtocolOpenAdapterComplete(
 NDIS_HANDLE ProtocolBindingContext,
 NDIS_STATUS Status,
 NDIS_STATUS OpenErrorStatus
);

/* ProtocolReceive  [function; ce-only; CE 3.0..699; Ndislib.lib] */
NDIS_STATUS ProtocolReceive(
 NDIS_HANDLE ProtocolBindingContext,
 NDIS_HANDLE MacReceiveContext,
 PVOID pHeader,
 UINT HeaderSize,
 PVOID LookAheadBuffer,
 UINT LookAheadBufferSize,
 UINT PacketSize 
);

/* ProtocolReceiveComplete  [function; ce-only; CE 3.0..699; Ndislib.lib] */
VOID ProtocolReceiveComplete(
 NDIS_HANDLE ProtocolBindingContext 
);

/* ProtocolResetComplete  [function; ce-only; CE 3.0..699; Ndislib.lib] */
VOID ProtocolResetComplete(
 NDIS_HANDLE ProtocolBindingContext,
 NDIS_STATUS Status
);

/* ProtocolStatus  [function; ce-only; CE 3.0..699; Ndislib.lib] */
VOID ProtocolStatus(
 NDIS_HANDLE ProtocolBindingContext,
 NDIS_STATUS GeneralStatus,
 PVOID StatusBuffer,
 UINT StatusBufferSize
);

/* ProtocolStatusComplete  [function; ce-only; CE 3.0..699; Ndislib.lib] */
VOID ProtocolStatusComplete(
 NDIS_HANDLE ProtocolBindingContext
);

/* ProtocolUnbindAdapter  [function; ce-only; CE 3.0..699; Ndislib.lib] */
VOID ProtocolUnbindAdapter(
 PNDIS_STATUS Status,
 NDIS_HANDLE ProtocolBindingContext,
 NDIS_HANDLE UnbindContext
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x500) || (_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 4.0..499, 6.0..699 */

/* NdisAllocatePacketPoolEx  [function; ce-only; CE 4.0..499, 6.0..699; ndis.lib] */
VOID NdisAllocatePacketPoolEx(
 PNDIS_STATUS Status,
 PNDIS_HANDLE PoolHandle,
 UINT NumberOfDescriptors,
 UINT NumberOfOverflowDescriptors,
 UINT ProtocolReservedLength
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* NdisAllocateMemoryWithTag  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
NDIS_STATUS NdisAllocateMemoryWithTag(
 PVOID* VirtualAddress,
 UINT Length,
 ULONG Tag
);

/* NdisCancelSendPackets  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisCancelSendPackets(
 NDIS_HANDLE NdisBindingHandle,
 ULONG_PTR CancelId
);

/* NdisCloseFile  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisCloseFile(
 NDIS_HANDLE FileHandle
);

/* NdisCompleteBindAdapter  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisCompleteBindAdapter(
 NDIS_HANDLE BindAdapterContext,
 NDIS_STATUS Status,
 NDIS_STATUS OpenStatus
);

/* NdisCompleteUnbindAdapter  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisCompleteUnbindAdapter(
 NDIS_HANDLE UnbindAdapterContext,
 NDIS_STATUS Status
);

/* NdisCopyLookaheadData  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisCopyLookaheadData(
 PVOID Destination,
 PVOID Source,
 ULONG Length,
 ULONG MacOptions
);

/* NdisCreateLookaheadBufferFromSharedMemory  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID teLookaheadBufferFromSharedMemory(
 PVOID pSharedMemory,
 UINT LookaheadLength,
 PVOID* pLookaheadBuffer
);

/* NdisDestroyLookaheadBufferFromSharedMemory  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisDestroyLookaheadBufferFromSharedMemory(
 PVOID pLookaheadBuffer
);

/* NdisEqualMemory  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
ULONG NdisEqualMemory(
 CONST VOID* Source1,
 CONST VOID* Source2,
 ULONG Length
);

/* NdisFillMemory  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisFillMemory(
 PVOID Destination,
 ULONG Length,
 UCHAR Fill
);

/* NdisGeneratePartialCancelId  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
UCHAR NdisGeneratePartialCancelId(void);

/* NdisGetAdapterNames  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisGetAdapterNames(
 PNDIS_STATUS Status,
 PBYTE pOutBuf,
 DWORD cbOutBufSize,
 PDWORD pcbReturned
);

/* NdisGetCacheFillSize  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
ULONG NdisGetCacheFillSize();

/* NdisGetCurrentSystemTime  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisGetCurrentSystemTime(
 PLARGE_INTEGER pSystemTime
);

/* NdisGetDriverHandle  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisGetDriverHandle(
 PNDIS_HANDLE NdisBindingHandle,
 PNDIS_HANDLE NdisDriverHandle
);

/* NdisGetProtocolNames  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisGetProtocolNames(
 PNDIS_STATUS pStatus,
 PBYTE pOutBuf,
 DWORD cbOutBufSize,
 PDWORD pcbReturned
);

/* NdisGetSystemUpTime  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisGetSystemUpTime(
 PULONG pSystemUpTime
);

/* NdisIMAssociateMiniport  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisIMAssociateMiniport(
 NDIS_HANDLE DriverHandle,
 NDIS_HANDLE ProtocolHandle
);

/* NdisIMDeregisterLayeredMiniport  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
VOID NdisIMDeregisterLayeredMiniport(
 NDIS_HANDLE DriverHandle
);

/* NdisIMGetBindingContext  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
NDIS_HANDLE NdisIMGetBindingContext(
 NDIS_HANDLE NdisBindingHandle
);

/* NdisInterlockedDecrement  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
LONG NdisInterlockedDecrement(
 PLONG Addend
);

/* NdisInterlockedIncrement  [function; ce-only; CE 4.0..699; Ndis.lib, ndis.lib] */
LONG NdisInterlockedIncrement(
 PLONG Addend
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* NdisGetVersion  [function; ce-only; CE 5.0..699; Ndis.lib, ndis.lib] */
UINT NdisGetVersion(
);

/* NdisMAllocateSharedMemory  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
VOID NdisMAllocateSharedMemory(
 NDIS_HANDLE MiniportAdapterHandle,
 ULONG Length ,
 BOOLEAN Cached,
 PVOID* VirtualAddress,
 PNDIS_PHYSICAL_ADDRESS PhysicalAddress
);

/* NdisMapFile  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
VOID NdisMapFile(
 PNDIS_STATUS
 Status
 ,
 PVOID* 
 MappedBuffer
 ,
 NDIS_HANDLE
 FileHandle
 );

/* NdisMCloseLog  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
VOID NdisMCloseLog(
 NDIS_HANDLE
 LogHandle
 );

/* NdisMCreateLog  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
NDIS_STATUS NdisMCreateLog(
 NDIS_HANDLE
 MiniportAdapterHandle
 ,
 UINT
 Size
 ,
 PNDIS_HANDLE
 LogHandle
 );

/* NdisMFlushLog  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
VOID NdisMFlushLog(
 NDIS_HANDLE LogHandle
);

/* NdisMFreeSharedMemory  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
VOID NdisMFreeSharedMemory(
 NDIS_HANDLE MiniportAdapterHandle,
 ULONG Length,
 BOOLEAN Cached,
 PVOID VirtualAddress,
 NDIS_PHYSICAL_ADDRESS PhysicalAddress
);

/* NdisMPromoteMiniport  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
NDIS_STATUS NdisMPromoteMiniport(
 NDIS_HANDLE MiniportAdapterHandle
);

/* NdisMRebindProtocolsToAdapter  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
VOID NdisMRebindProtocolsToAdapter(
 NDIS_HANDLE MiniportAdapterHandle 
);

/* NdisMRemoveMiniport  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
NDIS_STATUS NdisMRemoveMiniport(
 NDIS_HANDLE MiniportAdapterHandle
);

/* NdisMSetMiniportSecondary  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
NDIS_STATUS NdisMSetMiniportSecondary(
 NDIS_HANDLE MiniportAdapterHandle,
 NDIS_HANDLE PrimaryMiniportAdapterHandle
);

/* NdisMWriteLogData  [function; ce-only; CE 5.0..699; Ndis.dll, ndis.dll] */
NDIS_STATUS NdisMWriteLogData(
 NDIS_HANDLE LogHandle,
 PVOID LogBuffer,
 UINT LogBufferSize
);

/* NdisPacketSize  [function; ce-only; CE 5.0..699; Ndis.lib, ndis.lib] */
UINT NdisPacketSize(
 IN UINT ProtocolReservedSize
);

/* NdisQueryPendingIoCount  [function; ce-only; CE 5.0..699] */
NDIS_STATUS NdisQueryPendingIoCount(
 PVOID NdisBindingHandle,
 PULONG IoCount
);

/* NdisReadPcmciaAttributeMemory  [function; ce-only; CE 5.0..699; Ndis.lib, ndis.lib] */
ULONG NdisReadPcmciaAttributeMemory(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG Offset,
 PVOID Buffer,
 ULONG Length
);

/* NdisReadPortUchar  [function; ce-only; CE 5.0..699] */
VOID NdisReadPortUchar(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG Port,
 PUCHAR Data 
);

/* NdisReadPortUlong  [function; ce-only; CE 5.0..699] */
VOID NdisReadPortUlong(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG Port,
 PULONG Data 
);

/* NdisReadPortUshort  [function; ce-only; CE 5.0..699] */
VOID NdisReadPortUshort(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG Port,
 PUSHORT Data 
);

/* NdisReadRegisterUchar  [function; ce-only; CE 5.0..699] */
VOID NdisReadRegisterUchar(
 PUCHAR Register,
 PUCHAR Data
);

/* NdisReadRegisterUlong  [function; ce-only; CE 5.0..699] */
VOID NdisReadRegisterUlong(
 PULONG Register,
 PULONG Data
);

/* NdisReadRegisterUshort  [function; ce-only; CE 5.0..699] */
VOID NdisReadRegisterUshort(
 PUSHORT Register,
 PUSHORT Data
);

/* NdisReEnumerateProtocolBindings  [function; ce-only; CE 5.0..699] */
VOID NdisReEnumerateProtocolBindings(
 NDIS_HANDLE NdisProtocolHandle
);

/* NdisRetrieveUlong  [function; ce-only; CE 5.0..699] */
VOID NdisRetrieveUlong(
 PULONG DestinationAddress,
 PULONG SourceAddress
);

/* NdisSetPacketPoolProtocolId  [function; ce-only; CE 5.0..699; Ndis.lib, ndis.lib] */
VOID NdisSetPacketPoolProtocolId(
 IN NDIS_HANDLE PacketPoolHandle,
 IN UINT ProtocolId
);

/* NdisStoreUlong  [function; ce-only; CE 5.0..699] */
VOID NdisStoreUlong(
 PULONG DestinationAddress,
 ULONG Value
);

/* NdisUnmapFile  [function; ce-only; CE 5.0..699] */
VOID NdisUnmapFile(
 NDIS_HANDLE FileHandle
);

/* NdisWritePcmciaAttributeMemory  [function; ce-only; CE 5.0..699; Ndis.lib, ndis.lib] */
ULONG NdisWritePcmciaAttributeMemory(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG Offset,
 PVOID Buffer,
 ULONG Length
);

/* NdisWritePortUchar  [function; ce-only; CE 5.0..699] */
VOID NdisWritePortUchar(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG Port,
 UCHAR Data
);

/* NdisWritePortUlong  [function; ce-only; CE 5.0..699] */
VOID NdisWritePortUlong(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG Port,
 ULONG Data
);

/* NdisWritePortUshort  [function; ce-only; CE 5.0..699] */
VOID NdisWritePortUshort(
 NDIS_HANDLE NdisAdapterHandle,
 ULONG Port,
 USHORT Data
);

/* NdisWriteRegisterUchar  [function; ce-only; CE 5.0..699] */
VOID NdisWriteRegisterUchar(
 PUCHAR Register,
 UCHAR Data
);

/* NdisWriteRegisterUlong  [function; ce-only; CE 5.0..699] */
VOID NdisWriteRegisterUlong(
 PULONG Register,
 ULONG Data
);

/* NdisWriteRegisterUshort  [function; ce-only; CE 5.0..699] */
VOID NdisWriteRegisterUshort(
 PUSHORT Register,
 USHORT Data
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* NdisPacketPoolUsage  [function; ce-only; CE 6.0..699] */
UINT NdisPacketPoolUsage(
 NDIS_HANDLE PoolHandle
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
PVOID NDIS_BUFFER_LINKAGE(  IN PNDIS_BUFFER Buffer );
UINT NDIS_GET_PACKET_PROTOCOL_TYPE(PNDIS_PACKET_Packet_,);
UINT NDIS_SET_PACKET_HEADER_SIZE(PNDIS_PACKET _Packet,UINT _HdrSize);
LONG NDIS_SET_PACKET_TIME_RECEIVED( PNDIS_PACKET _Packet, ULONGLONG _TimeReceived );
LONG NDIS_SET_PACKET_TIME_SENT(PNDIS_PACKET _Packet,ULONGLONG _TimeSent);
LONG NDIS_SET_PACKET_TIME_TO_SEND(PNDIS_PACKET _Packet,ULONGLONG _TimeToSend);
LONG NdisMReadDmaCounter (IN NDIS_HANDLE MiniportDmaHandle);

#endif /* _NDIS_ */
