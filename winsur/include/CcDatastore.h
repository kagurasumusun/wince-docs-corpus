/* CcDatastore.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 11 extra decls
 */
#ifndef _CCDATASTORE_
#define _CCDATASTORE_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AddFileContainer()
HRESULT AddPropertyContainer()
HRESULT ClearOSImage()
HRESULT ClearServiceMap( BSTRin_bstrServiceCategoryID);
HRESULT GetOSImage( HRESULT GetOSImage );
HRESULT RegisterRefreshEvent( BSTRin_bstrEventName);
HRESULT SetOSImage( BSTRin_bstrOSImage);
HRESULT SetServiceMap( BSTRin_bstrServiceCategoryID, BSTRin_bstrServiceInfoID);
HRESULT UnregisterRefreshEvent()

#endif /* _CCDATASTORE_ */
