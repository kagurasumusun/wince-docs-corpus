/* Upnphost.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 5 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _UPNPHOST_
#define _UPNPHOST_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* IUPnPDeviceControl  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPEventSink  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPEventSource  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPRegistrar  [interface; shared; CE 5.0..599; Uuid.lib] */

/* IUPnPReregistrar  [interface; shared; CE 5.0..599; Uuid.lib] */
#endif /* _WIN32_WCE */

#endif /* _UPNPHOST_ */
