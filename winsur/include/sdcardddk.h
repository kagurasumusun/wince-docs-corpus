/* sdcardddk.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 46 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _SDCARDDDK_
#define _SDCARDDDK_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FUNCTION_POWER_STATE  [struct; ce-only] */
typedef struct _FUNCTION_POWER_STATE{
 BOOL fPowerControlSupport;
 BOOL fPowerControlEnabled;
 BOOL fFunctionEnabled;
 BOOL fSupportsPowerSelect;
 BOOL fLowPower;
 DWORD OperatingVoltage;
 USHORT CurrentDrawNow;
 INT EnableDelta;
 INT SelectDelta;
}FUNCTION_POWER_STATE, *PFUNCTION_POWER_STATE;

/* SD_CARD_SWITCH_FUNCTION  [struct; ce-only] */
typedef struct _SD_CARD_SWITCH_FUNCTION{
 DWORD dwSelectedFunction;
 DWORD dwMaxCurrentAllowed;
 DWORD dwTimeOut;
 BYTE clientData[512/8];
}SD_CARD_SWITCH_FUNCTION, *PSD_CARD_SWITCH_FUNCTION;

/* SD_FS_TYPE  [enum; ce-only] */
typedef enum {
 SD_FS_FAT_PARTITION_TABLE,
 SD_FS_FAT_NO_PARTITION_TABLE,
 SD_FS_UNIVERSAL,
 SD_FS_OTHER
} SD_FS_TYPE, *PSD_FS_TYPE;

/* SD_HOST_ALLOC_FREE_DMA_BUFFER  [struct; ce-only] */
typedef struct {
 ULONG Length;
 BOOLEAN CacheEnabled;
 PVOID VirtualAddress;
 PHYSICAL_ADDRESS LogicalAddress;
}SD_HOST_ALLOC_FREE_DMA_BUFFER, *PSD_HOST_ALLOC_FREE_DMA_BUFFER;

/* SD_HOST_BLOCK_CAPABILITY  [struct; ce-only] */
typedef struct _SD_HOST_BLOCK_CAPABILITY {
 USHORT ReadBlockSize;
 USHORT WriteBlockSize;
 USHORT ReadBlocks;
 USHORT WriteBlocks;
} SD_HOST_BLOCK_CAPABILITY, *PSD_HOST_BLOCK_CAPABILITY;

/* SD_INFO_TYPE  [enum; ce-only] */
typedef enum {
 SD_INFO_REGISTER_OCR = 0,
 SD_INFO_REGISTER_CID,
 SD_INFO_REGISTER_CSD,
 SD_INFO_REGISTER_RCA,
 SD_INFO_REGISTER_IO_OCR,
 SD_INFO_CARD_INTERFACE,
 SD_INFO_CARD_STATUS,
 SD_INFO_SDIO,
 SD_INFO_HOST_IF_CAPABILITIES,
 SD_INFO_HOST_BLOCK_CAPABILITY,
 SD_INFO_HIGH_CAPACITY_SUPPORT,
 SD_INFO_TYPE_COUNT,
 SD_INFO_CARD_INTERFACE_EX,
 SD_INFO_SWITCH_FUNCTION
} SD_INFO_TYPE;
typedef SD_INFO_TYPE *PSD_INFO_TYPE, *LPSD_INFO_TYPE;

/* SD_INTERFACE_MODE  [enum; ce-only] */
typedef enum {
 SD_INTERFACE_SD_MMC_1BIT,
 SD_INTERFACE_SD_4BIT
} SD_INTERFACE_MODE;
typedef SD_INTERFACE_MODE *PSD_INTERFACE_MODE, *LPSD_INTERFACE_MODE;

/* SD_INTERFACE_MODE_EX  [typedef; ce-only] */
typedef union{
 struct{
 ULONG sd4Bit:1;
 ULONG sdHighSpeed:1;
 ULONG :28;
 ULONG sdWriteProtected:1;
 ULONG sdHighCapacity:1;
 }bit;
 ULONG uInterfaceMode;
}SD_INTERFACE_MODE_EX, *PSD_INTERFACE_MODE_EX;

/* SD_IO_FUNCTION_ENABLE_INFO  [struct; ce-only] */
typedef struct _SD_IO_FUNCTION_ENABLE_INFO {
 ULONG ReadyRetryCount;
 ULONG Interval;
} SD_IO_FUNCTION_ENABLE_INFO, *PSD_IO_FUNCTION_ENABLE_INFO

/* SD_IO_TRANSFER_TYPE  [enum; ce-only] */
typedef enum {
 SD_IO_READ,
 SD_IO_WRITE,
} SD_IO_TRANSFER_TYPE

/* SD_PARSED_REGISTER_CID  [struct; ce-only] */
typedef struct _SD_PARSED_REGISTER_CID {
 UCHAR ManufacturerID;
 CHAR OEMApplicationID[3];
 CHAR ProductName[7];
 UCHAR MajorProductRevision;
 UCHAR MinorProductRevision;
 DWORD ProductSerialNumber;
 UCHAR ManufacturingMonth;
 USHORT ManufacturingYear;
 UCHAR RawCIDRegister[16];
} SD_PARSED_REGISTER_CID, *PSD_PARSED_REGISTER_CID;

/* SD_RESPONSE_TYPE  [enum; ce-only] */
typedef enum _SD_RESPONSE_TYPE {
 NoResponse,
 ResponseR1,
 ResponseR1b,
 ResponseR2,
 ResponseR3,
 ResponseR4,
 ResponseR5,
 ResponseR6,
 ResponseR7
} SD_RESPONSE_TYPE, *PSD_RESPONSE_TYPE;

/* SD_SET_FEATURE_TYPE  [enum; ce-only] */
typedef enum {
 SD_IO_FUNCTION_ENABLE = 0,
 SD_IO_FUNCTION_DISABLE,
 SD_IO_FUNCTION_SET_BLOCK_SIZE,
 SD_SET_DATA_TRANSFER_CLOCKS,
 SD_SET_CARD_INTERFACE,
 SD_SET_CLOCK_STATE_DURING_IDLE,
 SD_IS_SOFT_BLOCK_AVAILABLE,
 SD_SOFT_BLOCK_FORCE_UTILIZATION,
 SD_SOFT_BLOCK_DEFAULT_UTILIZATON,
 SD_CARD_SELECT_REQUEST,
 SD_CARD_DESELECT_REQUEST,
 SD_CARD_FORCE_RESET,
 SD_IS_FAST_PATH_AVAILABLE,
 SD_FAST_PATH_DISABLE,
 SD_FAST_PATH_ENABLE,
 SD_IO_FUNCTION_HIGH_POWER,
 SD_IO_FUNCTION_LOW_POWER,
 SD_INFO_POWER_CONTROL_STATE,
 SD_SET_CARD_INTERFACE_EX,
 SD_SET_SWITCH_FUNCTION,
 SD_DMA_ALLOC_PHYS_MEM,
 SD_DMA_FREE_PHYS_MEM
} SD_SET_FEATURE_TYPE, *PSD_SET_FEATURE_TYPE;

/* SD_SLOT_EVENT_TYPE  [enum; ce-only] */
typedef enum _SD_SLOT_EVENT_TYPE{
 SDCardEjected = 1,
 SDCardSelected = 2,
 SDCardDeselected = 3,
 SDCardBeginSelectDeselect = 4,
 SDCardDeselectRequest = 5,
 SDCardSelectRequest = 6
} SD_SLOT_EVENT_TYPE, *PSD_SLOT_EVENT_TYPE;

/* SD_TRANSFER_CLASS  [enum; ce-only] */
typedef enum {
 SD_READ,
 SD_WRITE,
 SD_COMMAND
} SD_TRANSFER_CLASS;
typedef SD_TRANSFER_CLASS *PSD_TRANSFER_CLASS, *LPSD_TRANSFER_CLASS;

/* SDCARD_DEVICE_TYPE  [enum; ce-only] */
typedef enum _SDCARD_DEVICE_TYPE {
 Device_Unknown,
 Device_MMC,
 Device_SD_Memory,
 Device_SD_IO,
 Device_SD_Combo
} SDCARD_DEVICE_TYPE, *PSDCARD_DEVICE_TYPE;

/* SDIO_CARD_INFO  [struct; ce-only] */
typedef struct _SDIO_CARD_INFO {
 UCHAR FunctionNumber;
 UCHAR DeviceCode;
 DWORD CISPointer;
 DWORD CSAPointer;
 UCHAR CardCapability;
} SDIO_CARD_INFO, *PSDIO_CARD_INFO;

/* SD_CARD_INTERFACE  [struct; ce-only] */
typedef struct _SD_CARD_INTERFACE {
 SD_INTERFACE_MODE InterfaceMode;
 ULONG ClockRate;
 BOOL WriteProtected;
} SD_CARD_INTERFACE, *PSD_CARD_INTERFACE;

/* SD_CARD_INTERFACE_EX  [struct; ce-only] */
typedef struct _SD_CARD_INTERFACE_EX{
 SD_INTERFACE_MODE_EX InterfaceModeEx;
 ULONG ClockRate;
 ULONG Reserved[6];
}SD_CARD_INTERFACE_EX, *PSD_CARD_INTERFACE_EX;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* SDOutputBuffer  [function; ce-only; CE 5.0..699; Sdcardlib.lib, sdcardlib.lib] */
VOID SDOutputBuffer(
 PVOID pBuffer,
 ULONG BufferSize
);

/* SDPerformSafeCopy  [function; ce-only; CE 5.0..699; Sdcardlib.lib, sdcardlib.lib] */
BOOLEAN SDPerformSafeCopy(
 PVOID pDestination,
 PVOID pSource, 
 ULONG Length
);
#endif /* _WIN32_WCE */

#endif /* _SDCARDDDK_ */
