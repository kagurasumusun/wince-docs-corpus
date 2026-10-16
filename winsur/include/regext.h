/* regext.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 16 declarations, 0 outlines, 0 base types, 0 extra macros, 4 extra decls
 */
#ifndef _REGEXT_
#define _REGEXT_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* REG_COMPARISONTYPE  [enum; ce-only] */
typedef enum tagREG_COMPARISONTYPE { 
 REG_CT_ANYCHANGE,
 REG_CT_EQUAL,
 REG_CT_NOT_EQUAL,
 REG_CT_GREATER,
 REG_CT_GREATER_OR_EQUAL,
 REG_CT_LESS,
 REG_CT_LESS_OR_EQUAL,
 REG_CT_CONTAINS,
 REG_CT_STARTS_WITH,
 REG_CT_ENDS_WITH
} REG_COMPARISONTYPE;
typedef REG_COMPARISONTYPE *PREG_COMPARISONTYPE, *LPREG_COMPARISONTYPE;

/* NOTIFICATIONCONDITION  [struct; ce-only] */
typedef struct tagNOTIFICATIONCONDITION {
 REG_COMPARISONTYPE ctComparisonType;
 DWORD dwMask;
 union TargetValue {
 LPCTSTR psz;
 DWORD dw; 
 };
} NOTIFICATIONCONDITION;
typedef NOTIFICATIONCONDITION *PNOTIFICATIONCONDITION, *LPNOTIFICATIONCONDITION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* RegistryDeleteValue  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT WINAPI RegistryDeleteValue( 
 HKEY hKey
 LPCTSTR pszSubKey,
 LPCTSTR pszValueName
);

/* RegistryGetDWORD  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT WINAPI RegistryGetDWORD( 
 HKEY hKey,
 LPCTSTR pszSubKey,
 LPCTSTR pszValueName,
 DWORD* pdwData
);

/* RegistryGetString  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT WINAPI RegistryGetString( 
 HKEY hKey,
 LPCTSTR pszSubKey,
 LPCTSTR pszValueName,
 LPTSTR pszData,
 UINT cchData 
);

/* RegistryNotifyApp  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT WINAPI RegistryNotifyApp( 
 HKEY hKey,
 LPCTSTR pszSubKey,
 LPCTSTR pszValueName,
 LPCTSTR pszName,
 LPCTSTR pszApp,
 LPCTSTR pszClass,
 LPCTSTR pszWindow,
 UINT msg,
 DWORD dwFlags,
 NOTIFICATIONCONDITION* pCondition
);

/* RegistrySetDWORD  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT WINAPI RegistrySetDWORD( 
 HKEY hKey,
 LPCTSTR pszSubKey,
 LPCTSTR pszValueName,
 DWORD dwData 
);

/* RegistrySetString  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT WINAPI RegistrySetString( 
 HKEY hKey,
 LPCTSTR pszSubKey,
 LPCTSTR pszValueName,
 LPCTSTR pszData 
);

/* RegistryStopNotification  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT WINAPI RegistryStopNotification(
 LPCTSTR pszName
);

/* RegistryTestExchangeDWORD  [function; ce-only; CE 6.0..699; aygshell.lib] */
HRESULT WINAPI RegistryTestExchangeDWORD( 
 HKEY hKey,
 LPCTSTR pszSubKey,
 LPCTSTR pszValueName,
 DWORD dwOldValue,
 DWORD dwNewValue 
);
#endif /* _WIN32_WCE */

#endif /* _REGEXT_ */
