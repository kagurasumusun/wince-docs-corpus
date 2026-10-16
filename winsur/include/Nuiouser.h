/* Nuiouser.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 34 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NUIOUSER_
#define _NUIOUSER_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define MEDIA_STATE_CONNECTED 0
#define MEDIA_STATE_DISCONNECTED 0
#define MEDIA_STATE_UNKNOWN -1
#define NDISUIO_NOTIFICATION_ADAPTER_ARRIVAL 0x00000040
#define NDISUIO_NOTIFICATION_ADAPTER_REMOVAL 0x00000080
#define NDISUIO_NOTIFICATION_BIND 0x00000010
#define NDISUIO_NOTIFICATION_DEVICE_POWER_DOWN 0x00000400
#define NDISUIO_NOTIFICATION_DEVICE_POWER_UP 0x00000200
#define NDISUIO_NOTIFICATION_MEDIA_CONNECT 0x00000004
#define NDISUIO_NOTIFICATION_MEDIA_DISCONNECT 0x00000008
#define NDISUIO_NOTIFICATION_RESET_END 0x00000002
#define NDISUIO_NOTIFICATION_RESET_START 0x00000001
#define NDISUIO_NOTIFICATION_UNBIND 0x00000020
#define NUIO_8021P_TAG_TYPE 0x0081
#define NUIO_ETH_TYPE 0x8001
#define NUIOO_BIND_ACTIVE 0x00000004
#define NUIOO_BIND_CLOSING 0x00000008
#define NUIOO_BIND_FAILED 0x00000002
#define NUIOO_BIND_FLAGS 0x0000000F
#define NUIOO_BIND_IDLE 0x00000000
#define NUIOO_BIND_OPENING 0x00000001
#define NUIOO_MEDIA_CONNECTED 0x00000000
#define NUIOO_MEDIA_DISCONNECTED 0x00000200
#define NUIOO_MEDIA_FLAGS 0x00000200
#define NUIOO_NOT_RESETTING 0x00000000
#define NUIOO_OPEN_ACTIVE 0x00000010
#define NUIOO_OPEN_FLAGS 0x000000F0
#define NUIOO_OPEN_IDLE 0x00000000
#define NUIOO_READ_FLAGS 0x00100000
#define NUIOO_READ_SERVICING 0x00100000
#define NUIOO_RESET_FLAGS 0x00000100
#define NUIOO_RESET_IN_PROGRESS 0x00000100
#define NUIOO_UNBIND_FLAGS 0x10000000
#define NUIOO_UNBIND_RECEIVED 0x10000000

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* NDISUIO_DEVICE_NOTIFICATION  [struct; ce-only] */
typedef struct {
 DWORD dwNotificationType;
 TCHAR ptcDeviceName[MAX_PATH];
 UINT uiOffsetToStatusBuffer;
 UINT uiStatusBufferSize;
} NDISUIO_DEVICE_NOTIFICATION, *PNDISUIO_DEVICE_NOTIFICATION;

/* NDISUIO_QUERY_BINDING  [struct; ce-only] */
typedef struct _NDISUIO_QUERY_BINDING {
 ULONG BindingIndex;
 ULONG DeviceNameOffset;
 ULONG DeviceNameLength;
 ULONG DeviceDescrOffset;
 ULONG DeviceDescrLength;
} NDISUIO_QUERY_BINDING, *PNDISUIO_QUERY_BINDING;

/* NDISUIO_REQUEST_NOTIFICATION  [struct; ce-only] */
typedef struct{
 HANDLE hMsgQueue;
 DWORD dwNotificationTypes;
}NDISUIO_REQUEST_NOTIFICATION, *PNDISUIO_REQUEST_NOTIFICATION;

#endif /* _NUIOUSER_ */
