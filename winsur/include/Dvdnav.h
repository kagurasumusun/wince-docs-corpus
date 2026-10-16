/* Dvdnav.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 37 extra decls
 */
#ifndef _DVDNAV_
#define _DVDNAV_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* EDDVDPlaybackState  [enum; ce-only] */
typedef enum {
 DVD_STOPPED,
 DVD_PAUSED,
 DVD_STILLED,
 DVD_NORMAL_PLAY,
 DVD_FORWARD_SCAN,
 DVD_FORWARD_SLOW,
 DVD_FORWARD_SINGLE,
 DVD_BACKWARD_SCAN,
 DVD_BACKWARD_SLOW,
 DVD_BACKWARD_SINGLE
} EDDVDPlaybackState;
typedef EDDVDPlaybackState *PEDDVDPlaybackState, *LPEDDVDPlaybackState;

/* EDVDNavException  [enum; ce-only] */
typedef enum {
 InsufficientParentalLevel,
 FatalNavigationError
} EDVDNavException;
typedef EDVDNavException *PEDVDNavException, *LPEDVDNavException;

/* EDVDSParamEvent  [enum; ce-only] */
typedef enum {
 InitialAccess,
 TitlePartTimePlay,
 MenuCallToVmgmDom,
 MenuCallToVtsmDom
} EDVDSParamEvent;
typedef EDVDSParamEvent *PEDVDSParamEvent, *LPEDVDSParamEvent;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT BackwardScan( double dblSpeed );
HRESULT ButonSelectAndActivate( BYTE byteButtonNumber );
HRESULT ButtonActivate(void);
HRESULT ButtonSelect( BYTE byteDirection );
HRESULT ButtonSelectDirect( BYTE byteButtonNumber );
HRESULT ChangeAngel( BYTE byteAngleNumber );
HRESULT ChangeAudioStream( BYTE byteStreamNumber );
HRESULT ChangeSubPictureStream( BYTE streamNumber, BOOL bDisplayFlag );
HRESULT ForwardScan( double dblSpeed );
HRESULT GetPlaybackState( EDDVDPlaybackState* peState );
HRESULT InitializeSystemParameters( EDVDSParamEvent eventCode);
HRESULT ManuLanguageSelect( USHORT uhLanguageCode );
HRESULT MenuCall( BYTE byteMenu_ID );
HRESULT OnDiskReadError( DWORD osCode );
HRESULT OnGOPUserData( DVDUserGOPData* pData );
HRESULT OnNavigationException( EDVDNavException excCode );
HRESULT ParentalCountrySelect( USHORT uhCountryCode );
HRESULT ParentalLevelSelect( BYTE byteLevel );
HRESULT PartPlay( BYTE byteTitleNumber, USHORT uhPartOfTheTitle );
HRESULT ProgramSearch( BYTE byteProgramType );
HRESULT Resume(void);
HRESULT StillOff(void);
HRESULT TimePlay( USHORT uhPartOfTheTitle );
HRESULT TimeSearch( UINT uiBCDTime );
HRESULT TitlePlay( BYTE byteTitleNumber );
HRESULT UseRenderer( WCHAR* pszRendererName );
HRESULT VideoPresentationModeChange( USHORT uhVideoMode );

#endif /* _DVDNAV_ */
