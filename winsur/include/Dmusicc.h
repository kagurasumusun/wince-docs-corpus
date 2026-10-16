/* Dmusicc.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 2 outlines, 0 base types, 0 extra macros, 22 extra decls
 */
#ifndef _DMUSICC_
#define _DMUSICC_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* IDirectMusicBuffer  [typedef; ce-only; Dmusic.lib] */

/* IDirectMusicPort  [typedef; ce-only; Dmusic.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DMUS_PORTPARAMS  [struct; ce-only] */
typedef struct _DMUS_PORTPARAMS {
 DWORD dwSize;
 DWORD dwValidParams;
 DWORD dwVoices;
 DWORD dwChannelGroups;
 DWORD dwAudioChannels;
 DWORD dwSampleRate;
 DWORD dwEffectFlags;
 DWORD fShare;
} DMUS_PORTPARAMS, *LPDMUS_PORTPARAMS;

/* DMUS_WAVES_REVERB_PARAMS  [struct; ce-only] */
typedef struct _DMUS_WAVES_REVERB_PARAMS {
 float fInGain;
 float fReverbMix;
 float fReverbTime;
 float fHighFreqRTRatio;
} DMUS_WAVES_REVERB_PARAMS;
typedef DMUS_WAVES_REVERB_PARAMS *PDMUS_WAVES_REVERB_PARAMS, *LPDMUS_WAVES_REVERB_PARAMS;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT EnumInstrument( DWORD dwIndex, DWORD* pdwPatch, LPWSTR pwszName, DWORD dwNameLen );
HRESULT GetAppend( DWORD* pdwAppend );
HRESULT GetChannelPriority( DWORD dwChannelGroup, DWORD dwChannel, LPDWORD pdwPriority );
HRESULT GetDLId( DWORD* pdwStartDLId, DWORD dwCount );
HRESULT GetMaxBytes( LPDWORD pcb );
HRESULT GetRawBufferPtr( LPBYTE* ppData );
HRESULT GetUsedBytes( LPDWORD pcb );
HRESULT ResetReadPtr()
HRESULT SetChannelPriority( DWORD dwChannelGroup, DWORD dwChannel, DWORD dwPriority );
HRESULT SetNumChannelGroups( DWORD dwChannelGroups );
HRESULT SetPatch( DWORD dwPatch );
HRESULT SetReadNotificationHandle( HANDLE hEvent );
HRESULT SetUsedBytes( DWORD cb );

#endif /* _DMUSICC_ */
