/* mprapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 44 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MPRAPI_
#define _MPRAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ATADDRESSLEN 32
#define IPADDRESSLEN 15
#define IPXADDRESSLEN 22
#define MAX_DEVICE_NAME 128
#define MAX_DEVICETYPE_NAME 16
#define MAX_MEDIA_NAME 16
#define MAX_PHONE_NUMBER_LEN 128
#define MAX_PORT_NAME 16
#define MAX_TRANSPORT_NAME_LEN 40
#define MPR_ENABLE_RAS_ON_DEVICE 0x00000001
#define MPR_ENABLE_ROUTING_ON_DEVICE 0x00000002
#define MPR_INTERFACE_ADMIN_DISABLED 0x00000002
#define MPR_INTERFACE_CONNECTION_FAILURE 0x00000004
#define MPR_INTERFACE_DIALOUT_HOURS_RESTRICTION 0x00000010
#define MPR_INTERFACE_NO_DEVICE 0x00000040
#define MPR_INTERFACE_NO_MEDIA_SENSE 0x00000020
#define MPR_INTERFACE_OUT_OF_RESOURCES 0x00000001
#define MPR_INTERFACE_SERVICE_PAUSED 0x00000008
#define MPRDT_SW56 RASDT_SW56
#define MPRDT_X25 RASDT_X25
#define PID_ATALK 0x00000029
#define PID_IP 0x00000021
#define PID_IPX 0x0000002B
#define PID_NBF 0x0000003F
#define PPP_CCP_COMPRESSION 0x00000001
#define PPP_CCP_ENCRYPTION128BIT 0x00000040
#define PPP_CCP_ENCRYPTION40BIT 0x00000020
#define PPP_CCP_ENCRYPTION40BITOLD 0x00000010
#define PPP_CCP_ENCRYPTION56BIT 0x00000080
#define PPP_CCP_HISTORYLESS 0x01000000
#define PPP_LCP_CHAP 0x0000C223
#define PPP_LCP_CHAP_MD5 0x00000005
#define PPP_LCP_CHAP_MS 0x00000080
#define PPP_LCP_CHAP_MSV2 0x00000081
#define PPP_LCP_EAP 0x0000C227
#define PPP_LCP_MULTILINK_FRAMING 0x00000001
#define PPP_LCP_PAP 0x0000C023
#define PPP_LCP_SPAP 0x0000C027
#define RAS_FLAGS_MESSENGER_PRESENT 0x00000002
#define RAS_FLAGS_PPP_CONNECTION 0x00000001
#define RAS_FLAGS_QUARANTINE_PRESENT 0x00000008
#define RAS_FLAGS_RAS_CONNECTION 0x00000004
#define RASCCPCA_MPPC 0x00000006
#define RASCCPCA_STAC 0x00000005

#endif /* _MPRAPI_ */
