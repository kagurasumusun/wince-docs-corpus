/* Ws2tcpip.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 6 declarations, 0 outlines, 0 base types, 0 extra macros, 4 extra decls
 */
#ifndef _WS2TCPIP_
#define _WS2TCPIP_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* getnameinfo  [struct, macro, function; shared; Ws2.lib; A/W GetNameInfoW (CE is W-side)] */
int getnameinfo(
 const struct sockaddr FAR* sa,
 socklen_t salen,
 char FAR* host,
 DWORD hostlen,
 char FAR* serv,
 DWORD servlen,
 int flags
);

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* addrinfo  [struct; shared; A/W ADDRINFOA,ADDRINFOW (CE is W-side)] */
struct addrinfo {
 int ai_flags;
 int ai_family;
 int ai_socktype;
 int ai_protocol;
 size_t ai_addrlen;
 char* ai_canonname;
 struct sockaddr* ai_addr;
 struct addrinfo* ai_next;
};

/* freeaddrinfo  [struct, function; shared; Ws2.lib; A/W FreeAddrInfoW (CE is W-side)] */
void freeaddrinfo(
 struct addrinfo FAR* ai
);

/* getaddrinfo  [struct, function; shared; Ws2.lib; A/W GetAddrInfoW (CE is W-side)] */
int getaddrinfo(
 const char FAR* nodename,
 const char FAR* servname,
 const struct addrinfo FAR* hints,
 struct addrinfo FAR* FAR* res
);

/* in6_addr  [struct; shared] */
struct in6_addr {
 union {
 u_char Byte[16];
 u_short Word[8];
 } u;
};

/* sockaddr_in6  [struct; ce-only] */
struct sockaddr_in6 {
 short sin6_family;
 u_short sin6_port;
 u_long sin6_flowinfo;
 struct in6_addr sin6_addr;
 u_long sin6_scope_id;
};

/* ai  [extra struct] */
void freeaddrinfo(struct addrinfo FAR* ai);

/* sin6_scope_id  [extra struct] */
struct sockaddr_in6 {short sin6_family;u_short sin6_port;u_longsin6_flowinfo;struct in6_addrsin6_addr;u_long sin6_scope_id;};

/* ai_next  [extra struct] */
struct addrinfo {
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  size_t ai_addrlen;
  char* ai_canonname;
  struct sockaddr* ai_addr;
  struct addrinfo* ai_next;
};

/* flags  [extra struct] */
int getnameinfo( const struct sockaddr FAR* sa, socklen_t salen, char FAR* host, DWORD hostlen, char FAR* serv, DWORD servlen, int flags );

#endif /* _WS2TCPIP_ */
