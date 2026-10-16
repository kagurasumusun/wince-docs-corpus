/* Dsgetdc.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 43 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DSGETDC_
#define _DSGETDC_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DCLOCATOR_CRITICAL 0x00000100
#define DCLOCATOR_DNS 0x00004000
#define DCLOCATOR_DNS_MORE 0x00020000
#define DCLOCATOR_MAILBOX_TEXT 0x02000000
#define DCLOCATOR_MAILSLOT 0x00000010
#define DCLOCATOR_MISC 0x00000002
#define DCLOCATOR_SESSION_SETUP 0x00000200
#define DCLOCATOR_SITE 0x00000020
#define DCLOCATOR_SITE_MORE 0x08000000
#define DS_AVOID_SELF 0x00004000
#define DS_BACKGROUND_ONLY 0x00000100
#define DS_DIRECTORY_SERVICE_PREFERRED 0x00000020
#define DS_DIRECTORY_SERVICE_REQUIRED 0x00000010
#define DS_DNS_CONTROLLER_FLAG 0x20000000
#define DS_DNS_DOMAIN_FLAG 0x40000000
#define DS_DNS_FOREST_FLAG 0x80000000
#define DS_DOMAIN_DIRECT_INBOUND 0x0020
#define DS_DOMAIN_DIRECT_OUTBOUND 0x0002
#define DS_DOMAIN_IN_FOREST 0x0001
#define DS_DOMAIN_NATIVE_MODE 0x0010
#define DS_DOMAIN_PRIMARY 0x0008
#define DS_DOMAIN_TREE_ROOT 0x0004
#define DS_DS_FLAG 0x00000010
#define DS_FORCE_REDISCOVERY 0x00000001
#define DS_GC_FLAG 0x00000004
#define DS_GC_SERVER_REQUIRED 0x00000040
#define DS_GOOD_TIMESERV_PREFERRED 0x00002000
#define DS_INET_ADDRESS 0x0001
#define DS_IP_REQUIRED 0x00000200
#define DS_IS_DNS_NAME 0x00020000
#define DS_IS_FLAT_NAME 0x00010000
#define DS_KDC_FLAG 0x00000020
#define DS_KDC_REQUIRED 0x00000400
#define DS_NETBIOS_ADDRESS 0x0002
#define DS_ONLY_LDAP_NEEDED 0x00008000
#define DS_PDC_FLAG 0x00000001
#define DS_PDC_REQUIRED 0x00000080
#define DS_RETURN_DNS_NAME 0x40000000
#define DS_RETURN_FLAT_NAME 0x80000000
#define DS_TIMESERV_FLAG 0x00000040
#define DS_TIMESERV_REQUIRED 0x00000800
#define DS_WRITABLE_FLAG 0x00000100
#define DS_WRITABLE_REQUIRED 0x00001000

#endif /* _DSGETDC_ */
