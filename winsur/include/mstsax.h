/* mstsax.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 8 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 79 extra decls
 */
#ifndef _MSTSAX_
#define _MSTSAX_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define TS_PERF_DISABLE_CURSOR_SHADOW 0x00000020
#define TS_PERF_DISABLE_CURSORSETTINGS 0x00000040
#define TS_PERF_DISABLE_FULLWINDOWDRAG 0x00000002
#define TS_PERF_DISABLE_MENUANIMATIONS 0x00000004
#define TS_PERF_DISABLE_NOTHING 0x00000000
#define TS_PERF_DISABLE_THEMING 0x00000008
#define TS_PERF_DISABLE_WALLPAPER 0x00000001
#define TS_PERF_ENABLE_ENHANCED_GRAPHICS 0x00000010

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT get_AcceleratorPassthrough( LONG *pacceleratorPassthrough );
HRESULT get_BitmapPersistence( LONG *pbitmapPersistence );
HRESULT get_BitmapVirtualCache16BppSize( LONG *pBitmapVirtualCache16BppSize );
HRESULT get_BitmapVirtualCacheSize( LONG *pbitmapVirtualCacheSize );
HRESULT get_DedicatedTerminal( LONG *pdedicatedTerminal );
HRESULT get_DisableCtrlAltDel( LONG *pdisableCtrlAltDel );
HRESULT get_HotKeyAltShiftTab( LONG *photKeyAltShiftTab );
HRESULT get_HotKeyAltSpace( LONG *photKeyAltSpace );
HRESULT get_HotKeyCtrlEsc( LONG *photKeyCtrlEsc );
HRESULT get_HotKeyFullScreen( LONG *photKeyFullScreen );
HRESULT get_InputEventsAtOnce( LONG *pinputEventsAtOnce );
HRESULT get_KeyboardFunctionKey( LONG *pkeyboardFunctionKey );
HRESULT get_KeyboardSubType( LONG *pkeyboardSubType );
HRESULT get_KeyboardType( LONG *pkeyboardType );
HRESULT get_MaximizeShell( LONG *pmaximizeShell );
HRESULT get_MinutesToIdleTimeout( LONG *pminutesToIdleTimeout );
HRESULT get_NumBitmapCaches( LONG *pnumBitmapCaches );
HRESULT get_PerformanceFlags( LONG *pDisableList );
HRESULT get_RDPPort( LONG *prdpPort );
HRESULT get_ScaleBitmapCachesByBPP( LONG *pbScale );
HRESULT get_ShadowBitmap( LONG *pshadowBitmap );
HRESULT get_SmoothScroll( LONG *psmoothScroll );
HRESULT get_keepAliveInterval( LONG *pkeepAliveInterval );
HRESULT get_maxEventCount( LONG *pmaxEventCount );
HRESULT get_minInputSendInterval( LONG *pminInputSendInterval );
HRESULT get_orderDrawThreshold( LONG *porderDrawThreshold );
HRESULT get_overallConnectionTimeout( LONG *poverallConnectionTimeout );
HRESULT get_shutdownTimeout( LONG *pshutdownTimeout );
HRESULT get_singleConnectionTimeout( LONG *psingleConnectionTimeout );
HRESULT put_AcceleratorPassthrough( LONG acceleratorPassthrough );
HRESULT put_BitmapCacheSize( LONG bitmapCacheSize );
HRESULT put_BitmapVirtualCache16BppSize( LONG bitmapVirtualCache16BppSize );
HRESULT put_BitmapVirtualCache24BppSize( LONG bitmapVirtualCache24BppSize );
HRESULT put_BitmapVirtualCacheSize( LONG bitmapVirtualCacheSize );
HRESULT put_DedicatedTerminal( LONG dedicatedTerminal );
HRESULT put_DisableCtrlAltDel( LONG disableCtrlAltDel );
HRESULT put_DoubleClickDetect( LONG doubleClickDetect );
HRESULT put_EnableMouse( LONG enableMouse );
HRESULT put_EnableWindowsKey( LONG enableWindowsKey );
HRESULT put_HotKeyAltEsc( LONG hotKeyAltEsc );
HRESULT put_HotKeyAltShiftTab( LONG hotKeyAltShiftTab );
HRESULT put_HotKeyAltSpace( LONG hotKeyAltSpace );
HRESULT put_HotKeyAltTab( LONG hotKeyAltTab );
HRESULT put_HotKeyCtrlAltDel( LONG hotKeyCtrlAltDel );
HRESULT put_HotKeyCtrlEsc( LONG hotKeyCtrlEsc );
HRESULT put_HotKeyFullScreen( LONG hotKeyFullScreen );
HRESULT put_InputEventsAtOnce( LONG inputEventsAtOnce );
HRESULT put_KeyboardFunctionKey( LONG keyboardFunctionKey );
HRESULT put_KeyboardSubType( LONG keyboardSubType );
HRESULT put_KeyboardType( LONG keyboardType );
HRESULT put_MaximizeShell( LONG maximizeShell );
HRESULT put_MinutesToIdleTimeout( LONG minutesToIdleTimeout );
HRESULT put_NumBitmapCaches( LONG numBitmapCaches );
HRESULT put_PerformanceFlags( LONG DisableList );
HRESULT put_RDPPort( LONG rdpPort );
HRESULT put_ShadowBitmap( LONG shadowBitmap );
HRESULT put_SmoothScroll( LONG smoothScroll );
HRESULT put_keepAliveInterval( LONG keepAliveInterval );
HRESULT put_minInputSendInterval( LONG minInputSendInterval );
HRESULT put_orderDrawThreshold( LONG orderDrawThreshold );
HRESULT put_overallConnectionTimeout( LONG overallConnectionTimeout );
HRESULT put_shutdownTimeout( LONG shutdownTimeout );
HRESULT put_singleConnectionTimeout( LONG singleConnectionTimeout );

#endif /* _MSTSAX_ */
