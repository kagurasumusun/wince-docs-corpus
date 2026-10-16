/* Upnp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 0 declarations, 10 outlines, 0 base types, 0 extra macros, 9 extra decls
 */
#ifndef _UPNP_
#define _UPNP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SDT_STRING 0

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* IUPnPDescriptionDocument  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPDescriptionDocumentCallback  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPDevice  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPDeviceDocumentAccess  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPDeviceFinder  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPDeviceFinderCallback  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPDevices  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPService  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPServiceCallback  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPServices  [interface; shared; CE 5.0..599; Uuid.lib] */
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT CancelAsyncFind( LONG lFindData );
HRESULT LoadComplete( HRESULT hrLoadResult );
HRESULT SearchComplete( LONG lFindData );
HRESULT StartAsyncFind( LONG lFindData );
HRESULT get_LastTransportStatus( long* plValue );
HRESULT get_LoadResult( long* phrError );
HRESULT get_ReadyState( LONG* plReadyState );

#endif /* _UPNP_ */
