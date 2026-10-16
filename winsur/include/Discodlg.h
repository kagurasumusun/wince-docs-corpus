/* Discodlg.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 35 extra decls
 */
#ifndef _DISCODLG_
#define _DISCODLG_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT NotifyRedirectDeviceChange( WPARAM wParam, LPARAM lParam );
VOID OnConnected();
VOID OnConnecting();
VOID OnDisconnected(  long discReason  );
VOID OnFatalError(  long errorCode  );
VOID OnIdleTimeoutNotification();
VOID OnLoginComplete();
VOID OnRequestContainerMinimize();
VOID OnWarning(  long warningCode  );
HRESULT RequestClose( ControlCloseStatus* pCloseStatus );
HRESULT ResetPassword();
HRESULT get_BitmapPeristence( long* pBitmapPersistence );
HRESULT get_CipherStrength( LONG* pCipherStrength );
HRESULT get_Compress( long* pCompress );
HRESULT get_Connected( short* pIsConnected );
HRESULT get_ContainerHandledFullScreen( BOOL* pContainerHandledFullScreen );
HRESULT get_DesktopHeight( LONG* pVal );
HRESULT get_DesktopWidth( LONG* pVal );
HRESULT get_DisableRdpdr( BOOL* pDisableRdpdr );
HRESULT get_ExtendedDisconnectReason( ExtendedDisconnectReasonCode* pExtendedDisconnectReason );
HRESULT get_HorizontalScrollBarVisible( BOOL* pfHScrollVisible );
HRESULT get_KeyboardHookMode( LONG *pkeyboardHookMode );
HRESULT get_VerticalScrollBarVisible( BOOL* pfVScrollVisible );
HRESULT get_allowBackgroundInput( long* pallowBackgroundInput );
HRESULT put_AudioRedirectionMode( LONG audioRedirectionMode );
HRESULT put_BitmapPersistence( long bitmapPeristence );
HRESULT put_ColorDepth( LONG colorDepth) ;
HRESULT put_Compress( long compress );
HRESULT put_ContainerHandledFullScreen( BOOL containerHandledFullScreen );
HRESULT put_DisableRdpdr( BOOL DisableRdpdr );
HRESULT put_IconIndex( LONG IconIndex );
HRESULT put_KeyboardHookMode( LONG keyboardHookMode );
HRESULT put_allowBackgroundInput( long allowBackgroundInput );

#endif /* _DISCODLG_ */
