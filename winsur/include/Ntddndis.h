/* Ntddndis.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 39 declarations, 0 outlines, 0 base types, 1 extra macros, 0 extra decls
 */
#ifndef _NTDDNDIS_
#define _NTDDNDIS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define OID_GEN_RNDIS_CONFIG_PARAMETER 0x0001021B

/* ==================================================================
 * macros -- supplementary #define from CE pages
 * ================================================================ */
#define OID_SIZEOF(Oid) (sizeof (Oid) / sizeof (UINT))

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* NDIS_802_11_ANTENNA  [typedef; ce-only] */
typedef 
ULONG NDIS_802_11_ANTENNA;

/* NDIS_802_11_AUTHENTICATION_MODE  [enum; ce-only] */
typedef enum _NDIS_802_11_AUTHENTICATION_MODE {
 Ndis802_11AuthModeOpen,
 Ndis802_11AuthModeShared,
 Ndis802_11AuthModeAutoSwitch,
 Ndis802_11AuthModeMax,
} NDIS_802_11_AUTHENTICATION_MODE, *PNDIS_802_11_AUTHENTICATION_MODE;

/* NDIS_802_11_CONFIGURATION_FH  [struct; ce-only] */
typedef struct _NDIS_802_11_CONFIGURATION_FH {
 ULONG Length; 
 ULONG HopPattern;
 ULONG HopSet; 
 ULONG DwellTime;
} NDIS_802_11_CONFIGURATION_FH, *PNDIS_802_11_CONFIGURATION_FH;

/* NDIS_802_11_FRAGMENTATION_THRESHOLD  [typedef; ce-only] */
typedef 
ULONG NDIS_802_11_FRAGMENTATION_THRESHOLD;

/* NDIS_802_11_KEY_INDEX  [typedef; ce-only] */
typedef 
ULONG NDIS_802_11_KEY_INDEX;

/* NDIS_802_11_LSM_MODE  [enum; ce-only] */
typedef enum _NDIS_802_11_LSM_MODE {
 Ndis802_11LSMOff, 
 Ndis802_11LSMOn 
} NDIS_802_11_LSM_MODE, * PNDIS_802_11_LSM_MODE;

/* NDIS_802_11_LSM_PARAMETERS  [enum; ce-only] */
typedef enum _NDIS_802_11_LSM_PARAMETERS {
 NDIS_802_11_LSM_MODE Mode; 
 ULONG PacketLatency; 
} NDIS_802_11_LSM_PARAMETERS, * PNDIS_802_11_LSM_PARAMETERS;

/* NDIS_802_11_MAC_ADDRESS  [typedef; ce-only] */
typedef 
UCHAR NDIS_802_11_MAC_ADDRESS[6];

/* NDIS_802_11_NETWORK_INFRASTRUCTURE  [enum; ce-only] */
typedef enum _NDIS_802_11_NETWORK_INFRASTRUCTURE {
 Ndis802_11IBSS,
 Ndis802_11Infrastructure,
 Ndis802_11AutoUnknown,
 Ndis802_11InfrastructureMax,
} NDIS_802_11_NETWORK_INFRASTRUCTURE, *PNDIS_802_11_NETWORK_INFRASTRUCTURE;

/* NDIS_802_11_NETWORK_TYPE  [enum; ce-only] */
typedef enum _NDIS_802_11_NETWORK_TYPE {
 Ndis802_11FH,
 Ndis802_11DS,
 Ndis802_11NetworkTypeMax,
} NDIS_802_11_NETWORK_TYPE, *PNDIS_802_11_NETWORK_TYPE;

/* NDIS_802_11_NETWORK_TYPE_LIST  [struct; ce-only] */
typedef struct _NDIS_802_11_NETWORK_TYPE_LIST {
 ULONG NumberOfItems;
 NDIS_802_11_NETWORK_TYPE NetworkType[1];
} NDIS_802_11_NETWORK_TYPE_LIST, *PNDIS_802_11_NETWORK_TYPE_LIST;

/* NDIS_802_11_POWER_MODE  [enum; ce-only] */
typedef enum _NDIS_802_11_POWER_MODE {
 Ndis802_11PowerModeCAM,
 Ndis802_11PowerModeMAX_PSP,
 Ndis802_11PowerModeFast_PSP,
 Ndis802_11PowerModeMax,
} NDIS_802_11_POWER_MODE, *PNDIS_802_11_POWER_MODE;

/* NDIS_802_11_PRIVACY_FILTER  [enum; ce-only] */
typedef enum _NDIS_802_11_PRIVACY_FILTER {
 Ndis802_11PrivFilterAcceptAll,
 Ndis802_11PrivFilter8021xWEP,
} NDIS_802_11_PRIVACY_FILTER, *PNDIS_802_11_PRIVACY_FILTER;

/* NDIS_802_11_RADIO_POWER_STATE  [enum; ce-only] */
typedef enum _NDIS_802_11_RADIO_POWER_STATE {
 Ndis802_11RadioPowerState_Off = 0,
 Ndis802_11RadioPowerState_On = 1,
} NDIS_802_11_RADIO_POWER_STATE, *PNDIS_802_11_RADIO_POWER_STATE;

/* NDIS_802_11_RATES  [typedef; ce-only] */
typedef 
UCHAR NDIS_802_11_RATES[8];

/* NDIS_802_11_RELOAD_DEFAULTS  [enum; ce-only] */
typedef enum _NDIS_802_11_RELOAD_DEFAULTS {
 Ndis802_11ReloadWEPKeys,
} NDIS_802_11_RELOAD_DEFAULTS, *PNDIS_802_11_RELOAD_DEFAULTS;

/* NDIS_802_11_RSSI  [typedef; ce-only] */
typedef 
LONG NDIS_802_11_RSSI;

/* NDIS_802_11_RTS_THRESHOLD  [typedef; ce-only] */
typedef 
ULONG NDIS_802_11_RTS_THRESHOLD;

/* NDIS_802_11_SSID  [struct; ce-only] */
typedef struct _NDIS_802_11_SSID {
 ULONG SsidLength;
 UCHAR Ssid [32];
} NDIS_802_11_SSID, *PNDIS_802_11_SSID;

/* NDIS_802_11_STATISTICS  [struct; ce-only] */
typedef struct _NDIS_802_11_STATISTICS {
 ULONG Length;
 LARGE_INTEGER TransmittedFragmentCount;
 LARGE_INTEGER MulticastTransmittedFrameCount;
 LARGE_INTEGER FailedCount;
 LARGE_INTEGER RetryCount;
 LARGE_INTEGER MultipleRetryCount;
 LARGE_INTEGER RTSSuccessCount;
 LARGE_INTEGER RTSFailureCount;
 LARGE_INTEGER ACKFailureCount;
 LARGE_INTEGER FrameDuplicateCount;
 LARGE_INTEGER ReceivedFragmentCount;
 LARGE_INTEGER MulticastReceivedFrameCount;
 LARGE_INTEGER FCSErrorCount;
} NDIS_802_11_STATISTICS, *PNDIS_802_11_STATISTICS;

/* NDIS_802_11_TX_POWER_LEVEL  [typedef; ce-only] */
typedef 
ULONG NDIS_802_11_TX_POWER_LEVEL;

/* NDIS_802_11_WEP  [struct; ce-only] */
typedef struct _NDIS_802_11_WEP {
 ULONG Length;
 ULONG KeyIndex;
 ULONG KeyLength;
 UCHAR KeyMaterial[1];
} NDIS_802_11_WEP, *PNDIS_802_11_WEP;

/* NDIS_802_11_WEP_STATUS  [enum; ce-only] */
typedef enum _NDIS_802_11_WEP_STATUS {
 Ndis802_11WEPEnabled,
 Ndis802_11Encryption1Enabled = Ndis802_11WEPEnabled,
 Ndis802_11WEPDisabled,
 Ndis802_11EncryptionDisabled = Ndis802_11WEPDisabled,
 Ndis802_11WEPKeyAbsent,
 Ndis802_11Encryption1KeyAbsent = Ndis802_11WEPNotSupported,
 Ndis802_11WEPNotSupported,
 Ndis802_11EncryptionNotSupported = Ndis802_11WEPNotSupported,
 Ndis802_11Encryption2Enabled,
 Ndis802_11Encryption2KeyAbsent,
 Ndis802_11Encryption3Enabled,
 Ndis802_11Encryption3KeyAbsent
} NDIS_802_11_WEP_STATUS, *PNDIS_802_11_WEP_STATUS, NDIS_802_11_ENCRYPTION_STATUS, *PNDIS_802_11_ENCRYPTION_STATUS;

/* NDIS_802_5_RING_STATE  [enum; ce-only] */
typedef enum _NDIS_802_5_RING_STATE {
 NdisRingStateOpened = 1,
 NdisRingStateClosed,
 NdisRingStateOpening,
 NdisRingStateClosing,
 NdisRingStateOpenFailure,
 NdisRingStateRingFailure,
} NDIS_802_5_RING_STATE, *PNDIS_802_5_RING_STATE;

/* NDIS_MEDIUM  [enum; ce-only] */
typedef enum _NDIS_MEDIUM {
 NdisMedium802_3,
 NdisMedium802_5,
 NdisMediumWan,
 NdisMediumDix,
 NdisMediumWirelessWan,
 NdisMediumIrda,
 NdisMediumBpc,
 NdisMediumCoWan,
 NdisMedium1394,
 NdisMediumMax,
} NDIS_MEDIUM, *PNDIS_MEDIUM;

/* NDIS_PM_PACKET_PATTERN  [struct; ce-only] */
typedef struct _NDIS_PM_PACKET_PATTERN {
 ULONG Priority;
 ULONG Reserved;
 ULONG MaskSize;
 ULONG PatternOffset;
 ULONG PatternSize;
 ULONG PatternFlags;
} NDIS_PM_PACKET_PATTERN, *PNDIS_PM_PACKET_PATTERN;

/* NDIS_WAN_MEDIUM_SUBTYPE  [enum; ce-only] */
typedef enum _NDIS_WAN_MEDIUM_SUBTYPE {
 NdisWanMediumHub,
 NdisWanMediumX_25,
 NdisWanMediumIsdn,
 NdisWanMediumSerial,
 NdisWanMediumFrameRelay,
 NdisWanMediumAtm,
 NdisWanMediumSonet,
 NdisWanMediumSW56K,
 NdisWanMediumPPTP,
 NdisWanMediumL2TP,
 NdisWanMediumIrda,
 NdisWanMediumParallel,
 NdisWanMediumPppoe,
} NDIS_WAN_MEDIUM_SUBTYPE, *PNDIS_WAN_MEDIUM_SUBTYPE;

/* OID_802_11_FRAGMENTATION_THRESHOLD  [typedef; ce-only] */
typedef ULONG NDIS_802_11_FRAGMENTATION_THRESHOLD;

/* OID_802_11_REMOVE_WEP  [typedef; ce-only] */
typedef ULONG NDIS_802_11_KEY_INDEX;

/* OID_802_11_RSSI  [typedef; ce-only] */
typedef LONG NDIS_802_11_RSSI;

/* OID_802_11_RSSI_TRIGGER  [typedef; ce-only] */
typedef LONG NDIS_802_11_RSSI;

/* OID_802_11_RTS_THRESHOLD  [typedef; ce-only] */
typedef ULONG NDIS_802_11_RTS_THRESHOLD;

/* OID_802_11_RX_ANTENNA_SELECTED  [typedef; ce-only] */
typedef ULONG NDIS_802_11_ANTENNA;

/* OID_802_11_TX_ANTENNA_SELECTED  [typedef; ce-only] */
typedef ULONG NDIS_802_11_ANTENNA;

/* NDIS_802_11_CONFIGURATION  [struct; ce-only] */
typedef struct _NDIS_802_11_CONFIGURATION {
 ULONG Length;
 ULONG BeaconPeriod;
 ULONG ATIMWindow;
 ULONG DSConfig;
 NDIS_802_11_CONFIGURATION_FH FHConfig;
} NDIS_802_11_CONFIGURATION, *PNDIS_802_11_CONFIGURATION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* OID_802_11_BSSID  [?; ce-only; CE 4.0..699] */
Typedef UCHAR NDIS_802_11_MAC_ADDRESS[6];
#endif /* _WIN32_WCE */

#endif /* _NTDDNDIS_ */
