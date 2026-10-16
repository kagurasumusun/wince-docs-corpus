/* Hiddi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 11 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _HIDDI_
#define _HIDDI_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* HID_DRIVER_SETTINGS  [struct; ce-only] */
typedef struct _HID_DRIVER_SETTINGS {
 DWORD dwVendorId;
 DWORD dwProductId;
 DWORD dwReleaseNumber;
 DWORD dwInterfaceNumber;
 DWORD dwCollection;
 DWORD dwUsagePage;
 DWORD dwUsage;
} HID_DRIVER_SETTINGS, *PHID_DRIVER_SETTINGS;

/* HID_STRING_TYPE  [enum; ce-only] */
typedef enum _HID_STRING_TYPE {
 HID_STRING_INDEXED = 0,
 HID_STRING_ID_IMANUFACTURER,
 HID_STRING_ID_IPRODUCT,
 HID_STRING_ID_ISERIALNUMBER,
 HID_STRING_MAX
} HID_STRING_TYPE;
typedef HID_STRING_TYPE *PHID_STRING_TYPE, *LPHID_STRING_TYPE;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* HIDDeviceNotifications  [function; ce-only; CE 4.0..699; Conshid_lib.lib, Kbdhid_lib.lib, Mouhid_lib.lib] */
BOOL HIDDeviceNotifications(
 DWORD dwMsg, 
 WPARAM wParam,
 PVOID pvNotifyParameter
);
#endif /* _WIN32_WCE */

#endif /* _HIDDI_ */
