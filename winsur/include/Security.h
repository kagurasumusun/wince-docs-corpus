/* Security.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 48 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 17 extra decls
 */
#ifndef _SECURITY_
#define _SECURITY_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SEC_E_CERT_EXPIRED (-2146893016)
#define SEC_E_NOT_OWNER (-2146893050)
#define SEC_E_QOP_NOT_SUPPORTED (-2146893046)
#define SEC_E_TARGET_UNKNOWN (-2146893053)
#define SEC_E_UNKNOWN_CREDENTIALS (-2146893043)
#define SEC_E_UNTRUSTED_ROOT (-2146893019)
#define SEC_E_WRONG_PRINCIPAL (-2146893022)
#define SEC_I_INCOMPLETE_CREDENTIALS 590624
#define SEC_I_RENEGOTIATE 590625
#define SECBUFFER_APPLICATION_PROTOCOLS 18
#define SECPKG_ATTR_C_ACCESS_TOKEN 0x80000012
#define SECPKG_ATTR_C_FULL_ACCESS_TOKEN 0x80000082
#define SECPKG_ATTR_CERT_TRUST_STATUS 0x80000084
#define SECPKG_ATTR_CREDS 0x80000080
#define SECPKG_ATTR_CREDS_2 0x80000086
#define SECPKG_ATTR_NEGOTIATION_PACKAGE 0x80000081
#define SECPKG_ATTR_PACKAGE_INFO 10
#define SECPKG_ATTR_SERVER_AUTH_FLAGS 0x80000083
#define SECPKG_ATTR_SIZES 0x0
#define SECPKG_ATTR_SUBJECT_SECURITY_ATTRIBUTES 124
#define SECPKG_CALLFLAGS_APPCONTAINER 0x00000001
#define SECPKG_CALLFLAGS_AUTHCAPABLE 0x00000002
#define SECPKG_CALLFLAGS_FORCE_SUPPLIED 0x00000004
#define SECPKG_CRED_INBOUND 0x1
#define SECPKG_CRED_OUTBOUND 0x2
#define SECPKG_FLAG_ACCEPT_WIN32_NAME 0x200
#define SECPKG_FLAG_APPCONTAINER_CHECKS 0x00800000
#define SECPKG_FLAG_APPCONTAINER_PASSTHROUGH 0x00400000
#define SECPKG_FLAG_ASCII_BUFFERS 0x4000
#define SECPKG_FLAG_CLIENT_ONLY 0x40
#define SECPKG_FLAG_CONNECTION 0x10
#define SECPKG_FLAG_DATAGRAM 0x8
#define SECPKG_FLAG_DELEGATION 0x20000
#define SECPKG_FLAG_EXTENDED_ERROR 0x80
#define SECPKG_FLAG_FRAGMENT 0x8000
#define SECPKG_FLAG_GSS_COMPATIBLE 0x1000
#define SECPKG_FLAG_IMPERSONATION 0x100
#define SECPKG_FLAG_INTEGRITY 0x1
#define SECPKG_FLAG_LOGON 0x2000
#define SECPKG_FLAG_MULTI_REQUIRED 0x20
#define SECPKG_FLAG_MUTUAL_AUTH 0x10000
#define SECPKG_FLAG_NEGO_EXTENDER 0x00100000
#define SECPKG_FLAG_NEGOTIABLE2 0x00200000
#define SECPKG_FLAG_PRIVACY 0x2
#define SECPKG_FLAG_READONLY_WITH_CHECKSUM 0x40000
#define SECPKG_FLAG_RESTRICTED_TOKENS 0x80000
#define SECPKG_FLAG_STREAM 0x400
#define SECPKG_FLAG_TOKEN_ONLY 0x4

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
PSecurityFunctionTable InitSecurityInterface(VOID);

#endif /* _SECURITY_ */
