/* Icmpapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 30 constants, 9 declarations, 0 outlines, 0 base types, 0 extra macros, 3 extra decls
 */
#ifndef _ICMPAPI_
#define _ICMPAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define IP_BAD_DESTINATION 11018
#define IP_BAD_OPTION 11007
#define IP_BAD_REQ 11011
#define IP_BAD_ROUTE 11012
#define IP_BUF_TOO_SMALL 11001
#define IP_DEST_HOST_UNREACHABLE 11003
#define IP_DEST_NET_UNREACHABLE 11002
#define IP_DEST_PORT_UNREACHABLE 11005
#define IP_DEST_PROT_UNREACHABLE 11004
#define IP_FLAG_DF 0x2
#define IP_FLAG_REVERSE 0x01
#define IP_GENERAL_FAILURE 11050
#define IP_HW_ERROR 11008
#define IP_NO_RESOURCES 11006
#define IP_OPT_EOL 0
#define IP_OPT_LSRR 0x83
#define IP_OPT_NOP 1
#define IP_OPT_RR 0x7
#define IP_OPT_SECURITY 0x82
#define IP_OPT_SID 0x88
#define IP_OPT_SSRR 0x89
#define IP_OPT_TS 0x44
#define IP_OPTION_TOO_BIG 11017
#define IP_PACKET_TOO_BIG 11009
#define IP_PARAM_PROBLEM 11015
#define IP_REQ_TIMED_OUT 11010
#define IP_SOURCE_QUENCH 11016
#define IP_SUCCESS 11000
#define IP_TTL_EXPIRED_REASSEM 11014
#define IP_TTL_EXPIRED_TRANSIT 11013

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ICMP_ECHO_REPLY  [struct; shared] */
struct icmp_echo_reply {
 IPAddr Address;
 unsigned long Status;
 unsigned long RoundTripTime;
 unsigned short DataSize; 
 unsigned short Reserved; 
 void FAR* Data;
 struct ip_option_information Options; 
} ICMP_ECHO_REPLY;

/* IP_OPTION_INFORMATION  [struct; shared] */
typedef struct IP_OPTION_INFORMATION {
 unsigned char Ttl;
 unsigned char Tos;
 unsigned char Flags;
 unsigned char OptionsSize;
 unsigned char FAR* OptionsData;
} IP_OPTION_INFORMATION;
typedef IP_OPTION_INFORMATION *PIP_OPTION_INFORMATION, *LPIP_OPTION_INFORMATION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 1.0..199, 2.11..2.12, 3.0..699 */

/* IcmpCloseHandle  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Icmplib.lib, Iphlpapi.dll, Iphlpapi.lib] */
BOOL WINAPI IcmpCloseHandle(
 HANDLE IcmpHandle 
);

/* IcmpCreateFile  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Icmplib.lib, Iphlpapi.dll, Iphlpapi.lib] */
HANDLE WINAPI IcmpCreateFile(VOID);

/* IcmpSendEcho  [function; shared; CE 1.0..199, 2.11..2.12, 3.0..699; Icmplib.lib, Iphlpapi.dll, Iphlpapi.lib] */
DWORD WINAPI IcmpSendEcho(
 HANDLE IcmpHandle, 
 IPAddr DestinationAddress,
 LPVOID RequestData, 
 WORD RequestSize, 
 PIP_OPTION_INFORMATION RequestOptions, 
 LPVOID ReplyBuffer,
 DWORD ReplySize, 
 DWORD Timeout 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* Icmp6CreateFile  [function; shared; CE 4.0..699; Icmplib.lib, Iphlpapi.dll, Iphlpapi.lib] */
HANDLE WINAPI Icmp6CreateFile(VOID);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* Icmp6ParseReplies  [function; shared; CE 5.0..699; Icmplib.lib, Iphlpapi.dll, Iphlpapi.lib] */
DWORD Icmp6ParseReplies(
 LPVOID ReplyBuffer,
 DWORD ReplySize
);

/* IcmpParseReplies  [function; shared; CE 5.0..699; Icmplib.lib, Iphlpapi.dll, Iphlpapi.lib] */
DWORD IcmpParseReplies(
 LPVOID ReplyBuffer,
 DWORD ReplySize
);
#endif /* _WIN32_WCE */

#endif /* _ICMPAPI_ */
