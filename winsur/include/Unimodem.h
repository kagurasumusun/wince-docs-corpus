/* Unimodem.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _UNIMODEM_
#define _UNIMODEM_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* PHONECAPS  [struct; shared] */
typedef struct phonecaps_tag{
 DWORD dwTotalSize;
 DWORD dwNeededSize;
 DWORD dwUsedSize;
 DWORD dwProviderInfoSize;
 DWORD dwProviderInfoOffset;
 DWORD dwPhoneInfoSize;
 DWORD dwPhoneInfoOffset;
 DWORD dwPermanentPhoneID;
 DWORD dwPhoneNameSize;
 DWORD dwPhoneNameOffset;
 DWORD dwStringFormat;
 DWORD dwPhoneStates;
 DWORD dwHookSwitchDevs;
 DWORD dwHandsetHookSwitchModes;
 DWORD dwSpeakerHookSwitchModes;
 DWORD dwHeadsetHookSwitchModes;
 DWORD dwVolumeFlags;
 DWORD dwGainFlags;
 DWORD dwDisplayNumRows;
 DWORD dwDisplayNumColumns;
 DWORD dwNumRingModes;
 DWORD dwNumButtonLamps;
 DWORD dwButtonModesSize;
 DWORD dwButtonModesOffset;
 DWORD dwButtonModesFunctionsSize;
 DWORD dwButtonModesFunctionsOffset;
 DWORD dwLampModesSize;
 DWORD dwLampModesOffset;
 DWORD dwNumSetData;
 DWORD dwSetDataSize;
 DWORD dwSetDataOffset;
 DWORD dwNumGetData;
 DWORD dwGetDataSize;
 DWORD dwGetDataOffset;
 DWORD dwDevSpecificSize;
 DWORD dwDevSpecificOffset;
 DWORD dwDeviceClassesSize;
 DWORD dwDeviceClassesOffset;
 DWORD dwPhoneFeatures;
 DWORD dwSettableHandsetHookSwitchModes;
 DWORD dwSettableSpeakerHookSwitchModes;
 DWORD dwSettableHeadsetHookSwitchModes;
 DWORD dwMonitoredHandsetHookSwitchModes;
 DWORD dwMonitoredSpeakerHookSwitchModes;
 DWORD dwMonitoredHeadsetHookSwitchModes;
} PHONECAPS;
typedef PHONECAPS *PPHONECAPS, *LPPHONECAPS;

/* UNIMODEM_INFO  [struct; ce-only] */
typedef struct UNIMODEM_INFO_tag {
 WORD wDeviceType; 
 WORD wActive; 
 DWORD dwPPPMTU; 
} UNIMODEM_INFO, * PUNIMODEM_INFO;

#endif /* _UNIMODEM_ */
