/* lmuse.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 18 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMUSE_
#define _LMUSE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define USE_ASGTYPE_PARMNUM 4
#define USE_CHARDEV 2
#define USE_CONN 4
#define USE_DISCONN 2
#define USE_DISKDEV 0
#define USE_DOMAINNAME_PARMNUM 6
#define USE_IPC 3
#define USE_LOCAL_PARMNUM 1
#define USE_NETERR 3
#define USE_OK 0
#define USE_PASSWORD_PARMNUM 3
#define USE_PAUSED 1
#define USE_RECONN 5
#define USE_REMOTE_PARMNUM 2
#define USE_SESSLOST 2
#define USE_SPOOLDEV 1
#define USE_USERNAME_PARMNUM 5
#define USE_WILDCARD ((DWORD)-1)

#endif /* _LMUSE_ */
