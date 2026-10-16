/* wmp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 44 extra decls
 */
#ifndef _WMP_
#define _WMP_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void AudioLanguageChange( long LangID );
void Click( short nButton, short nShiftState, long fX, long fY );
void CurrentPlaylistChange( WMPPlaylistChangeEventType change );
void DoubleClick( short nButton, short nShiftState, long fX, long fY );
void Error();
void KeyDown( short nKeyCode, short nShiftState );
void KeyPress( short nKeyAscii );
void KeyUp( short nKeyCode, short nShiftState );
void MarkerHit( long MarkerNum );
void MouseDown( short nButton, short nShiftState, long fX, long fY );
void MouseMove( short nButton, short nShiftState, long fX, long fY );
void MouseUp( short nButton, short nShiftState, long fX, long fY );
void NewStream();
void OpenStateChange( long NewState );
void PlayStateChange( long NewState );
void PositionChange( double oldPosition, double newPosition );
void StatusChange();
HRESULT get_attributeCount( long* plCount );
HRESULT get_balance( long* plBalance );
HRESULT get_count( long* plCount );
HRESULT get_currentPosition( double* pdCurrentPosition );
HRESULT get_defaultAudioLanguage( long* plLangID );
HRESULT get_duration( double* pDuration );
HRESULT get_errorCount( long* plNumErrors );
HRESULT get_imageSourceHeight( long* pHeight );
HRESULT get_imageSourceWidth( long* pWidth );
HRESULT get_openState( WMPOpenState* pwmpos );
HRESULT get_playState( WMPPlayState* pwmpps );
HRESULT get_volume( long* plVolume );
HRESULT put_balance( long lBalance );
HRESULT put_currentPosition( double dCurrentPosition );
HRESULT put_volume( long lVolume );

#endif /* _WMP_ */
