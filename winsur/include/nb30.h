/* nb30.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 85 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NB30_
#define _NB30_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ALL_TRANSPORTS "M\0\0\0"
#define ASYNCH 0x80
#define CALL_PENDING 0x02
#define DEREGISTERED 0x05
#define DUPLICATE 0x06
#define DUPLICATE_DEREG 0x07
#define GROUP_NAME 0x80
#define HANGUP_COMPLETE 0x05
#define HANGUP_PENDING 0x04
#define LISTEN_OUTSTANDING 0x01
#define MAX_LANA 254
#define MS_NBF "MNBF"
#define NAME_FLAGS_MASK 0x87
#define NCB_POST void
#define NCBACTION 0x77
#define NCBADDGRNAME 0x36
#define NCBADDNAME 0x30
#define NCBASTAT 0x33
#define NCBCALL 0x10
#define NCBCANCEL 0x35
#define NCBCHAINSEND 0x17
#define NCBCHAINSENDNA 0x72
#define NCBDELNAME 0x31
#define NCBDGRECV 0x21
#define NCBDGRECVBC 0x23
#define NCBDGSEND 0x20
#define NCBDGSENDBC 0x22
#define NCBENUM 0x37
#define NCBFINDNAME 0x78
#define NCBHANGUP 0x12
#define NCBLANSTALERT 0x73
#define NCBLISTEN 0x11
#define NCBNAMSZ 16
#define NCBRECV 0x15
#define NCBRECVANY 0x16
#define NCBRESET 0x32
#define NCBSEND 0x14
#define NCBSENDNA 0x71
#define NCBSSTAT 0x34
#define NCBTRACE 0x79
#define NCBUNLINK 0x70
#define NRC_ACTSES 0x0f
#define NRC_BADDR 0x07
#define NRC_BRIDGE 0x23
#define NRC_BUFLEN 0x01
#define NRC_CANCEL 0x26
#define NRC_CANOCCR 0x24
#define NRC_CMDCAN 0x0b
#define NRC_CMDTMO 0x05
#define NRC_DUPENV 0x30
#define NRC_DUPNAME 0x0d
#define NRC_ENVNOTDEF 0x34
#define NRC_GOODRET 0x00
#define NRC_IFBUSY 0x21
#define NRC_ILLCMD 0x03
#define NRC_ILLNN 0x13
#define NRC_INCOMP 0x06
#define NRC_INUSE 0x16
#define NRC_INVADDRESS 0x39
#define NRC_INVDDID 0x3B
#define NRC_LOCKFAIL 0x3C
#define NRC_LOCTFUL 0x11
#define NRC_MAXAPPS 0x36
#define NRC_NAMCONF 0x19
#define NRC_NAMERR 0x17
#define NRC_NAMTFUL 0x0e
#define NRC_NOCALL 0x14
#define NRC_NORES 0x09
#define NRC_NORESOURCES 0x38
#define NRC_NOSAPS 0x37
#define NRC_NOWILD 0x15
#define NRC_OPENERR 0x3f
#define NRC_OSRESNOTAV 0x35
#define NRC_PENDING 0xff
#define NRC_REMTFUL 0x12
#define NRC_SABORT 0x18
#define NRC_SCLOSED 0x0a
#define NRC_SNUMOUT 0x08
#define NRC_SYSTEM 0x40
#define NRC_TOOMANY 0x22
#define REGISTERED 0x04
#define REGISTERING 0x00
#define SESSION_ABORTED 0x06
#define SESSION_ESTABLISHED 0x03
#define UNIQUE_NAME 0x00

#endif /* _NB30_ */
