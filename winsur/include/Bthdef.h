/* Bthdef.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 40 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _BTHDEF_
#define _BTHDEF_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define BTH_CONTROL_DEVICEONLY 0x00001000
#define BTH_CONTROL_ROUTE_ALL 0x00000001
#define BTH_CONTROL_ROUTE_BY_ADDR 0x00000010
#define BTH_CONTROL_ROUTE_BY_COD 0x00000020
#define BTH_CONTROL_ROUTE_BY_LINKTYPE 0x00000040
#define BTH_CONTROL_ROUTE_HARDWARE 0x00000100
#define BTH_CONTROL_ROUTE_SECURITY 0x00000080
#define BTH_HCI_IOCTL_GET_BASEBAND_CONNECTIONS 0x00000013
#define BTH_HCI_IOCTL_GET_BASEBAND_HANDLES 0x00000010
#define BTH_HCI_IOCTL_GET_BD_FOR_HANDLE 0x00000001
#define BTH_HCI_IOCTL_GET_COMMANDSIZE 0x0000000b
#define BTH_HCI_IOCTL_GET_ERRORS 0x00000009
#define BTH_HCI_IOCTL_GET_FLOW 0x0000000a
#define BTH_HCI_IOCTL_GET_HANDLE_FOR_BD 0x00000002
#define BTH_HCI_IOCTL_GET_HANDLE_MODE 0x00000011
#define BTH_HCI_IOCTL_GET_HARDWARE_STATUS 0x00000014
#define BTH_HCI_IOCTL_GET_INQUIRY 0x00000006
#define BTH_HCI_IOCTL_GET_LAST_INQUIRY_DATA 0x0000000f
#define BTH_HCI_IOCTL_GET_LOOPBACK 0x00000008
#define BTH_HCI_IOCTL_GET_NUM_ONDEVICE 0x00000004
#define BTH_HCI_IOCTL_GET_NUM_PENDING 0x00000005
#define BTH_HCI_IOCTL_GET_NUM_UNSENT 0x00000003
#define BTH_HCI_IOCTL_GET_PERIODIC_INQUIRY 0x00000007
#define BTH_HCI_IOCTL_GET_REMOTE_COD 0x00000015
#define BTH_HCI_IOCTL_GET_SCO_PARAMETERS 0x00000012
#define BTH_HCI_IOCTL_GET_UNDER_TEST 0x0000000e
#define BTH_HCI_IOCTL_HANDLE_AUTHENTICATED 0x0000000c
#define BTH_HCI_IOCTL_HANDLE_ENCRYPTED 0x0000000d
#define BTH_MARKER_ADDRESS 2
#define BTH_MARKER_CONNECTION 1
#define BTH_MARKER_NONE 0
#define BTH_STACK_DISCONNECT 4
#define BTH_STACK_DOWN 2
#define BTH_STACK_FLOW_OFF 6
#define BTH_STACK_FLOW_ON 5
#define BTH_STACK_HOST_BUFFER 7
#define BTH_STACK_IOCTL_GET_CONNECTED 0x80000001
#define BTH_STACK_NONE 0
#define BTH_STACK_RESET 1
#define BTH_STACK_UP 3

#endif /* _BTHDEF_ */
