/* Dvdata.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 45 constants, 17 declarations, 0 outlines, 0 base types, 0 extra macros, 80 extra decls
 */
#ifndef _DVDATA_
#define _DVDATA_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DVD_MENU_ANGLE 4
#define DVD_MENU_AUDIO 3
#define DVD_MENU_PTT 5
#define DVD_MENU_ROOT 1
#define DVD_MENU_SUBPICTURE 2
#define DVD_MENU_TITLE 0
#define DVD_NAVSTATREQ_VOLUME_BIT 1
#define DVD_PROGRAM_NEXT 1
#define DVD_PROGRAM_PREVIOUS 0
#define DVD_PROGRAM_TOP 2
#define DVD_SCANCAP_BACKWARD_SCAN 0x8
#define DVD_SCANCAP_BACKWARD_SINGLE 0x20
#define DVD_SCANCAP_BACKWARD_SLOW 0x10
#define DVD_SCANCAP_FORWARD_SCAN 0x1
#define DVD_SCANCAP_FORWARD_SINGLE 0x4
#define DVD_SCANCAP_FORWARD_SLOW 0x2
#define DVD_SELECT_LEFT 3
#define DVD_SELECT_LOWER 2
#define DVD_SELECT_RIGHT 1
#define DVD_SELECT_UPPER 0
#define DVD_SYSTEM_SPACE_BIT 1
#define GoUp_PGCN 2
#define Next_PGCN 0
#define Previous_PGCN 1
#define SPRM_AGLN 3
#define SPRM_ASTN 1
#define SPRM_CTY_CD 12
#define SPRM_HL_BTNN 8
#define SPRM_INI_LCD_AST 16
#define SPRM_INI_LCD_EXT_AST 17
#define SPRM_INI_LCD_EXT_SPST 19
#define SPRM_INI_LCD_SPST 18
#define SPRM_M_LCD 0
#define SPRM_NV_TMR 9
#define SPRM_NV_TMR_PGCN 10
#define SPRM_P_AMXMD 11
#define SPRM_P_CFG_AUDIO 15
#define SPRM_P_CFG_VIDEO 14
#define SPRM_PTL_LVL 13
#define SPRM_PTTN 7
#define SPRM_REGION 20
#define SPRM_SPSTN 2
#define SPRM_TT_PGCN 6
#define SPRM_TTN 4
#define SPRM_VTS_TTN 5

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* UNICODE_PATH  [macro; ce-only] */
#define MAX_PATH 128
typedef [string] WCHAR UNICODE_PATH [MAX_PATH];

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* EDVDDomainType  [enum; ce-only] */
typedef enum {
 DVD_FP_DOM,
 DVD_VMGM_DOM,
 DVD_VTSM_DOM,
 DVD_TT_DOM
} EDVDDomainType;
typedef EDVDDomainType *PEDVDDomainType, *LPEDVDDomainType;

/* ENavCmdArea  [enum; ce-only] */
typedef enum {
 DVD_PRE_CMD = 0,
 DVD_POST_CMD = 1,
 DVD_CELL_CMD = 2
} ENavCmdArea;
typedef ENavCmdArea *PENavCmdArea, *LPENavCmdArea;

/* EPGCLinkType  [enum; ce-only] */
typedef enum {
 DVD_NEXT_PGC,
 DVD_PREVIOUS_PGC,
 DVD_UP_PGC
} EPGCLinkType;
typedef EPGCLinkType *PEPGCLinkType, *LPEPGCLinkType;

/* EPGCPlaybackMode  [enum; ce-only] */
typedef enum {
 DVD_PLAYMODE_SEQUENTIAL,
 DVD_PLAYMODE_RANDOM,
 DVD_PLAYMODE_SHUFFLE
} EPGCPlaybackMode;
typedef EPGCPlaybackMode *PEPGCPlaybackMode, *LPEPGCPlaybackMode;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT EnumerateTextLanguageUnits( IEnumDVD_TEXT_LANGUAGE_UNIT** ppEnum );
HRESULT GetAudioAttr( UINT nStreamNo, DVD_AUDIO_STREAM_ATTR* pAudioAttr );
HRESULT GetPOSCode( DVD_POS_CODE* pPOSCode );
HRESULT GetProviderID( DVD_PROVIDER_ID* pProvider );
HRESULT GetRecordingVideoInfo( DVD_ISRC* pVideo );
HRESULT NotifyNewPCI();
HRESULT ReaderLock(void);
HRESULT ReaderUnlock(void);
HRESULT ReleaseMem( HRESULT* bufptr );

#endif /* _DVDATA_ */
