/* Usbtypes.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 6 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _USBTYPES_
#define _USBTYPES_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* LPTRANSFER_NOTIFY_ROUTINE  [typedef; ce-only] */
typedef DWORD (WINAPI *LPTRANSFER_NOTIFY_ROUTINE)(
 LPVOID lpvNotifyParameter
);

/* USB_INTERFACE_DESCRIPTOR  [struct; ce-only] */
typedef struct {
 UCHAR bLength;
 UCHAR bDescriptorType;
 UCHAR bInterfaceNumber;
 UCHAR bAlternateSetting;
 UCHAR bNumEndpoints;
 UCHAR bInterfaceClass;
 UCHAR bInterfaceSubClass;
 UCHAR bInterfaceProtocol;
 UCHAR iInterface;
} USB_INTERFACE_DESCRIPTOR;
typedef USB_INTERFACE_DESCRIPTOR *PUSB_INTERFACE_DESCRIPTOR, *LPUSB_INTERFACE_DESCRIPTOR;

#endif /* _USBTYPES_ */
