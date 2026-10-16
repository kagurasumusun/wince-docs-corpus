/* rassapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 35 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RASSAPI_
#define _RASSAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define GATEWAY_ACTIVE 0x0008
#define MEDIA_ISDN 4
#define MEDIA_RAS10_SERIAL 2
#define MEDIA_SERIAL 1
#define MEDIA_UNKNOWN 0
#define MEDIA_X25 3
#define MESSENGER_PRESENT 0x0002
#define PORT_MULTILINKED 0x0020
#define PPP_CLIENT 0x0004
#define RAS_ATADDRESSLEN 32
#define RAS_IPADDRESSLEN 15
#define RAS_IPXADDRESSLEN 22
#define RAS_MODEM_HARDWARE_FAILURE 3
#define RAS_MODEM_INCORRECT_RESPONSE 4
#define RAS_MODEM_NOT_RESPONDING 2
#define RAS_MODEM_OPERATIONAL 1
#define RAS_MODEM_UNKNOWN 5
#define RAS_PORT_AUTHENTICATED 6
#define RAS_PORT_AUTHENTICATING 5
#define RAS_PORT_CALLING_BACK 3
#define RAS_PORT_DISCONNECTED 2
#define RAS_PORT_INITIALIZING 7
#define RAS_PORT_LISTENING 4
#define RAS_PORT_NON_OPERATIONAL 1
#define RASADMIN_35 35
#define RASADMIN_CURRENT 40
#define RASDOWNLEVEL 10
#define RASSAPI_MAX_DEVICE_NAME 128
#define RASSAPI_MAX_DEVICETYPE_NAME 16
#define RASSAPI_MAX_MEDIA_NAME 16
#define RASSAPI_MAX_PARAM_KEY_SIZE 32
#define RASSAPI_MAX_PHONENUMBER_SIZE 128
#define RASSAPI_MAX_PORT_NAME 16
#define REMOTE_LISTEN 0x0010
#define USER_AUTHENTICATED 0x0001

#endif /* _RASSAPI_ */
