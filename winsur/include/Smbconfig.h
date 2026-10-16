/* Smbconfig.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 5 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SMBCONFIG_
#define _SMBCONFIG_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* Add_Share  [function; ce-only; CE 5.0..699; Smbconfig.lib] */
HRESULT Add_Share(
 const WCHAR* pName,
 DWORD dwType,
 const WCHAR* pPath,
 const WCHAR* pACL,
 const WCHAR* pROACL,
 const WCHAR* pDriver,
 const WCHAR* pComment
);

/* Change_ACL  [function; ce-only; CE 5.0..699; Smbconfig.lib] */
HRESULT Change_ACL(
 const WCHAR* pShareName,
 const WCHAR* pACL,
 const WCHAR* pROACL
);

/* Del_Share  [function; ce-only; CE 5.0..699; Smbconfig.lib] */
HRESULT Del_Share(
 const WCHAR* pName
);

/* List_Connected_Users  [function; ce-only; CE 5.0..699; Smbconfig.lib] */
HRESULT List_Connected_Users(
 WCHAR* pBuffer,
 UINT* puiLen
);

/* QueryAmountTransfered  [function; ce-only; CE 5.0..699; Smbconfig.lib] */
HRESULT QueryAmountTransfered(
 LARGE_INTEGER* pRead,
 LARGE_INTEGER* pWritten
);
#endif /* _WIN32_WCE */

#endif /* _SMBCONFIG_ */
