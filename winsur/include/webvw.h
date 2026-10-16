/* webvw.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 49 extra decls
 */
#ifndef _WEBVW_
#define _WEBVW_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void DownloadBegin(void);
void DownloadComplete(void);
void OnProgressChange( long lProgress, long lProgressMax);
void OnQuit(void);
void OnVisible(void);
HRESULT get_Busy(BOOL* pVal);
HRESULT get_CBrowserPointer( long* pVal);
HRESULT get_LayoutHeight( int* piLayoutHeight);
HRESULT get_LayoutWidth( int* piLayoutWidth);
HRESULT get_MarginHeight( long* pVal);
HRESULT get_MarginWidth( long* pVal);
HRESULT get_ScrollStyle ( long* pVal);
HRESULT get_SelectedCodepage( long* pVal);
HRESULT get_ZoomLevel( DWORD* pdwZoomLevel);
HRESULT put_MarginHeight( long newVal);
HRESULT put_MarginWidth( long newVal);
HRESULT put_ScrollStyle ( long newVal);
HRESULT put_SelectedCodepage( long newVal);
HRESULT put_ZoomLevel( DWORD dwZoomLevel);

#endif /* _WEBVW_ */
