/* Av_upnp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 9 declarations, 1 outlines, 0 base types, 0 extra macros, 14 extra decls
 */
#ifndef _AV_UPNP_
#define _AV_UPNP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define BIT_AV_ERROR 0
#define BIT_AV_TRACE 2
#define BIT_AV_WARN 1

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ConnectionInfo  [struct, typedef; ce-only; Av_upnp.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DeviceCapabilities  [struct, typedef; shared; Av_upnp.lib; A/W DeviceCapabilitiesA,DeviceCapabilitiesW (CE is W-side)] */
struct DeviceCapabilities
 {
 wstring 
 strPossiblePlayMedia
 ;
 wstring 
 strPossibleRecMedia
 ;
 wstring 
 strPossibleRecQualityModes
 ;
 };

/* DIRECTION  [enum; ce-only; Av_upnp.lib] */
enum DIRECTION {
 OUTPUT,
 INPUT
};

/* MediaInfo  [struct, typedef; ce-only; Av_upnp.lib] */
struct MediaInfo
 {
 unsigned long 
 nNrTracks
 ;
 wstring 
 strMediaDuration
 ;
 wstring 
 strCurrentURI
 ;
 wstring 
 strCurrentURIMetaData
 ;
 wstring 
 strNextURI
 ;
 wstring 
 strNextURIMetaData
 ;
 wstring 
 strPlayMedium
 ;
 wstring 
 strRecordMedium
 ;
 wstring 
 strWriteStatus
 ;
 };

/* object  [struct, typedef; ce-only; Av_upnp.lib] */
struct object 
{ 
 // constructor not shown 
 bool bContainer; 
 wstring strID; 
 wstring strParentID; 
 wstring strTitle; 
 wstring strClass; 
 bool bRestricted; 
 // GetProperty declarations not shown 
 // private members not shown 
};

/* PositionInfo  [struct, typedef; ce-only; Av_upnp.lib] */
struct PositionInfo
 {
 unsigned long 
 nTrack
 ;
 wstring 
 strTrackDuration
 ;
 wstring 
 strTrackMetaData
 ;
 wstring 
 strTrackURI
 ;
 wstring 
 strRelTime
 ;
 wstring 
 strAbsTime
 ;
 long 
 nRelCount
 ;
 long 
 nAbsCount
 ;
 };

/* TransportActions  [struct, typedef; ce-only; Av_upnp.lib] */
struct TransportActions
 {
 bool 
 bPlay
 ;
 bool 
 bStop
 ;
 bool 
 bPause
 ;
 bool 
 bSeek
 ;
 bool 
 bNext
 ;
 bool 
 bPrevious
 ;
 bool 
 bRecord
 ;
 };

/* TransportInfo  [struct, typedef; ce-only; Av_upnp.lib] */
struct TransportInfo
 {
 wstring 
 strCurrentTransportState
 ;
 wstring 
 strCurrentTransportStatus
 ;
 wstring 
 strCurrentSpeed
 ;
 };

/* TransportSettings  [struct, typedef; ce-only; Av_upnp.lib] */
struct TransportSettings
 {
 wstring 
 strPlayMode
 ;
 wstring 
 strRecQualityMode
 ;
 };

/* UPnPAVError  [enum; ce-only; Av_upnp.lib] */
enum UPnPAVError
{
 SUCCESS_AV = 0,
 // Internal AV Toolkit only errors
 ERROR_AV_POINTER = -1,
 ERROR_AV_OOM = -2,
 ERROR_AV_INVALID_INSTANCE = -3,
 ERROR_AV_INVALID_STATEVAR = -4,
 ERROR_AV_ALREADY_INITED = -5,
 // Internal AV Toolkit Control Point errors
 ERROR_AV_NONEXISTANT_SERVICE = -6,
 ERROR_AV_NO_MORE_ITEMS = -7,
 ERROR_AV_UPNP_ERROR = -8,
 ERROR_AV_INVALID_OUT_ARGUMENTS = -9,
 // Standard UPnP Errors
 ERROR_AV_UPNP_INVALID_ACTION = FAULT_INVALID_ACTION,
 ERROR_AV_UPNP_ACTION_FAILED = FAULT_DEVICE_INTERNAL_ERROR,
 // ConnectionManager Errors
 ERROR_AV_UPNP_CM_INCOMPATIBLE_PROTOCOL = 701,
 ERROR_AV_UPNP_CM_INCOMPATIBLE_DIRECTION = 702,
 ERROR_AV_UPNP_CM_INSUFFICIENT_NET_RESOURCES = 703,
 ERROR_AV_UPNP_CM_LOCAL_RESTRICTIONS = 704,
 ERROR_AV_UPNP_CM_ACCESS_DENIED = 705,
 ERROR_AV_UPNP_CM_INVALID_CONNECTION_REFERENCE = 706,
 ERROR_AV_UPNP_CM_NOT_IN_NETWORK = 707,
 // AVTransport Errors
 ERROR_AV_UPNP_AVT_INVALID_TRANSITION = 701,
 ERROR_AV_UPNP_AVT_NO_CONTENTS = 702,
 ERROR_AV_UPNP_AVT_READ_ERROR = 703,
 ERROR_AV_UPNP_AVT_UNSUPPORTED_PLAY_FORMAT = 704,
 ERROR_AV_UPNP_AVT_TRANSPORT_LOCKED = 705,
 ERROR_AV_UPNP_AVT_WRITE_ERROR = 706,
 ERROR_AV_UPNP_AVT_PROTECTED_MEDIA = 707,
 ERROR_AV_UPNP_AVT_UNSUPPORTED_REC_FORMAT = 708,
 ERROR_AV_UPNP_AVT_FULL_MEDIA = 709,
 ERROR_AV_UPNP_AVT_UNSUPPORTED_SEEK_MODE = 710,
 ERROR_AV_UPNP_AVT_ILLEGAL_SEEK_TARGET = 711,
 ERROR_AV_UPNP_AVT_UNSUPPORTED_PLAY_MODE = 712,
 ERROR_AV_UPNP_AVT_UNSUPPORTED_REC_QUALITY = 713,
 ERROR_AV_UPNP_AVT_ILLEGAL_MIME = 714,
 ERROR_AV_UPNP_AVT_CONTENT_BUSY = 715,
 ERROR_AV_UPNP_AVT_RESOURCE_NOT_FOUND = 716,
 ERROR_AV_UPNP_AVT_UNSUPPORTED_PLAY_SPEED = 717,
 ERROR_AV_UPNP_AVT_INVALID_INSTANCE_ID = 718,
 // RenderingControl Errors
 ERROR_AV_UPNP_RC_INVALID_PRESET_NAME = 701,
 ERROR_AV_UPNP_RC_INVALID_INSTANCE_ID = 702,
 // ContentDirectory Errors
 ERROR_AV_UPNP_CD_NO_SUCH_OBJECT = 701,
 ERROR_AV_UPNP_CD_INVALID_CURRENTTAGVALUE = 702,
 ERROR_AV_UPNP_CD_INVALID_NEWTAGVALUE = 703,
 ERROR_AV_UPNP_CD_REQUIRED_TAG_DELETE = 704,
 ERROR_AV_UPNP_CD_READONLY_TAG_UPDATE = 705,
 ERROR_AV_UPNP_CD_PARAMETER_NUM_MISMATCH = 706,
 ERROR_AV_UPNP_CD_BAD_SEARCH_CRITERIA = 708,
 ERROR_AV_UPNP_CD_BAD_SORT_CRITERIA = 709,
 ERROR_AV_UPNP_CD_NO_SUCH_CONTAINER = 710,
 ERROR_AV_UPNP_CD_RESTRICTED_OBJECT = 711,
 ERROR_AV_UPNP_CD_BAD_METADATA = 712,
 ERROR_AV_UPNP_CD_RESTRICTED_PARENT_OBJECT = 713,
 ERROR_AV_UPNP_CD_NO_SUCH_SOURCE_RESOURCE = 714,
 ERROR_AV_UPNP_CD_SOURCE_RESOURCE_ACCESS_DENIED = 715,
 ERROR_AV_UPNP_CD_TRANSFER_BUSY = 716,
 ERROR_AV_UPNP_CD_NO_SUCH_FILE_TRANSFER = 717,
 ERROR_AV_UPNP_CD_NO_SUCH_DESTINATION_RESOURCE = 718,
 ERROR_AV_UPNP_CD_DESTINATION_RESOURCE_ACCESS_DENIED = 719,
 ERROR_AV_UPNP_CD_REQUEST_FAILED = 720
};

/* strPossibleRecQualityModes  [extra struct] */
struct DeviceCapabilities
{
  wstring strPossiblePlayMedia;
  wstring strPossibleRecMedia;
  wstring strPossibleRecQualityModes;
};

/* strWriteStatus  [extra struct] */
struct MediaInfo
{
  unsigned long nNrTracks;
  wstring strMediaDuration;
  wstring strCurrentURI;
  wstring strCurrentURIMetaData;
  wstring strNextURI;
  wstring strNextURIMetaData;
  wstring strPlayMedium;
  wstring strRecordMedium;
  wstring strWriteStatus;
};

/* shown  [extra struct] */
struct object
{
  bool bContainer;
  wstring strID;
  wstring strParentID;
  wstring strTitle;
  wstring strClass;
  bool bRestricted;
};

/* nAbsCount  [extra struct] */
struct PositionInfo
{
  unsigned long nTrack;
  wstring strTrackDuration;
  wstring strTrackMetaData;
  wstring strTrackURI;
  wstring strRelTime;
  wstring strAbsTime;
  long nRelCount;
  long nAbsCount;
};

/* bRecord  [extra struct] */
struct TransportActions
{
  bool bPlay;
  bool bStop;
  bool bPause;
  bool bSeek;
  bool bNext;
  bool bPrevious;
  bool bRecord;
};

/* strCurrentSpeed  [extra struct] */
struct TransportInfo
{
  wstring strCurrentTransportState;
  wstring strCurrentTransportStatus;
  wstring strCurrentSpeed;
};

/* strRecQualityMode  [extra struct] */
struct TransportSettings
{
  wstring strPlayMode;
  wstring strRecQualityMode;
};

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
bool AddNamespaceMapping(  LPCWSTR pszNamespace,  LPCWSTR pszPrefix  );
DWORD AddSinkProtocol( LPCWSTR pszProtocolInfo );
DWORD AddSourceProtocol( LPCWSTR pszProtocolInfo );
bool GetFirstObject(  LPCWSTR pszXml,  object* pObj  );
bool GetNextObject(  object* pObj  );
DWORD RemoveSinkProtocol( LPCWSTR pszProtocolInfo );
DWORD RemoveSourceProtocol( LPCWSTR pszProtocolInfo );

#endif /* _AV_UPNP_ */
