/* Ndistapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 36 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NDISTAPI_
#define _NDISTAPI_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* NDIS_TAPI_CONFIG_DIALOG  [struct; ce-only] */
typedef struct _NDIS_TAPI_CONFIG_DIALOG { 
 ULONG ulRequestID; 
 ULONG ulDeviceID; 
 ULONG ulDeviceClassSize; 
 ULONG ulDeviceClassOffset; 
 ULONG ulLibraryNameTotalSize; 
 ULONG ulLibraryNameNeededSize; 
 CHAR szLibraryName[1]; 
} NDIS_TAPI_CONFIG_DIALOG, *PNDIS_TAPI_CONFIG_DIALOG;

/* NDIS_TAPI_NEGOTIATE_EXT_VERSION  [struct; ce-only] */
typedef struct _NDIS_TAPI_NEGOTIATE_EXT_VERSION { 
 ULONG ulRequestID; 
 ULONG ulDeviceID; 
 ULONG ulLowVersion; 
 ULONG ulHighVersion; 
 OUT ULONG ulExtVersion; 
} NDIS_TAPI_NEGOTIATE_EXT_VERSION, *PNDIS_TAPI_NEGOTIATE_EXT_VERSION;

/* NDIS_TAPI_PROVIDER_INITIALIZE  [struct; ce-only] */
typedef struct _NDIS_TAPI_PROVIDER_INITIALIZE { 
 ULONG ulRequestID; 
 ULONG ulDeviceIDBase; 
 ULONG ulNumLineDevs; 
 ULONG ulProviderID; 
} NDIS_TAPI_PROVIDER_INITIALIZE, *PNDIS_TAPI_PROVIDER_INITIALIZE;

/* NDIS_TAPI_PROVIDER_SHUTDOWN  [struct; ce-only] */
typedef struct _NDIS_TAPI_PROVIDER_SHUTDOWN { 
 ULONG ulRequestID; 
} NDIS_TAPI_PROVIDER_SHUTDOWN, *PNDIS_TAPI_PROVIDER_SHUTDOWN;

/* NDIS_TAPI_SET_DEV_CONFIG  [struct; ce-only] */
typedef struct _NDIS_TAPI_SET_DEV_CONFIG { 
 ULONG ulRequestID; 
 ULONG ulDeviceID; 
 ULONG ulDeviceClassSize; 
 ULONG ulDeviceClassOffset; 
 ULONG ulDeviceConfigSize; 
 UCHAR DeviceConfig[1]; 
} NDIS_TAPI_SET_DEV_CONFIG, *PNDIS_TAPI_SET_DEV_CONFIG;

/* VAR_STRING  [struct; ce-only] */
typedef struct _VAR_STRING {
 ULONG ulTotalSize;
 ULONG ulNeededSize;
 ULONG ulUsedSize;
 ULONG ulStringFormat;
 ULONG ulStringSize;
 ULONG ulStringOffset;
} VAR_STRING, *PVAR_STRING;

/* NDIS_TAPI_GET_DEV_CONFIG  [struct; ce-only] */
typedef struct _NDIS_TAPI_GET_DEV_CONFIG { 
 ULONG ulRequestID; 
 ULONG ulDeviceID; 
 ULONG ulDeviceClassSize; 
 ULONG ulDeviceClassOffset; 
 VAR_STRING DeviceConfig; 
} NDIS_TAPI_GET_DEV_CONFIG, *PNDIS_TAPI_GET_DEV_CONFIG;

#endif /* _NDISTAPI_ */
