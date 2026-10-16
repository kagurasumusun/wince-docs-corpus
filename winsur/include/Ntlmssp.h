/* Ntlmssp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 10 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NTLMSSP_
#define _NTLMSSP_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 3.0..399, 5.0..699 */

/* NTLMDeleteUser  [function; ce-only; CE 3.0..399, 5.0..699; Ntlmssp.lib] */
BOOL NTLMDeleteUser(
 LPTSTR pszUser 
);

/* NTLMEnumUser  [function; ce-only; CE 3.0..399, 5.0..699; Ntlmssp.lib] */
BOOL NTLMEnumUser(
 DWORD index,
 LPTSTR pszUser,
 LPDWORD pcchUser 
);

/* NTLMSetUserInfo  [function; ce-only; CE 3.0..399, 5.0..699; Ntlmssp.lib] */
BOOL NTLMSetUserInfo(
 LPTSTR pszUser,
 LPTSTR pszPassword
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* NTLMAddGroup  [function; ce-only; CE 5.0..699; Ntlmssp.lib] */
BOOL NTLMAddGroup(
 WCHAR* groupName
);

/* NTLMAddUserToGroup  [function; ce-only; CE 5.0..699; Ntlmssp.lib] */
BOOL NTLMAddUserToGroup(
 WCHAR* groupName,
 WCHAR* userName
);

/* NTLMEnumGroups  [function; ce-only; CE 5.0..699; Ntlmssp.lib] */
BOOL NTLMEnumGroups(
 DWORD index,
 WCHAR* groupName,
 DWORD* dwSizeInChars
);

/* NTLMGetGroupList  [function; ce-only; CE 5.0..699; Ntlmssp.lib] */
BOOL NTLMGetGroupList(
 WCHAR* userName,
 WCHAR* groupList,
 DWORD* pdwccLen
);

/* NTLMGetUserList  [function; ce-only; CE 5.0..699; Ntlmssp.lib] */
BOOL NTLMGetUserList(
 WCHAR* groupName,
 WCHAR* userList,
 DWORD* pdwccLen
);

/* NTLMRemoveGroup  [function; ce-only; CE 5.0..699; Ntlmssp.lib] */
BOOL NTLMRemoveGroup(
 WCHAR* groupName
);

/* NTLMRemoveUserFromGroup  [function; ce-only; CE 5.0..699; Ntlmssp.lib] */
BOOL NTLMRemoveUserFromGroup(
 WCHAR* groupName,
 WCHAR* userName
);
#endif /* _WIN32_WCE */

#endif /* _NTLMSSP_ */
