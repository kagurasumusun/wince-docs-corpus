/* connmgr_status.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CONNMGR_STATUS_
#define _CONNMGR_STATUS_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* ConnMgrRegisterForStatusChangeNotification  [function; ce-only; CE 6.0..699; cellcore.lib] */
HRESULT WINAPI ConnMgrRegisterForStatusChangeNotification(
 BOOL fEnable,
 HWND hWnd
);
#endif /* _WIN32_WCE */

#endif /* _CONNMGR_STATUS_ */
