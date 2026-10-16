/* TileProxy.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 21 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _TILEPROXY_
#define _TILEPROXY_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* CreateTileProxy  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT CreateTileProxy(
 HWND hParentWnd,
 HWND hHtmlWnd,
 WNDPROC pfnWndProc,
 LPVOID pCreateParam,
 HANDLE* phTileProxy);

/* ReleaseTileProxy  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT ReleaseTileProxy(
 HANDLE hTileProxy);

/* TPChangeZoom  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPChangeZoom(
 HANDLE hTileProxy,
 POINT ptHitPoint, 
 RECT* pZoomRect, 
 BOOL bAllowVerticalZoom);

/* TPChangeZoomScale  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPChangeZoomScale(
 HANDLE hTileProxy,
 float fScale);

/* TPGetHostWindow  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPGetHostWindow(
 HANDLE hTileProxy,
 HWND* phWnd);

/* TPGetIsChanging  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPGetIsChanging(
 HANDLE hTileProxy,
 BOOL* pIsChanging);

/* TPGetViewDocSize  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPGetViewDocSize(
 HANDLE hTileProxy,
 SIZE* pDocSize);

/* TPGetViewPosition  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPGetViewPosition(
 HANDLE hTileProxy,
 float* px,
 float* py);

/* TPGetViewScale  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPGetViewScale(
 HANDLE hTileProxy,
 float* pViewscale);

/* TPGetViewVisBounds  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPGetViewVisBounds(
 HANDLE hTileProxy,
 RECT* pRect);

/* TPGetWaitEvent  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPGetWaitEvent(
 HANDLE hTileProxy,
 HANDLE* phEvent);

/* TPRedraw  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPRedraw(
 HANDLE hTileProxy);

/* TPSetHtmlWindow  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPSetHtmlWindow(
 HANDLE hTileProxy,
 HWND hWnd);

/* TPSetPageChanged  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPSetPageChanged(
 HANDLE hTileProxy);

/* TPSetView  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPSetView(
 HANDLE hTileProxy,
 POINT ptScrollPosition,
 float fZoomFactor);

/* TPSetViewPosition  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPSetViewPosition(
 HANDLE hTileProxy,
 float x,
 float y);

/* TPShowTileWindow  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPShowTileWindow(
 __in HANDLE hTileProxy,
 __in BOOL bShow);

/* TPUpdate  [function; ce-only; CE 6.0..699; tileengine.dll] */
HRESULT TPUpdate(
 HANDLE hTileProxy);
#endif /* _WIN32_WCE */

#endif /* _TILEPROXY_ */
