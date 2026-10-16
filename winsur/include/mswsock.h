/* mswsock.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 25 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MSWSOCK_
#define _MSWSOCK_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SO_CONNDATA 0x7000
#define SO_CONNDATALEN 0x7004
#define SO_CONNECT_TIME 0x700C
#define SO_CONNOPT 0x7001
#define SO_CONNOPTLEN 0x7005
#define SO_DISCDATA 0x7002
#define SO_DISCDATALEN 0x7006
#define SO_DISCOPT 0x7003
#define SO_DISCOPTLEN 0x7007
#define SO_MAXDG 0x7009
#define SO_MAXPATHDG 0x700A
#define SO_OPENTYPE 0x7008
#define SO_SYNCHRONOUS_ALERT 0x10
#define SO_SYNCHRONOUS_NONALERT 0x20
#define SO_UPDATE_ACCEPT_CONTEXT 0x700B
#define TCP_BSDURGENT 0x7000
#define TF_DISCONNECT 1
#define TF_REUSE_SOCKET 2
#define TF_USE_DEFAULT_WORKER 0
#define TF_USE_KERNEL_APC 32
#define TF_USE_SYSTEM_THREAD 16
#define TF_WRITE_BEHIND 4
#define TP_ELEMENT_EOP 4
#define TP_ELEMENT_FILE 1
#define TP_ELEMENT_MEMORY 2

#endif /* _MSWSOCK_ */
