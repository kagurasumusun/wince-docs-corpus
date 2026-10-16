/* Dmusici.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 24 declarations, 1 outlines, 0 base types, 0 extra macros, 43 extra decls
 */
#ifndef _DMUSICI_
#define _DMUSICI_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* DMUS_PMSG  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DMUS_NOTEF_FLAGS  [enum; ce-only] */
typedef enum enumDMUS_NOTEF_FLAGS {
 DMUS_NOTEF_NOTEON = 1,
} DMUS_NOTEF_FLAGS;
typedef DMUS_NOTEF_FLAGS *PDMUS_NOTEF_FLAGS, *LPDMUS_NOTEF_FLAGS;

/* DMUS_PLAYMODE_FLAGS  [enum; ce-only] */
typedef enum enumDMUS_PLAYMODE_FLAGS {
 DMUS_PLAYMODE_KEY_ROOT = 1,
 DMUS_PLAYMODE_CHORD_ROOT = 2,
 DMUS_PLAYMODE_SCALE_INTERVALS = 4,
 DMUS_PLAYMODE_CHORD_INTERVALS = 8,
 DMUS_PLAYMODE_NONE = 16,
} DMUS_PLAYMODE_FLAGS;
typedef DMUS_PLAYMODE_FLAGS *PDMUS_PLAYMODE_FLAGS, *LPDMUS_PLAYMODE_FLAGS;

/* DMUS_PMSGF_FLAGS  [enum; ce-only] */
typedef enum enumDMUS_PMSGF_FLAGS {
 DMUS_PMSGF_REFTIME = 1,
 DMUS_PMSGF_MUSICTIME = 2,
 DMUS_PMSGF_TOOL_IMMEDIATE = 4,
 DMUS_PMSGF_TOOL_QUEUE = 8,
 DMUS_PMSGF_TOOL_ATTIME = 16,
 DMUS_PMSGF_TOOL_FLUSH = 32
} DMUS_PMSGF_FLAGS;
typedef DMUS_PMSGF_FLAGS *PDMUS_PMSGF_FLAGS, *LPDMUS_PMSGF_FLAGS;

/* DMUS_PMSGT_TYPES  [enum; ce-only] */
typedef enum enumDMUS_PMSGT_TYPES {
 DMUS_PMSGT_MIDI = 0,
 DMUS_PMSGT_NOTE = 1,
 DMUS_PMSGT_SYSEX = 2,
 DMUS_PMSGT_NOTIFICATION = 3,
 DMUS_PMSGT_TEMPO = 4,
 DMUS_PMSGT_CURVE = 5,
 DMUS_PMSGT_TIMESIG = 6,
 DMUS_PMSGT_PATCH = 7,
 DMUS_PMSGT_TRANSPOSE = 8,
 DMUS_PMSGT_CHANNEL_PRIORITY = 9,
 DMUS_PMSGT_STOP = 10,
 DMUS_PMSGT_DIRTY = 11,
 DMUS_PMSGT_USER = 255
} DMUS_PMSGT_TYPES;
typedef DMUS_PMSGT_TYPES *PDMUS_PMSGT_TYPES, *LPDMUS_PMSGT_TYPES;

/* DMUS_SEGF_FLAGS  [enum; ce-only] */
typedef enum enumDMUS_SEGF_FLAGS {
 DMUS_SEGF_REFTIME = 64,
 DMUS_SEGF_SECONDARY = 128,
 DMUS_SEGF_QUEUE = 256,
 DMUS_SEGF_CONTROL = 512
 DMUS_SEGF_AFTERPREPARETIME = 1<<10,
 DMUS_SEGF_GRID = 1<<11,
 DMUS_SEGF_BEAT = 1<<12,
 DMUS_SEGF_MEASURE = 1<<13,
 DMUS_SEGF_DEFAULT = 1<<14,
 DMUS_SEGF_NOINVALIDATE = 1<<15,
} DMUS_SEGF_FLAGS;
typedef DMUS_SEGF_FLAGS *PDMUS_SEGF_FLAGS, *LPDMUS_SEGF_FLAGS;

/* DMUS_SHAPET_TYPES  [enum; ce-only] */
typedef enum enumDMUS_SHAPET_TYPES {
 DMUS_SHAPET_FALLING = 0,
 DMUS_SHAPET_LEVEL = 1,
 DMUS_SHAPET_LOOPABLE = 2,
 DMUS_SHAPET_LOUD = 3,
 DMUS_SHAPET_QUIET = 4,
 DMUS_SHAPET_PEAKING = 5,
 DMUS_SHAPET_RANDOM = 6,
 DMUS_SHAPET_RISING = 7,
 DMUS_SHAPET_SONG = 8
} DMUS_SHAPET_TYPES;
typedef DMUS_SHAPET_TYPES *PDMUS_SHAPET_TYPES, *LPDMUS_SHAPET_TYPES;

/* DMUS_SUBCHORD  [struct; ce-only] */
typedef struct {
 DWORD dwChordPattern;
 DWORD dwScalePattern;
 DWORD dwInversionPoints;
 DWORD dwLevels;
 BYTE bChordRoot;
 BYTE bScaleRoot;
} DMUS_SUBCHORD;
typedef DMUS_SUBCHORD *PDMUS_SUBCHORD, *LPDMUS_SUBCHORD;

/* DMUS_SYNTHSTATS  [struct; ce-only] */
typedef struct DMUS_SYNTHSTATS {
 DWORD dwSize;
 DWORD dwValidStats;
 DWORD dwVoices;
 DWORD dwTotalCPU;
 DWORD dwCPUPerVoice;
 DWORD dwLostNotes;
 DWORD dwFreeMemory;
 long lPeakVolume;
} DMUS_SYNTHSTATS, *LPDMUS_SYNTHSTATS;

/* DMUS_TIME_RESOLVE_FLAGS  [enum; ce-only] */
typedef enum enumDMUS_TIME_RESOLVE_FLAGS {
 DMUS_TIME_RESOLVE_AFTERPREPARETIME = 1<<10,
 DMUS_TIME_RESOLVE_GRID = 1<<11,
 DMUS_TIME_RESOLVE_BEAT = 1<<12,
 DMUS_TIME_RESOLVE_MEASURE = 1<<13
} DMUS_TIME_RESOLVE_FLAGS;
typedef DMUS_TIME_RESOLVE_FLAGS *PDMUS_TIME_RESOLVE_FLAGS, *LPDMUS_TIME_RESOLVE_FLAGS;

/* DMUS_TRACKF_FLAGS  [enum; ce-only] */
typedef enum enumDMUS_TRACKF_FLAGS {
 DMUS_TRACKF_SEEK = 1,
 DMUS_TRACKF_LOOP = 2,
 DMUS_TRACKF_START = 4,
 DMUS_TRACKF_FLUSH = 8,
 DMUS_TRACKF_DIRTY = 16
} DMUS_TRACKF_FLAGS;
typedef DMUS_TRACKF_FLAGS *PDMUS_TRACKF_FLAGS, *LPDMUS_TRACKF_FLAGS;

/* DMUS_VERSION  [struct; ce-only] */
typedef struct _DMUS_VERSION {
 DWORD dwVersionMS;
 DWORD dwVersionLS;
} DMUS_VERSION, FAR *LPDMUS_VERSION;

/* LPDMUS_BAND  [extra typedef] */
typedef IDirectMusicBand __RPC_FAR *LPDMUS_BAND;

/* LPDMUS_LOADER  [extra typedef] */
typedef IDirectMusicLoader __RPC_FAR *LPDMUS_LOADER;

/* LPDMUS_OBJECT  [extra typedef] */
typedef IDirectMusicObject __RPC_FAR *LPDMUS_OBJECT;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AllocPMsg( ULONG cb, DMUS_PMSG** ppPMSG );
HRESULT CloseDown();
HRESULT FreePMsg( DMUS_PMSG* pPMSG );
HRESULT GetBumperLength( DWORD* pdwMilliSeconds );
HRESULT GetNotificationPMsg( DMUS_NOTIFICATION_PMSG** ppNotificationPMsg );
HRESULT GetPatch( DWORD* pdwPatch );
HRESULT GetPrepareTime( DWORD* pdwMilliSeconds );
HRESULT GetRepeats( DWORD* pdwRepeats );
HRESULT GetScale( DWORD* pdwScale );
HRESULT SendPMsg( DMUS_PMSG* pPMSG );
HRESULT SetBumperLength( DWORD dwMilliSeconds );
HRESULT SetDescriptor( LPDMUS_OBJECTDESC pDesc );
HRESULT SetPrepareTime( DWORD dwMilliSeconds );
HRESULT StampPMsg( DMUS_PMSG* pPMSG );

#endif /* _DMUSICI_ */
