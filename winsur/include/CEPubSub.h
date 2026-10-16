/* CEPubSub.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 4 extra decls
 */
#ifndef _CEPUBSUB_
#define _CEPUBSUB_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT Control( DWORD dwControl, DWORD dwBufSize, BYTE* pbData );
HRESULT StartPublishing();
HRESULT StopPublishing();

#endif /* _CEPUBSUB_ */
