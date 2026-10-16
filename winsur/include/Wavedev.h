/* Wavedev.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _WAVEDEV_
#define _WAVEDEV_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ACMDRV_MESSAGE_PARAMS  [struct; ce-only] */
typedef struct { 
 DWORD dwDeviceID;
 HANDLE hDriver;
 UINT uMsg;
 LPARAM lParam1;
 LPARAM lParam2;
} ACMDRV_MESSAGE_PARAMS;
typedef ACMDRV_MESSAGE_PARAMS *PACMDRV_MESSAGE_PARAMS, *LPACMDRV_MESSAGE_PARAMS;

/* MMDRV_MESSAGE_PARAMS  [struct; ce-only] */
typedef struct {
 UINT uDeviceId;
 UINT uMsg;
 DWORD dwUser;
 DWORD dwParam1;
 DWORD dwParam2;
} MMDRV_MESSAGE_PARAMS;
typedef MMDRV_MESSAGE_PARAMS *PMMDRV_MESSAGE_PARAMS, *LPMMDRV_MESSAGE_PARAMS;

/* CMDRV_MESSAGE_PARAMS  [extra struct] */
typedef struct {
  DWORD dwDriverID;
  HANDLE hDriver;
  UINT uMsg;
  LPARAM lParam1;
  LPARAM lParam2;
} CMDRV_MESSAGE_PARAMS;

#endif /* _WAVEDEV_ */
