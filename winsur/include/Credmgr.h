/* Credmgr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CREDMGR_
#define _CREDMGR_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CRED_FLAGS_PROMPT_NOW 2
#define CRED_PERSIST_LOCAL_MACHINE 2
#define CRED_PERSIST_SESSION 1
#define CRED_TYPE_DOMAIN_CERTIFICATE 3
#define CRED_TYPE_DOMAIN_PASSWORD 2
#define CRED_TYPE_DOMAIN_VISIBLE_PASSWORD 4
#define CRED_TYPE_GENERIC 1
#define CRED_TYPE_KERBEROS_PASSWORD 6
#define CRED_TYPE_NTLM_PASSWORD 5

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CREDENTIAL  [struct; shared; A/W CREDENTIALA,CREDENTIALW (CE is W-side)] */
typedef struct _CREDENTIAL {
 DWORD Flags;
 DWORD Type;
 FILETIME LastWritten;
 DWORD CredentialBlobSize;
 LPBYTE CredentialBlob;
 DWORD Persist;
 LPTSTR UserName;
} CREDENTIAL, *PCREDENTIAL;

#endif /* _CREDMGR_ */
