/* gpsapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 22 constants, 15 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _GPSAPI_
#define _GPSAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define GPS_DATA_FLAGS_HARDWARE_OFF 0x00000001
#define GPS_MAX_FRIENDLY_NAME 64
#define GPS_MAX_PREFIX_NAME 16
#define GPS_MAX_SATELLITES 12
#define GPS_VALID_ALTITUDE_WRT_ELLIPSOID 0x00000080
#define GPS_VALID_ALTITUDE_WRT_SEA_LEVEL 0x00000040
#define GPS_VALID_HEADING 0x00000010
#define GPS_VALID_HORIZONTAL_DILUTION_OF_PRECISION 0x00000200
#define GPS_VALID_LATITUDE 0x00000002
#define GPS_VALID_LONGITUDE 0x00000004
#define GPS_VALID_MAGNETIC_VARIATION 0x00000020
#define GPS_VALID_POSITION_DILUTION_OF_PRECISION 0x00000100
#define GPS_VALID_SATELLITE_COUNT 0x00000800
#define GPS_VALID_SATELLITES_IN_VIEW 0x00002000
#define GPS_VALID_SATELLITES_IN_VIEW_AZIMUTH 0x00010000
#define GPS_VALID_SATELLITES_IN_VIEW_ELEVATION 0x00008000
#define GPS_VALID_SATELLITES_IN_VIEW_PRNS 0x00004000
#define GPS_VALID_SATELLITES_IN_VIEW_SIGNAL_TO_NOISE_RATIO 0x00020000
#define GPS_VALID_SATELLITES_USED_PRNS 0x00001000
#define GPS_VALID_SPEED 0x00000008
#define GPS_VALID_UTC_TIME 0x00000001
#define GPS_VALID_VERTICAL_DILUTION_OF_PRECISION 0x00000400

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* GPS_FIX_QUALITY  [enum; ce-only] */
typedef enum {
 GPS_FIX_QUALITY_UNKNOWN = 0,
 GPS_FIX_QUALITY_GPS,
 GPS_FIX_QUALITY_DGPS
} GPS_FIX_QUALITY;
typedef GPS_FIX_QUALITY *PGPS_FIX_QUALITY, *LPGPS_FIX_QUALITY;

/* GPS_FIX_SELECTION  [enum; ce-only] */
typedef enum {
 GPS_FIX_SELECTION_UNKNOWN = 0,
 GPS_FIX_SELECTION_AUTO,
 GPS_FIX_SELECTION_MANUAL
} GPS_FIX_SELECTION;
typedef GPS_FIX_SELECTION *PGPS_FIX_SELECTION, *LPGPS_FIX_SELECTION;

/* GPS_FIX_TYPE  [enum; ce-only] */
typedef enum {
 GPS_FIX_UNKNOWN = 0,
 GPS_FIX_2D,
 GPS_FIX_3D
} GPS_FIX_TYPE;
typedef GPS_FIX_TYPE *PGPS_FIX_TYPE, *LPGPS_FIX_TYPE;

/* GPS_POSITION  [struct; ce-only] */
typedef struct _GPS_POSITION {
 DWORD dwVersion;
 DWORD dwSize;
 DWORD dwValidFields;
 DWORD dwFlags;
 SYSTEMTIME stUTCTime;
 double dblLatitude;
 double dblLongitude;
 float flSpeed;
 float flHeading;
 double dblMagneticVariation;
 float flAltitudeWRTSeaLevel;
 float flAltitudeWRTEllipsoid;
 GPS_FIX_QUALITY FixQuality;
 GPS_FIX_TYPE FixType;
 GPS_FIX_SELECTION SelectionType;
 float flPositionDilutionOfPrecision;
 float flHorizontalDilutionOfPrecision;
 float flVerticalDilutionOfPrecision;
 DWORD dwSatelliteCount;
 DWORD rgdwSatellitesUsedPRNs[GPS_MAX_SATELLITES];
 DWORD dwSatellitesInView;
 DWORD rgdwSatellitesInViewPRNs[GPS_MAX_SATELLITES];
 DWORD rgdwSatellitesInViewElevation[GPS_MAX_SATELLITES];
 DWORD rgdwSatellitesInViewAzimuth[GPS_MAX_SATELLITES];
 DWORD rgdwSatellitesInViewSignalToNoiseRatio[GPS_MAX_SATELLITES];
} GPS_POSITION, *PGPS_POSITION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* GPSCloseDevice  [function; ce-only; unified-kb; unified-kb] */
DWORD GPSCloseDevice(
 HANDLE hGPSDevice
);

/* GPSGetPosition  [function; ce-only; unified-kb; unified-kb] */
DWORD GPSGetPosition(
 HANDLE hGPSDevice,
 GPS_POSITION *pGPSPosition,
 DWORD dwMaximumAge,
 DWORD dwFlags
);

/* GPSOpenDevice  [function; ce-only; unified-kb; unified-kb] */
HANDLE GPSOpenDevice(
 HANDLE hNewLocationData,
 HANDLE hDeviceStateChange,
 const WCHAR *szDeviceName,
 DWORD dwFlags
);

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
DWORD GPS_Init(DWORD dwContext);

#endif /* _GPSAPI_ */
