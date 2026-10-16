/* CEDDK.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 178 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CEDDK_
#define _CEDDK_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BUS_DATA_TYPE  [enum; ce-only; harvest-kb; harvest-kb] */
typedef enum _BUS_DATA_TYPE {
 ConfigurationSpaceUndefined = -1,
 Cmos,
 EisaConfiguration,
 Pos,
 CbusConfiguration,
 PCIConfiguration,
 VMEConfiguration,
 NuBusConfiguration,
 PCMCIAConfiguration,
 MPIConfiguration,
 MPSAConfiguration,
 PNPISAConfiguration,
 MaximumBusDataType
} BUS_DATA_TYPE, *PBUS_DATA_TYPE;

/* INTERFACE_TYPE  [enum; ce-only; harvest-kb; harvest-kb] */
typedef enum _INTERFACE_TYPE {
 InterfaceTypeUndefined = -1,
 Internal,
 Isa,
 Eisa,
 MicroChannel,
 TurboChannel,
 PCIBus,
 VMEBus,
 NuBus,
 PCMCIABus,
 CBus,
 MPIBus,
 MPSABus,
 ProcessorInternal,
 InternalPowerBus,
 PNPISABus,
 PNPBus,
 MaximumInterfaceType
} INTERFACE_TYPE, *PINTERFACE_TYPE;

/* DMA_ADAPTER_OBJECT  [struct; ce-only] */
typedef struct _DMA_ADAPTER_OBJECT_ {
 USHORT ObjectSize;
 INTERFACE_TYPE InterfaceType;
 ULONG BusNumber;
} DMA_ADAPTER_OBJECT , *PDMA_ADAPTER_OBJECT;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* HalGetBusData  [function; ce-only; unified-kb; unified-kb] */
ULONG HalGetBusData( 
 BUS_DATA_TYPE BusDataType, 
 ULONG BusNumber, 
 ULONG SlotNumber, 
 PVOID Buffer, 
 ULONG Length 
);

/* HalGetBusDataByOffset  [function; ce-only; unified-kb; unified-kb] */
ULONG HalGetBusDataByOffset( 
 BUS_DATA_TYPE BusDataType, 
 ULONG BusNumber, 
 ULONG SlotNumber, 
 PVOID Buffer, 
 ULONG Offset, 
 ULONG Length 
);

/* HalSetBusData  [function; ce-only; unified-kb; unified-kb] */
ULONG HalSetBusData( 
 BUS_DATA_TYPE BusDataType, 
 ULONG BusNumber, 
 ULONG SlotNumber, 
 PVOID Buffer, 
 ULONG Length 
);

/* HalSetBusDataByOffset  [function; ce-only; unified-kb; unified-kb] */
ULONG HalSetBusDataByOffset( 
 BUS_DATA_TYPE BusDataType, 
 ULONG BusNumber, 
 ULONG SlotNumber, 
 PVOID Buffer, 
 ULONG Offset, 
 ULONG Length 
);

/* HalTranslateBusAddress  [function; ce-only; harvest-kb; harvest-kb] */
BOOL HalTranslateBusAddress ( 
INTERFACE_TYPE InterfaceType, 
ULONG BusNumber, 
PHYSICAL_ADDRESS BusAddress, 
PULONG AddressSpace, 
PPHYSICAL_ADDRESS TranslatedAddress );

/* MmUnmapIoSpace  [function; ce-only; unified-kb; unified-kb] */
VOID MmUnmapIoSpace( 
 PVOID BaseAddress, 
 ULONG NumberOfBytes 
);

/* READ_PORT_BUFFER_UCHAR  [function; ce-only; unified-kb; unified-kb] */
VOID READ_PORT_BUFFER_UCHAR(
 PUCHAR Port, 
 PUCHAR Buffer, 
 ULONG Count 
);

/* READ_PORT_BUFFER_ULONG  [function; ce-only; unified-kb; unified-kb] */
VOID READ_PORT_BUFFER_ULONG(
 PULONG Port, 
 PULONG Buffer, 
 ULONG Count 
);

/* READ_PORT_BUFFER_USHORT  [function; ce-only; unified-kb; unified-kb] */
VOID READ_PORT_BUFFER_USHORT(
 PUSHORT Port, 
 PUSHORT Buffer, 
 ULONG Count 
);

/* READ_PORT_UCHAR  [function; ce-only; unified-kb; unified-kb] */
UCHAR READ_PORT_UCHAR(
 PUCHAR Port 
);

/* READ_PORT_ULONG  [function; ce-only; unified-kb; unified-kb] */
ULONG READ_PORT_ULONG(
 PULONG Port 
);

/* READ_PORT_USHORT  [function; ce-only; unified-kb; unified-kb] */
USHORT READ_PORT_USHORT(
 PUSHORT Port 
);

/* READ_REGISTER_UCHAR  [function; ce-only; unified-kb; unified-kb] */
UCHAR READ_REGISTER_UCHAR(
 PUCHAR Register 
);

/* READ_REGISTER_ULONG  [function; ce-only; unified-kb; unified-kb] */
ULONG READ_REGISTER_ULONG(
 PULONG Register 
);

/* READ_REGISTER_USHORT  [function; ce-only; unified-kb; unified-kb] */
USHORT READ_REGISTER_USHORT(
 PUSHORT Register 
);

/* WRITE_PORT_BUFFER_UCHAR  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_PORT_BUFFER_UCHAR(
 PUCHAR Port, 
 PUCHAR Buffer, 
 ULONG Count 
);

/* WRITE_PORT_BUFFER_ULONG  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_PORT_BUFFER_ULONG(
 PULONG Port, 
 PULONG Buffer, 
 ULONG Count 
);

/* WRITE_PORT_BUFFER_USHORT  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_PORT_BUFFER_ULONG(
 PULONG Port, 
 PULONG Buffer, 
 ULONG Count 
);

/* WRITE_PORT_UCHAR  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_PORT_UCHAR(
 PUCHAR Port, 
 UCHAR Value 
);

/* WRITE_PORT_ULONG  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_PORT_ULONG(
 PULONG Port, 
 ULONG Value 
);

/* WRITE_PORT_USHORT  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_PORT_USHORT(
 PUSHORT Port, 
 USHORT Value 
);

/* WRITE_REGISTER_UCHAR  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_REGISTER_UCHAR(
 PUCHAR Register, 
 UCHAR Value 
);

/* WRITE_REGISTER_ULONG  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_REGISTER_ULONG(
 PULONG Register, 
 ULONG Value 
);

/* WRITE_REGISTER_USHORT  [function; ce-only; unified-kb; unified-kb] */
VOID WRITE_REGISTER_USHORT(
 PUSHORT Register, 
 USHORT Value 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* MmMapIoSpace  [function; ce-only; CE 3.0..399, 5.0..699; CEDDK.lib] */
PVOID MmMapIoSpace( 
 PHYSICAL_ADDRESS PhysicalAddress, 
 ULONG NumberOfBytes, 
 BOOLEAN CacheEnable 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* READ_REGISTER_BUFFER_UCHAR  [function; ce-only; CE 3.0..699; CEDDK.lib] */
VOID READ_REGISTER_BUFFER_UCHAR(
 PUCHAR Register, 
 PUCHAR Buffer, 
 ULONG Count 
);

/* READ_REGISTER_BUFFER_ULONG  [function; ce-only; CE 3.0..699; CEDDK.lib] */
VOID READ_REGISTER_BUFFER_ULONG(
 PULONG Register, 
 PULONG Buffer, 
 ULONG Count 
);

/* READ_REGISTER_BUFFER_USHORT  [function; ce-only; CE 3.0..699; CEDDK.lib] */
VOID READ_REGISTER_BUFFER_USHORT(
 PUSHORT Register, 
 PUSHORT Buffer, 
 ULONG Count 
);

/* WRITE_REGISTER_BUFFER_UCHAR  [function; ce-only; CE 3.0..699; CEDDK.lib] */
VOID WRITE_REGISTER_BUFFER_UCHAR(
 PUCHAR Register, 
 PUCHAR Buffer, 
 ULONG Count 
);

/* WRITE_REGISTER_BUFFER_ULONG  [function; ce-only; CE 3.0..699; CEDDK.lib] */
VOID WRITE_REGISTER_BUFFER_ULONG(
 PULONG Register, 
 PULONG Buffer, 
 ULONG Count 
);

/* WRITE_REGISTER_BUFFER_USHORT  [function; ce-only; CE 3.0..699; CEDDK.lib] */
VOID WRITE_REGISTER_BUFFER_USHORT(
 PUSHORT Register, 
 PUSHORT Buffer, 
 ULONG Count 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* HalAllocateCommonBuffer  [function; ce-only; CE 4.0..699; CEDDK.lib] */
PVOID HalAllocateCommonBuffer(
 PDMA_ADAPTER_OBJECT DmaAdapter,
 ULONG Length,
 PPHYSICAL_ADDRESS LogicalAddress,
 BOOLEAN CacheEnabled
);

/* HalFreeCommonBuffer  [function; ce-only; CE 4.0..699; CEDDK.lib] */
VOID HalFreeCommonBuffer(
 PDMA_ADAPTER_OBJECT DmaAdapter,
 ULONG Length,
 PHYSICAL_ADDRESS LogicalAddress,
 PVOID VirtualAddress,
 BOOLEAN CacheEnabled
);

/* HalTranslateSystemAddress  [function; ce-only; CE 4.0..699; CEDDK.lib] */
BOOLEAN HalTranslateSystemAddress(
 INTERFACE_TYPE InterfaceType,
 ULONG BusNumber,
 PHYSICAL_ADDRESS SystemAddress,
 PPHYSICAL_ADDRESS TranslatedAddress
);

/* TransBusAddrToStatic  [function; ce-only; CE 4.0..699; CEDDK.lib] */
BOOL TransBusAddrToStatic(
 INTERFACE_TYPE InterfaceType,
 ULONG BusNumber,
 PHYSICAL_ADDRESS BusAddress,
 ULONG Length,
 PULONG AddressSpace,
 PPVOID MappedAddress
);

/* TransBusAddrToVirtual  [function; ce-only; CE 4.0..699; CEDDK.lib] */
BOOL TransBusAddrToVirtual(
 INTERFACE_TYPE InterfaceType,
 ULONG BusNumber,
 PHYSICAL_ADDRESS BusAddress,
 ULONG Length,
 PULONG AddressSpace,
 PPVOID MappedAddress
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* BusIoControl  [function; ce-only; CE 5.0..699; CEDDK.lib] */
BOOL BusIoControl (
 HANDLE hBusAccess,
 DWORD dwIoControlCode, 
 LPVOID lpInBuffer, 
 DWORD nInBufferSize, 
 LPVOID lpOutBuffer, 
 DWORD nOutBufferSize, 
 LPDWORD lpBytesReturned, 
 LPOVERLAPPED lpOverlapped
);

/* BusTransBusAddrToStatic  [function; ce-only; CE 5.0..699; CEDDK.lib] */
BOOL BusTransBusAddrToStatic (
 IN HANDLE hBusAccess,
 IN INTERFACE_TYPE InterfaceType,
 IN ULONG BusNumber,
 IN PHYSICAL_ADDRESS BusAddress,
 IN ULONG Length,
 IN OUT PULONG AddressSpace,
 OUT PPVOID MappedAddress
);

/* BusTransBusAddrToVirtual  [function; ce-only; CE 5.0..699; CEDDK.lib] */
BOOL BusTransBusAddrToVirtual (
 IN HANDLE hBusAccess,
 IN INTERFACE_TYPE InterfaceType,
 IN ULONG BusNumber,
 IN PHYSICAL_ADDRESS BusAddress,
 IN ULONG Length,
 IN OUT PULONG AddressSpace,
 OUT PPVOID MappedAddress
);

/* CalibrateStallCounter  [function; ce-only; CE 5.0..699; CEDDK.lib] */
VOID CalibrateStallCounter(
 void 
);

/* CloseBusAccessHandle  [function; ce-only; CE 5.0..699; CEDDK.lib] */
VOID CloseBusAccessHandle (
 HANDLE hBusAccess
);

/* CreateBusAccessHandle  [function; ce-only; CE 5.0..699; CEDDK.lib] */
HANDLE CreateBusAccessHandle (
 LPCTSTR lpActiveRegPath
);

/* GetBusNamePrefix  [function; ce-only; CE 5.0..699; CEDDK.lib] */
BOOL GetBusNamePrefix (
 HANDLE hBusAccess,
 LPTSTR lpReturnStr,
 DWORD dwSizeInCharacters
);

/* GetChildDeviceRemoveState  [function; ce-only; CE 5.0..699; CEDDK.lib] */
BOOL GetChildDeviceRemoveState (
 HANDLE hBusAccess,
 PDWORD lpdChildDeviceState
);

/* GetDeviceConfigurationData  [function; ce-only; CE 5.0..699; CEDDK.lib] */
ULONG GetDeviceConfigurationData (
 HANDLE hBusAccess,
 DWORD dwSpace,
 DWORD BusNumber,
 DWORD SlotNumber,
 DWORD dwOffset,
 DWORD dwLength,
 PVOID pBuffer
);

/* SetDeviceConfigurationData  [function; ce-only; CE 5.0..699; CEDDK.lib] */
ULONG SetDeviceConfigurationData (
 HANDLE hBusAccess,
 DWORD dwSpace,
 DWORD BusNumber,
 DWORD SlotNumber,
 DWORD dwOffset,
 DWORD dwLength,
 PVOID pBuffer
);

/* StallExecution  [function; ce-only; CE 5.0..699; CEDDK.lib] */
VOID StallExecution(
 DWORD dwMicroSec 
);

/* TranslateBusAddr  [function; ce-only; CE 5.0..699; CEDDK.lib] */
BOOL TranslateBusAddr (
 HANDLE hBusAccess,
 INTERFACE_TYPE InterfaceType,
 ULONG BusNumber,
 PHYSICAL_ADDRESS BusAddress,
 PULONG AddressSpace,
 PPHYSICAL_ADDRESS TranslatedAddress 
);

/* TranslateSystemAddr  [function; ce-only; CE 5.0..699; CEDDK.lib] */
BOOL TranslateSystemAddr (
 HANDLE hBusAccess,
 INTERFACE_TYPE InterfaceType,
 ULONG BusNumber,
 PHYSICAL_ADDRESS SystemAddress,
 PPHYSICAL_ADDRESS TranslatedAddress 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* BusChildIoControl  [function; ce-only; CE 6.0..699; CEDDK.lib] */
BOOL BusChildIoControl(
 HANDLE hBusAccess,
 DWORD dwIoControlCode,
 LPVOID lpBuffer, 
 DWORD nBufferSize
) ;

/* CeDriverDuplicateCallerHandle  [function; ce-only; CE 6.0..699; CEDDK.lib] */
HANDLE CeDriverDuplicateCallerHandle(
 HANDLE DirectCallerHandle,
 DWORD dwDesiredAccess,
 BOOL bInheritHandle,
 DWORD dwOptions
);

/* CeDriverPerformCallback  [function; ce-only; CE 6.0..699; CEDDK.lib] */
BOOL CeDriverPerformCallback(
 HANDLE hCallback,
 DWORD dwIoControlCode,
 LPVOID lpInBuf,
 DWORD nInBufSize,
 LPVOID lpOutBuf,
 DWORD nOutBufSize,
 LPDWORD lpBytesReturned,
 LPOVERLAPPED lpOverlapped
);
#endif /* _WIN32_WCE */

#endif /* _CEDDK_ */
