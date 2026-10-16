/* Playlist.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 9 extra decls
 */
#ifndef _PLAYLIST_
#define _PLAYLIST_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT GetFlags( DWORD* pdwFlags );
HRESULT GetItemCount( DWORD* pdwItems );
HRESULT GetRepeatInfo( DWORD* pdwRepeatCount, DWORD* pdwRepeatStart, DWORD* pdwRepeatEnd );
HRESULT GetSourceCount( DWORD* pdwSources );
HRESULT GetSourceEndMarker( DWORD dwSourceIndex, DWORD* pdwMarker );
HRESULT GetSourceStartMarker( DWORD dwSourceIndex, DWORD* pdwMarker );

#endif /* _PLAYLIST_ */
