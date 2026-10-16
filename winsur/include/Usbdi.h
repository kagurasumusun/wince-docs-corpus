/* Usbdi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 13 constants, 55 declarations, 0 outlines, 0 base types, 0 extra macros, 6 extra decls
 */
#ifndef _USBDI_
#define _USBDI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define USB_BIT_STUFFING_ERROR 0x00000002
#define USB_BUFFER_OVERRUN_ERROR 0x0000000C
#define USB_BUFFER_UNDERRUN_ERROR 0x0000000D
#define USB_CRC_ERROR 0x00000001
#define USB_DATA_OVERRUN_ERROR 0x00000008
#define USB_DATA_TOGGLE_MISMATCH_ERROR 0x00000003
#define USB_DATA_UNDERRUN_ERROR 0x00000009
#define USB_DEVICE_NOT_RESPONDING_ERROR 0x00000005
#define USB_NO_ERROR 0x00000000
#define USB_NOT_COMPLETE_ERROR 0x00000103
#define USB_PID_CHECK_FAILURE_ERROR 0x00000006
#define USB_STALL_ERROR 0x00000004
#define USB_UNEXPECTED_PID_ERROR 0x00000007

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* LPDEVICE_NOTIFY_ROUTINE  [typedef; ce-only] */
typedef BOOL (WINAPI *LPDEVICE_NOTIFY_ROUTINE)(
 LPVOID lpvNotifyParameter,
 DWORD dwCode,
 LPDWORD* dwInfo1,
 LPDWORD* dwInfo2,
 LPDWORD* dwInfo3,
 LPDWORD* dwInfo4
);

/* USB_DRIVER_SETTINGS  [struct; ce-only] */
typedef struct {
 DWORD dwCount;
 DWORD dwVendorId;
 DWORD dwProductId;
 DWORD dwReleaseNumber;
 DWORD dwDeviceClass;
 DWORD dwDeviceSubClass;
 DWORD dwDeviceProtocol;
 DWORD dwInterfaceClass;
 DWORD dwInterfaceSubClass;
 DWORD dwInterfaceProtocol;
} USB_DRIVER_SETTINGS;
typedef USB_DRIVER_SETTINGS *PUSB_DRIVER_SETTINGS, *LPUSB_DRIVER_SETTINGS;

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* LPGET_USBD_VERSION  [callback; ce-only; CE 5.0..699] */
typedef VOID (* LPGET_USBD_VERSION)(
 LPDWORD lpdwMajorVersion,
 LPDWORD lpdwMinorVersion
);

/* LPOPEN_CLIENT_REGISTRY_KEY  [callback; ce-only; CE 5.0..699] */
typedef HKEY (* LPOPEN_CLIENT_REGISTRY_KEY)(
 LPCWSTR szUniqueDriverId
);

/* LPREGISTER_CLIENT_DRIVER_ID  [callback; ce-only; CE 5.0..699] */
typedef BOOL (* LPREGISTER_CLIENT_DRIVER_ID)(
 LPCWSTR szUniqueDriverId
);

/* LPUN_REGISTER_CLIENT_DRIVER_ID  [callback; ce-only; CE 5.0..699] */
typedef BOOL (* LPUN_REGISTER_CLIENT_DRIVER_ID)(
 LPCWSTR szUniqueDriverId
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* USBInstallDriver  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL USBInstallDriver(
 LPCWSTR szDriverLibFile 
);

/* USBUnInstallDriver  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699] */
BOOL USBUnInstallDriver(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x500)) /* CE 2.11..2.12, 3.0..499 */

/* GetUSBDVersion  [function; ce-only; CE 2.11..2.12, 3.0..499; Usbd.lib] */
VOID GetUSBDVersion(
 LPDWORD lpdwMajorVersion,
 LPDWORD lpdwMinorVersion 
);

/* OpenClientRegistryKey  [function; ce-only; CE 2.11..2.12, 3.0..499] */
HKEY OpenClientRegistryKey(
 LPCWSTR szUniqueDriverId 
);

/* RegisterClientDriverID  [function; ce-only; CE 2.11..2.12, 3.0..499] */
BOOL RegisterClientDriverID(
 LPCWSTR szUniqueDriverId 
);
#endif /* _WIN32_WCE */

#endif /* _USBDI_ */
