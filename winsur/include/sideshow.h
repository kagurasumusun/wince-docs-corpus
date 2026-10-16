/* sideshow.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 21 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SIDESHOW_
#define _SIDESHOW_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* SideShowMgr_FindFirstItem  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
HANDLE SideShowMgr_FindFirstItem(
 UINT uiGadget,
 UINT* lpFirstItemSize
);

/* SideShowMgr_FindNextItem  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_FindNextItem(
 HANDLE hSearch,
 UINT* lpItemId,
 BYTE* lpBuffer,
 UINT* lpuiItemSize,
 UINT* lpNextItemSize
);

/* SideShowMgr_GetCurrentCacheSize  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
DWORD SideShowMgr_GetCurrentCacheSize();

/* SideShowMgr_GetGadgetCount  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
int SideShowMgr_GetGadgetCount();

/* SideShowMgr_GetGadgetInfoSizes  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_GetGadgetInfoSizes(
 UINT* lpuiNameLen,
 UINT* lpuiIcon48,
 UINT* lpuiIcon32,
 UINT* lpuiIcon16
);

/* SideShowMgr_GetGadgetOrder  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
int SideShowMgr_GetGadgetOrder(
 UINT* lpuiGadgetIds,
 int iGadgetIdBufferSize
);

/* SideShowMgr_GetItemData  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_GetItemData(
 UINT uiGadgetId,
 DWORD dwItemId,
 BYTE* lpData,
 DWORD dwDataSize
);

/* SideShowMgr_GetItemDataSize  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
DWORD SideShowMgr_GetItemDataSize(
 UINT uiGadgetId,
 DWORD dwItemId
);

/* SideShowMgr_GetItemDataSizeTimeout  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
DWORD SideShowMgr_GetItemDataSizeTimeout(
 UINT uiGadgetId,
 DWORD dwItemId,
 DWORD dwTimeout
);

/* SideShowMgr_GetNotificationInfo  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_GetNotificationInfo(
 UINT* lpuiGadgetId,
 UINT* lpuiNotificationId,
 FILETIME* lpftExpirationTime,
 WCHAR* wcTitle,
 UINT uiTitle,
 WCHAR* wcText,
 UINT uiText,
 BYTE* lpbIconData,
 UINT uiIconData
);

/* SideShowMgr_GetNotificationInfoSizes  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_GetNotificationInfoSizes(
 UINT* lpuiTitle,
 UINT* lpuiText,
 UINT* lpuiIcon
);

/* SideShowMgr_GetSizeOfAvailableUserNames  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
DWORD SideShowMgr_GetSizeOfAvailableUserNames();

/* SideShowMgr_IsServiceRunning  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_IsServiceRunning();

/* SideShowMgr_SendApplicationEvent  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_SendApplicationEvent(
 UINT uiGadgetId,
 UINT uiEventType,
 BYTE* lpEventData,
 DWORD dwEventDataSize
);

/* SideShowMgr_SetMaximumCacheSize  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_SetMaximumCacheSize(
 DWORD size
);

/* SideShowMgr_Stop  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_Stop();

/* SideShowMgr_UserChangeRequest  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_UserChangeRequest( 
 WCHAR* wcUserName
);

/* SideShowMgr_UserChangeRequestCch  [function; ce-only; CE 5.0..599; sideshowapi.lib] */
BOOL SideShowMgr_UserChangeRequestCch(
 WCHAR* wcUserName,
 DWORD dwAllocatedCharacters
);
#endif /* _WIN32_WCE */

#endif /* _SIDESHOW_ */
