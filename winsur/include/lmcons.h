/* lmcons.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 59 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMCONS_
#define _LMCONS_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ALERTSZ 128
#define API_RET_TYPE NET_API_STATUS
#define CLTYPE_LEN 12
#define CNLEN 15
#define CRYPT_KEY_LEN 7
#define CRYPT_TXT_LEN 8
#define DEVLEN 80
#define DNLEN 15
#define ENCRYPTED_PWLEN 16
#define EVLEN 16
#define GNLEN UNLEN
#define HELP_MSG_FILENAME TEXT("NETH")
#define LM20_CNLEN 15
#define LM20_DEVLEN 8
#define LM20_DNLEN 15
#define LM20_GNLEN LM20_UNLEN
#define LM20_MAXCOMMENTSZ 48
#define LM20_NNLEN 12
#define LM20_PATHLEN 256
#define LM20_PWLEN 14
#define LM20_QNLEN LM20_NNLEN
#define LM20_RMLEN (LM20_UNCLEN+1+LM20_NNLEN)
#define LM20_SNLEN 15
#define LM20_STXTLEN 63
#define LM20_UNCLEN (LM20_CNLEN+2)
#define LM20_UNLEN 20
#define LMCSTR LPCWSTR
#define LMSTR LPWSTR
#define MAX_LANMAN_MESSAGE_ID 5799
#define MAX_PREFERRED_LENGTH ((DWORD)-1)
#define MAXCOMMENTSZ 256
#define MAXDEVENTRIES (sizeof(int)*8)
#define MESSAGE_FILENAME TEXT("NETMSG")
#define MIN_LANMAN_MESSAGE_ID NERR_BASE
#define NET_API_FUNCTION __stdcall
#define NET_API_STATUS DWORD
#define NETBIOS_NAME_LEN 16
#define NNLEN 80
#define OS2MSG_FILENAME TEXT("BASE")
#define PARM_ERROR_NONE 0
#define PARM_ERROR_UNKNOWN ((DWORD)-1)
#define PARMNUM_ALL 0
#define PARMNUM_BASE_INFOLEVEL 1000
#define PATHLEN 256
#define PLATFORM_ID_DOS 300
#define PLATFORM_ID_NT 500
#define PLATFORM_ID_OS2 400
#define PLATFORM_ID_OSF 600
#define PLATFORM_ID_VMS 700
#define PWLEN 256
#define QNLEN NNLEN
#define RMLEN (UNCLEN+1+NNLEN)
#define SESSION_CRYPT_KLEN 21
#define SESSION_PWLEN 24
#define SHPWLEN 8
#define SNLEN 80
#define STXTLEN 256
#define UNCLEN (CNLEN
#define UNLEN 256

#endif /* _LMCONS_ */
