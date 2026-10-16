/* CcTransport.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _CCTRANSPORT_IDL_
#define _CCTRANSPORT_IDL_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT Bandwidth( DWORD* pdwRate);
HRESULT MTU( DWORD* pdwMTU);
HRESULT Recv( DWORD dwTimeout, BYTE*pBuffer, DWORD*pcbBuffer );

#endif /* _CCTRANSPORT_IDL_ */
