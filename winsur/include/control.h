/* control.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 11 extra decls
 */
#ifndef _CONTROL_
#define _CONTROL_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT CancelDefaultHandling( long lEvCode);
HRESULT FreeEventParams( long lEventCode, long lParam1, long lParam2);
HRESULT RestoreDefaultHandling( long lEvCode);
HRESULT SetNotifyFlags( long lNoNotifyFlags);
HRESULT StopWhenReady( );
HRESULT get_Balance( long *plBalance);
HRESULT get_Volume( long *plVolume);
HRESULT put_Balance( long lBalance);
HRESULT put_Volume( long lVolume);

#endif /* _CONTROL_ */
