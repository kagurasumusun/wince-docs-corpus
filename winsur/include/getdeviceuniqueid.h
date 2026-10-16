/* getdeviceuniqueid.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _GETDEVICEUNIQUEID_
#define _GETDEVICEUNIQUEID_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

/* GetDeviceUniqueID  [function; ce-only; unified-kb; unified-kb] */
HRESULT GetDeviceUniqueID(
 LPBYTE pbApplicationData,
 DWORD cbApplictionData,
 DWORD dwDeviceIDVersion,
 LPBYTE pbDeviceIDOutput,
 DWORD* pcbDeviceIDOutput
);

#endif /* _GETDEVICEUNIQUEID_ */
