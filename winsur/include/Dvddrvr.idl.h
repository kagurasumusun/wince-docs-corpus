/* Dvddrvr.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 24 extra decls
 */
#ifndef _DVDDRVR_IDL_
#define _DVDDRVR_IDL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DVD_AUDIOCAP_AC3 0x4000
#define DVD_AUDIOCAP_AC3_KARAOKE 0x0040
#define DVD_AUDIOCAP_DTS 0x0800
#define DVD_AUDIOCAP_DTS_KARAOKE 0x0008
#define DVD_AUDIOCAP_LPCM_KARAOKE 0x0080
#define DVD_AUDIOCAP_MPEG 0x1000
#define DVD_AUDIOCAP_MPEG_KARAOKE 0x0010
#define DVD_AUDIOCAP_SDDS 0x0400
#define DVD_AUDIOCAP_SDDS_KARAOKE 0x0004

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* EDVDAspectRatioMode  [enum; ce-only] */
typedef enum {
 DVD_ASPECT_RATIO_MODE_LETTERBOX,
 DVD_ASPECT_RATIO_MODE_PANSCAN
} EDVDAspectRatioMode;
typedef EDVDAspectRatioMode *PEDVDAspectRatioMode, *LPEDVDAspectRatioMode;

/* EDVDAudioFreq  [enum; ce-only] */
typedef enum {
 DVD_AUDIO_FREQ_48KHZ,
 DVD_AUDIO_FREQ_96KHZ
} EDVDAudioFreq;
typedef EDVDAudioFreq *PEDVDAudioFreq, *LPEDVDAudioFreq;

/* EDVDAudioStreamType  [enum; ce-only] */
typedef enum {
 DVD_AUDIO_TYPE_AC3 = 2,
 DVD_AUDIO_TYPE_MPEG,
 DVD_AUDIO_TYPE_LPCM,
 DVD_AUDIO_TYPE_DTS,
 DVD_AUDIO_TYPE_SDDS
} EDVDAudioStreamType;
typedef EDVDAudioStreamType *PEDVDAudioStreamType, *LPEDVDAudioStreamType;

/* EDVDDisplayAspectRatio  [enum; ce-only] */
typedef enum {
 DVD_DISPLAY_ASPECT_4x3 = 0,
 DVD_DISPLAY_ASPECT_16x9 = 0x3
} EDVDDisplayAspectRatio;
typedef EDVDDisplayAspectRatio *PEDVDDisplayAspectRatio, *LPEDVDDisplayAspectRatio;

/* EDVDLpcmQuantization  [enum; ce-only] */
typedef enum {
 DVD_LPCM_16,
 DVD_LPCM_20,
 DVD_LPCM_24
} EDVDLpcmQuantization;
typedef EDVDLpcmQuantization *PEDVDLpcmQuantization, *LPEDVDLpcmQuantization;

/* EDVDSyncEventType  [enum; ce-only] */
typedef enum {
 DVD_NAV_PACK_EVENT,
 DVD_HIGHLIGHT_EVENT,
 DVD_PLAYBACK_EVENT,
 DVD_CC_DATA_EVENT
} EDVDSyncEventType;
typedef EDVDSyncEventType *PEDVDSyncEventType, *LPEDVDSyncEventType;

/* EHighlightAction  [enum; ce-only] */
typedef enum {
 HIGHLIGHT_SELECT = 1,
 UNHIGHLIGHT,
 ACTIVATE_BUTTON,
 ACTIVATE_SELECTED,
 SELECT_AUTO_ACTIVATED
} EHighlightAction;
typedef EHighlightAction *PEHighlightAction, *LPEHighlightAction;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AbortAllTransfers();
HRESULT GetAudioCaps(DWORD* pdwCaps);
HRESULT GetDMAChannelCount(DWORD* pdwChannels);
HRESULT GetHighlightedButton(BYTE* buttonNumber);
HRESULT GetMaxOutstandingTransfers(DWORD* pdwTransfers,DWORD* pdwMaxSize);
HRESULT GetPendingTransfersCount(DWORD* pdwPending);
HRESULT Highlight( BYTE buttonNumber, EHighlightAction action, BOOL bRelativeMode );
HRESULT OnDiscontinuity();
HRESULT RegisterSyncEvent( EDVDSyncEventType eType, HANDLE h, void* pDataLock, DWORD dwMaxDataSize, void* pEventData );
HRESULT RequestTransfer( PHYSICAL_ADDRESS physStart, DWORD dwSize,  VOID* pva, DWORD* pdwPending );
HRESULT Scan( BOOL bForward, double dRate, double* dwActual, DWORD* bVobuSkip );
HRESULT SetAPS( DWORD apsType, DWORD* pdwCookie );
HRESULT SetAspectRatioMode(EDVDAspectRatioModeenumAspectRatioMode);
HRESULT SetAudioStreamNumber( int iDecodingNumber );
HRESULT SetAudioStreamType(EDVDAudioStreamTypedwSelectedDecoder);
HRESULT SetBitstreamType( DWORD dwBitstreamType );
HRESULT SetContentAspectRatio(EDVDDisplayAspectRatioenumDisplayAspectRatio);
HRESULT SetDataNotificationThreshold( DWORD dwPendingThreshold );
HRESULT SetDisplayAspectRatio(EDVDDisplayAspectRatioenumDisplayAspectRatio);
HRESULT SetSubpictureStreamNumber( int iDecodingNumber );
HRESULT Slow( BOOL bForward, double dRate, double* dwActual );
HRESULT UnregisterSyncEvent( EDVDSyncEventType etype, HANDLE h );

#endif /* _DVDDRVR_IDL_ */
