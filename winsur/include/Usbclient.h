/* Usbclient.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 19 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _USBCLIENT_
#define _USBCLIENT_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* REG_VALUE_DESCR  [struct; ce-only] */
typedef struct _REG_VALUE_DESCR {
 LPWSTR Name;
 DWORD Type;
 DWORD Size;
 PBYTE Data;
} REG_VALUE_DESCR, *PREG_VALUE_DESCR;

/* REMOVE_LOCK  [struct; ce-only] */
typedef struct _REMOVE_LOCK {
 BOOL Removed;
 LONG IoCount;
 HANDLE RemoveEvent;
} REMOVE_LOCK, *PREMOVE_LOCK;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* AcquireRemoveLock  [function; ce-only; CE 5.0..699] */
DWORD AcquireRemoveLock(
 IN PREMOVE_LOCK Lock,
 IN OPTIONAL PVOID Tag
);

/* DefaultTransferComplete  [function; ce-only; CE 5.0..699] */
DWORD DefaultTransferComplete(
 PVOID Context
);

/* GetSetKeyValues  [function; ce-only; CE 5.0..699] */
BOOL GetSetKeyValues(
 LPCTSTR KeyName,
 PREG_VALUE_DESCR ValDesc,
 BOOL bSet,
 BOOL bOverwrite
);

/* InitializeRemoveLock  [function; ce-only; CE 5.0..699] */
BOOL InitializeRemoveLock(
 IN PREMOVE_LOCK Lock
);

/* ReleaseRemoveLock  [function; ce-only; CE 5.0..699] */
VOID ReleaseRemoveLock(
 IN PREMOVE_LOCK Lock,
 IN OPTIONAL PVOID Tag
);

/* ReleaseRemoveLockAndWait  [function; ce-only; CE 5.0..699] */
VOID ReleaseRemoveLockAndWait(
 IN PREMOVE_LOCK Lock,
 IN OPTIONAL PVOID Tag
);
#endif /* _WIN32_WCE */

#endif /* _USBCLIENT_ */
