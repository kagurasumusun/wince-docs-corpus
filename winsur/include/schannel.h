/* schannel.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 45 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SCHANNEL_
#define _SCHANNEL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define AUTHTYPE_CLIENT 1
#define AUTHTYPE_SERVER 2
#define SCH_CRED_AUTO_CRED_VALIDATION 0x00000020
#define SCH_CRED_CACHE_ONLY_URL_RETRIEVAL_ON_CREATE 0x00020000
#define SCH_CRED_DISABLE_RECONNECTS 0x00000080
#define SCH_CRED_FORMAT_CERT_HASH 0x00000001
#define SCH_CRED_FORMAT_CERT_HASH_STORE 0x00000002
#define SCH_CRED_IGNORE_NO_REVOCATION_CHECK 0x00000800
#define SCH_CRED_IGNORE_REVOCATION_OFFLINE 0x00001000
#define SCH_CRED_MANUAL_CRED_VALIDATION 0x00000008
#define SCH_CRED_NO_DEFAULT_CREDS 0x00000010
#define SCH_CRED_NO_SERVERNAME_CHECK 0x00000004
#define SCH_CRED_NO_SYSTEM_MAPPER 0x00000002
#define SCH_CRED_REVOCATION_CHECK_CHAIN 0x00000200
#define SCH_CRED_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT 0x00000400
#define SCH_CRED_REVOCATION_CHECK_END_CERT 0x00000100
#define SCH_CRED_USE_DEFAULT_CREDS 0x00000040
#define SCH_SEND_AUX_RECORD 0x00200000
#define SCH_SEND_ROOT_CERT 0x00040000
#define SCH_USE_PRESHAREDKEY_ONLY 0x00800000
#define SCH_USE_STRONG_CRYPTO 0x00400000
#define SCHANNEL_CRED_VERSION 4
#define SCHANNEL_SHUTDOWN 1
#define SP_PROT_DTLS1_2_CLIENT 0x00080000
#define SP_PROT_DTLS1_2_SERVER 0x00040000
#define SP_PROT_DTLS_CLIENT 0x00020000
#define SP_PROT_DTLS_SERVER 0x00010000
#define SP_PROT_PCT1 (SP_PROT_PCT1_CLIENT|SP_PROT_PCT1_SERVER)
#define SP_PROT_PCT1_CLIENT 0x00000002
#define SP_PROT_PCT1_SERVER 0x00000001
#define SP_PROT_SSL2 (SP_PROT_SSL2_CLIENT|SP_PROT_SSL2_SERVER)
#define SP_PROT_SSL2_CLIENT 0x00000008
#define SP_PROT_SSL2_SERVER 0x00000004
#define SP_PROT_SSL3 (SP_PROT_SSL3_CLIENT|SP_PROT_SSL3_SERVER)
#define SP_PROT_SSL3_CLIENT 0x00000020
#define SP_PROT_SSL3_SERVER 0x00000010
#define SP_PROT_TLS1 (SP_PROT_TLS1_CLIENT|SP_PROT_TLS1_SERVER)
#define SP_PROT_TLS1_1_CLIENT 0x00000200
#define SP_PROT_TLS1_1_SERVER 0x00000100
#define SP_PROT_TLS1_2_CLIENT 0x00000800
#define SP_PROT_TLS1_2_SERVER 0x00000400
#define SP_PROT_TLS1_3_CLIENT 0x00002000
#define SP_PROT_TLS1_3_SERVER 0x00001000
#define SP_PROT_TLS1_CLIENT 0x00000080
#define SP_PROT_TLS1_SERVER 0x00000040

#endif /* _SCHANNEL_ */
