/* Storemgr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 40 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _STOREMGR_
#define _STOREMGR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* FindClosePartition  [function; ce-only; harvest-kb; harvest-kb] */
BOOL WINAPI FindClosePartition( 
 HANDLE hSearch 
);

/* FindCloseStore  [function; ce-only; harvest-kb; harvest-kb] */
BOOL WINAPI FindCloseStore( 
 HANDLE hSearch 
);

/* FormatStore  [function; ce-only; unified-kb; unified-kb] */
BOOL WINAPI FormatStore( 
 HANDLE hStore 
);

/* OpenStore  [function; ce-only; unified-kb; unified-kb] */
HANDLE OpenStore( 
 LPCSTR szDeviceName 
);

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* DeletePartition  [function; ce-only; CE 5.0..699; Storeapi.lib] */
BOOL WINAPI DeletePartition(
 HANDLE hStore,
 LPCTSTR szPartitionName
);

/* DismountPartition  [function; ce-only; CE 5.0..699; Storeapi.lib] */
BOOL WINAPI DismountPartition(
 HANDLE hPartition
);

/* DismountStore  [function; ce-only; CE 5.0..699; Storeapi.lib] */
BOOL WINAPI DismountStore(
 HANDLE hStore
);

/* FormatPartition  [function; ce-only; CE 5.0..699; Storeapi.lib] */
BOOL WINAPI FormatPartition(
 HANDLE hPartition
);

/* FormatPartitionEx  [function; ce-only; CE 5.0..699; Storeapi.lib] */
BOOL WINAPI FormatPartitionEx(
 HANDLE hPartition,
 BYTE bPartType,
 BOOL bAuto
);

/* MountPartition  [function; ce-only; CE 5.0..699; Storeapi.lib] */
BOOL WINAPI MountPartition(
 HANDLE hPartition
);

/* OpenPartition  [function; ce-only; CE 5.0..699; Storeapi.lib] */
HANDLE WINAPI OpenPartition(
 HANDLE hStore,
 LPCTSTR szPartitionName
);

/* RenamePartition  [function; ce-only; CE 5.0..699; Storeapi.lib] */
BOOL WINAPI RenamePartition(
 HANDLE hPartition,
 LPCTSTR szNewName
);

/* SetPartitionAttributes  [function; ce-only; CE 5.0..699; Storeapi.lib] */
BOOL WINAPI SetPartitionAttributes(
 HANDLE hPartition,
 DWORD dwAttrs
);
#endif /* _WIN32_WCE */

#endif /* _STOREMGR_ */
