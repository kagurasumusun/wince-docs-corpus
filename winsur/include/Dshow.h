/* Dshow.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 25 constants, 47 declarations, 2 outlines, 0 base types, 0 extra macros, 70 extra decls
 */
#ifndef _DSHOW_
#define _DSHOW_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define AM_EXSEEK_BUFFERING 32
#define AM_EXSEEK_CANSCAN 2
#define AM_EXSEEK_CANSEEK 1
#define AM_EXSEEK_MARKERSEEK 4
#define AM_EXSEEK_NOSTANDARDREPAINT 16
#define AM_EXSEEK_SCANWITHOUTCLOCK 8
#define AM_EXSEEK_SENDS_VIDEOFRAMEREADY 64
#define AM_VIDEO_FLAG_FIELD1 0x0001
#define AM_VIDEO_FLAG_FIELD1FIRST 0x0004
#define AM_VIDEO_FLAG_FIELD2 0x0002
#define AM_VIDEO_FLAG_FIELD_MASK 0x0003
#define AM_VIDEO_FLAG_INTERLEAVED_FRAME 0x0000
#define AM_VIDEO_FLAG_REPEAT_FIELD 0x0040
#define AM_VIDEO_FLAG_WEAVE 0x0008
#define KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE 0x0000L
#define KSPROPERTY_CAMERACONTROL_FLAGS_AUTO 0x0001L
#define KSPROPERTY_CAMERACONTROL_FLAGS_MANUAL 0x0002L
#define KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE 0x0010L
#define MAXLONGLONG 0x7FFFFFFFFFFFFFFF
#define MERIT_DO_NOT_USE 0x200000
#define MERIT_HW_COMPRESSOR 0x100050
#define MERIT_NORMAL 0x600000
#define MERIT_PREFERRED 0x800000
#define MERIT_SW_COMPRESSOR 0x100000
#define MERIT_UNLIKELY 0x400000

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* _AM_FILTER_MISC_FLAGS  [enum; shared; entity-headers] */
typedef enum _AM_FILTER_MISC_FLAGS {
 AM_FILTER_MISC_FLAGS_IS_RENDERER = 0x00000001,
 AM_FILTER_MISC_FLAGS_IS_SOURCE = 0x00000002,
 AM_FILTER_MISC_FLAG_NO_CAPTURE_PAUSE = 0x00000004
};

/* ALLOCATOR_PROPERTIES  [struct, typedef; shared] */
typedef struct _AllocatorProperties {
 long cBuffers;
 long cbBuffer;
 long cbAlign;
 long cbPrefix;
} ALLOCATOR_PROPERTIES;
typedef ALLOCATOR_PROPERTIES *PALLOCATOR_PROPERTIES, *LPALLOCATOR_PROPERTIES;

/* AM_FILESINK_FLAGS  [enum; ce-only; heuristic-prefix] */
typedef enum {
 AM_FILE_OVERWRITE = 0x00000001,
} AM_FILESINK_FLAGS;
typedef AM_FILESINK_FLAGS *PAM_FILESINK_FLAGS, *LPAM_FILESINK_FLAGS;

/* AM_SAMPLE_PROPERTY_FLAGS  [enum, typedef; ce-only; heuristic-prefix] */
enum tagAM_SAMPLE_PROPERTY_FLAGS { 
 AM_SAMPLE_SPLICEPOINT = 0x01, 
 AM_SAMPLE_PREROLL = 0x02, 
 AM_SAMPLE_DATADISCONTINUITY = 0x04, 
 AM_SAMPLE_TYPECHANGED = 0x08, 
 AM_SAMPLE_TIMEVALID = 0x10, 
 AM_SAMPLE_TIMEDISCONTINUITY = 0x40, 
 AM_SAMPLE_FLUSH_ON_PAUSE = 0x80, 
 AM_SAMPLE_STOPVALID = 0x100, 
 AM_SAMPLE_ENDOFSTREAM = 0x200, 
 AM_STREAM_MEDIA = 0, 
 AM_STREAM_CONTROL = 1 
};

/* AM_STREAM_INFO_FLAGS  [enum, typedef; shared; entity-headers] */
typedef enum {
 AM_STREAM_INFO_START_DEFINED = 0x00000001,
 AM_STREAM_INFO_STOP_DEFINED = 0x00000002,
 AM_STREAM_INFO_DISCARDING = 0x00000004,
 AM_STREAM_INFO_STOP_SEND_EXTRA = 0x00000010
} AM_STREAM_INFO_FLAGS;
typedef AM_STREAM_INFO_FLAGS *PAM_STREAM_INFO_FLAGS, *LPAM_STREAM_INFO_FLAGS;

/* AM_VIDEO_RENDERER_MODE  [enum; ce-only; heuristic-prefix] */
typedef enum {
 AM_VIDEO_RENDERER_MODE_DDRAW,
 AM_VIDEO_RENDERER_MODE_GDI
} AM_VIDEO_RENDERER_MODE;
typedef AM_VIDEO_RENDERER_MODE *PAM_VIDEO_RENDERER_MODE, *LPAM_VIDEO_RENDERER_MODE;

/* AMVPSIZE  [struct, typedef; shared] */
typedef struct _AMVPSIZE{
 DWORD dwWidth;
 DWORD dwHeight;
} AMVPSIZE, *LPAMVPSIZE;

/* AnalogVideoStandard  [enum, typedef; shared; entity-headers] */
typedef enum {
 AnalogVideo_None = 0x00000000,
 AnalogVideo_NTSC_M = 0x00000001,
 AnalogVideo_NTSC_M_J = 0x00000002,
 AnalogVideo_NTSC_433 = 0x00000004,
 AnalogVideo_PAL_B = 0x00000010,
 AnalogVideo_PAL_D = 0x00000020,
 AnalogVideo_PAL_H = 0x00000080,
 AnalogVideo_PAL_I = 0x00000100,
 AnalogVideo_PAL_M = 0x00000200,
 AnalogVideo_PAL_N = 0x00000400,
 AnalogVideo_PAL_60 = 0x00000800,
 AnalogVideo_SECAM_B = 0x00001000,
 AnalogVideo_SECAM_D = 0x00002000,
 AnalogVideo_SECAM_G = 0x00004000,
 AnalogVideo_SECAM_H = 0x00008000,
 AnalogVideo_SECAM_K = 0x00010000,
 AnalogVideo_SECAM_K1 = 0x00020000,
 AnalogVideo_SECAM_L = 0x00040000,
 AnalogVideo_SECAM_L1 = 0x00080000,
} AnalogVideoStandard;
typedef AnalogVideoStandard *PAnalogVideoStandard, *LPAnalogVideoStandard;

/* CameraControlFlags  [enum; shared; entity-headers] */
typedef enum{
 CameraControl_Flags_Auto = 0x0001,
 CameraControl_Flags_Manual = 0x0002
} CameraControlFlags;
typedef CameraControlFlags *PCameraControlFlags, *LPCameraControlFlags;

/* CameraControlProperty  [enum; shared; entity-headers] */
typedef enum {
 CameraControl_Pan,
 CameraControl_Tilt,
 CameraControl_Roll,
 CameraControl_Zoom,
 CameraControl_Exposure,
 CameraControl_Iris,
 CameraControl_Focus
 CameraControl_Flash
} CameraControlProperty;
typedef CameraControlProperty *PCameraControlProperty, *LPCameraControlProperty;

/* COLORKEY  [struct, typedef, function; shared] */
typedef struct tagCOLORKEY{
 DWORD KeyType;
 DWORD PaletteIndex;
 COLORREF LowColorValue;
 COLORREF HighColorValue;
} COLORKEY;
typedef COLORKEY *PCOLORKEY, *LPCOLORKEY;

/* CompressionCaps  [enum; shared; entity-headers] */
typedef enum {
 CompressionCaps_CanQuality = 0x01,
 CompressionCaps_CanCrunch = 0x02,
 CompressionCaps_CanKeyFrame = 0x04,
 CompressionCaps_CanBFrame = 0x08,
 CompressionCaps_CanWindow = 0x10
} CompressionCaps;
typedef CompressionCaps *PCompressionCaps, *LPCompressionCaps;

/* FILTER_INFO  [struct, typedef; shared] */
typedef struct _FilterInfo{
 WCHAR achName[128];
 IFilterGraph __RPC_FAR* pGraph;
} FILTER_INFO;
typedef FILTER_INFO *PFILTER_INFO, *LPFILTER_INFO;

/* FILTER_STATE  [enum, typedef; shared; entity-headers] */
typedef enum _FilterState {
 State_Stopped = 0,
 State_Paused = State_Stopped + 1,
 State_Running = State_Paused + 1
} FILTER_STATE;
typedef FILTER_STATE *PFILTER_STATE, *LPFILTER_STATE;

/* PIN_DIRECTION  [enum, typedef; shared; entity-headers] */
typedef enum _PinDirection {
 PINDIR_INPUT,
 PINDIR_OUTPUT
} PIN_DIRECTION;
typedef PIN_DIRECTION *PPIN_DIRECTION, *LPPIN_DIRECTION;

/* POSITION  [struct, typedef; ce-only] */
struct __POSITION { int unused; };
typedef __POSITION* POSITION;

/* QualityMessageType  [enum, typedef; shared; entity-headers] */
typedef enum {
 Famine,
 Flood
} QualityMessageType;
typedef QualityMessageType *PQualityMessageType, *LPQualityMessageType;

/* TIMECODE  [struct, typedef; shared] */
typedef struct tagTIMECODE {
 WORD wFrameRate;
 WORD wFrameFract;
 WORD dwFrames;
}TIMECODE;
typedef TIMECODE *PTIMECODE, *LPTIMECODE;

/* TIMECODE_SAMPLE  [struct, typedef; shared] */
typedef struct tagTIMECODE_SAMPLE {
 LONGLONG qwTick;
 TIMECODE timecode;
 DWORD dwUser;
 DWORD dwFlags;
} TIMECODE_SAMPLE;
typedef TIMECODE_SAMPLE *PTIMECODE_SAMPLE, *LPTIMECODE_SAMPLE;

/* VideoControlFlags  [enum; shared; entity-headers] */
typedef enum tagVideoControlFlags {
 VideoControlFlag_FlipHorizontal = 0x0001,
 VideoControlFlag_FlipVertical = 0x0002,
 VideoControlFlag_ExternalTriggerEnable = 0x0004,
 VideoControlFlag_Trigger = 0x0008
} VideoControlFlags;
typedef VideoControlFlags *PVideoControlFlags, *LPVideoControlFlags;

/* VideoProcAmpFlags  [enum; shared; entity-headers] */
typedef enum tagVideoProcAmpFlags {
 VideoProcAmp_Flags_Auto = 0x0001,
 VideoProcAmp_Flags_Manual = 0x0002,
} VideoProcAmpFlags;
typedef VideoProcAmpFlags *PVideoProcAmpFlags, *LPVideoProcAmpFlags;

/* VideoProcAmpProperty  [enum; shared; entity-headers] */
typedef enum tagVideoProcAmpProperty {
 VideoProcAmp_Brightness,
 VideoProcAmp_Contrast,
 VideoProcAmp_Hue,
 VideoProcAmp_Saturation,
 VideoProcAmp_Sharpness,
 VideoProcAmp_Gamma,
 VideoProcAmp_ColorEnable,
 VideoProcAmp_WhiteBalance,
 VideoProcAmp_BacklightCompensation,
 VideoProcAmp_Gain
} VideoProcAmpProperty;
typedef VideoProcAmpProperty *PVideoProcAmpProperty, *LPVideoProcAmpProperty;

/* AM_MEDIA_TYPE  [struct, typedef; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   majortype */
/*   subtype */
/*   bFixedSizeSamples */
/*   bTemporalCompression */
/*   lSampleSize */
/*   formattype */
/*   pUnk */
/*   cbFormat */
/*   pbFormat */

/* PIN_INFO  [struct, typedef; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   pFilter */
/*   dir */
/*   achName */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400)) /* CE 3.0..399 */

/* IAMDevMem  [function; ce-only; CE 3.0..399; heuristic-prefix] */
HRESULT QueryWriteSync( );
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AddSourceFilter( LPCWSTR lpwstrFileName, LPCWSTR lpwstrFilterName, IbaseFilter **ppFilter );
HRESULT AutoTune( long lChannel, long *plFoundSignal);
HRESULT ChannelMinMax( long *lChannelMin, long *lChannelMax);
HRESULT CheckMemory( const BYTE *pBuffer);
DWORD ColorKey (void );
HRESULT Enable( long lIndex, DWORD dwFlags);
HRESULT GetAllocatorProperties( ALLOCATOR_PROPERTIES* pprop );
HRESULT GetAvailableModes( long *plModes);
HRESULT GetAverageFrameSize( long* plAverageSize);
HRESULT GetDefaultColorKey( COLORKEY *pColorKey);
HRESULT GetDevId( DWORD *pdwDevId);
HRESULT GetDroppedInfo( long lSize, long* plArray, long* plNumCopied);
LONG GetMiscFlags(void);
HRESULT GetNumDropped( long* plDropped);
HRESULT GetNumNotDropped( long* plNotDropped);
HRESULT GetNumberOfCapabilities( int* piCount, int* piSize );
HRESULT GetRange( long Property, long* pMin, long* pMax, long* pSteppingDelta, long* pDefault, long* pCapsFlags );
HRESULT GetStreamCaps( int iIndex, AM_MEDIA_TYPE** pmt, BYTE* pSCC );
HRESULT Length( LONGLONG* pTotal, LONGLONG* pAvailable );
HRESULT Logout(void);
HRESULT NotifyGraphChange( );
HRESULT OnColorKeyChange( COLORKEY *pColorKey);
HRESULT OnPaletteChange( DWORD dwColors, const PALETTEENTRY *pPalette);
HRESULT OnPositionChange( const RECT *pSourceRect, const RECT *pDestinationRect);
HRESULT OverrideFrameSize( long FrameNumber, long Size );
HRESULT OverrideKeyFrame( long FrameNumber );
HRESULT QueryVersion( LONG *pVersion);
HRESULT RenderFile( LPCWSTR lpwstrFile, LPCWSTR lpwstrPlayList);
HRESULT SetDefaultSyncSource(void);
HRESULT SetLogFile( HANDLE hFile);
HRESULT SignalPresent( long *plSignalStrength);
HRESULT StoreAutoTune(void);
HRESULT SuggestAllocatorProperties( const ALLOCATOR_PROPERTIES* pprop );
HRESULT SyncRead( LONGLONG llPosition, LONG lLength, BYTE* pBuffer);
HRESULT WriteSync( );
HRESULT get_AudioFrequency( long *lFreq);
HRESULT get_AvailableTVFormats( long *lAnalogVideoStandard);
HRESULT get_Channel ( long *plChannel, long *plVideoSubChannel, long *plAudioSubChannel);
HRESULT get_ConnectInput ( long *plIndex);
HRESULT get_CountryCode( long *plCountryCode);
HRESULT get_InputType ( long lIndex, TunerInputType *pInputType);
HRESULT get_Mode( AMTunerModeType *plMode);
HRESULT get_NumInputConnections( long *plNumInputConnections);
HRESULT get_PFramesPerKeyFrame( long* pPFramesPerKeyFrame );
HRESULT get_Quality( double* pQuality );
HRESULT get_TVFormat( long *plAnalogVideoStandard);
HRESULT get_TuningSpace( long *plTuningSpace);
HRESULT get_VideoFrequency( long *lFreq);
HRESULT put_Channel( long lChannel, long lVideoSubChannel, long lAudioSubChannel);
HRESULT put_ConnectInput( long lIndex);
HRESULT put_CountryCode( long lCountryCode);
HRESULT put_InputType( long lIndex, TunerInputType InputType);
HRESULT put_KeyFrameRate( long KeyFrameRate );
HRESULT put_Mode( AMTunerModeType lMode);
HRESULT put_PFramesPerKeyFrame( long PFramesPerKeyFrame );
HRESULT put_Quality( double Quality );
HRESULT put_TuningSpace( long lTuningSpace);

#endif /* _DSHOW_ */
