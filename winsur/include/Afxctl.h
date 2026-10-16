/* Afxctl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 70 extra decls
 */
#ifndef _AFXCTL_
#define _AFXCTL_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL AmbientShowGrabHandles( );
BOOL AmbientShowHatching( );
short AmbientTextAlign( );
BOOL AmbientUIDead( );
BOOL AmbientUserMode( );
BOOL ClipCaretRect( LPRECT lpRect );
void ControlInfoChanged( );
void DoClick( );
void EnableSimpleFrame( );
BOOL ExchangeExtent( CPropExchange* pPX );
void ExchangeStockProps( CPropExchange* pPX );
void FireClick( );
void FireDblClick( );
void FireKeyDown( USHORT* pnChar, short nShiftState );
void FireKeyPress( USHORT* pnChar );
void FireKeyUp( USHORT* pnChar, short nShiftState );
void FireReadyStateChange( );
short GetAppearance ( );
short GetBorderStyle( );
void GetControlSize( int* pcx, int* pcy );
BOOL GetControlStatus( UINT nID );
BOOL GetEnabled( );
HFONT GetFontHandle( );
void GetFontTextMetrics( LPTEXTMETRIC lptm, CFontHolder& fontHolder );
void GetNotSupported( );
long GetReadyState( );
BOOL GetRectInContainer( LPRECT lpRect );
void GetStockTextMetrics( LPTEXTMETRIC lptm );
void IgnoreApply( UINT nID );
void InternalSetReadyState( long lNewReadyState );
BOOL IsConvertingVBX( );
BOOL IsOptimizedDraw( );
void PostModalDialog( );
void PreModalDialog( );
void RecreateControlWindow( );
void ResetStockProps( );
void ResetVersion( DWORD dwVersionDefault );
void SerializeExtent( CArchive& ar );
void SerializeStockProps( CArchive& ar );
void SetAppearance ( short sAppearance );
void SetBorderStyle( short sBorderStyle );
BOOL SetControlSize( int cx, int cy );
BOOL SetControlStatus( UINT nID, BOOL IsDirty );
void SetDialogResource( HGLOBAL hDialog );
void SetEnabled( BOOL bEnabled );
void SetInitialSize( int cx, int cy );
void SetNotPermitted( );
void SetNotSupported( );
void SetPageName( LPCTSTR lpszPageName );
BOOL WillAmbientsBeValidDuringLoad( );

#endif /* _AFXCTL_ */
