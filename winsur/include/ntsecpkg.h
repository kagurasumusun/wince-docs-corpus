/* ntsecpkg.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 38 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _NTSECPKG_
#define _NTSECPKG_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ASC_REQ_ALLOCATE_MEMORY 256
#define ASC_REQ_CONFIDENTIALITY 16
#define ASC_REQ_CONNECTION 2048
#define ASC_REQ_DATAGRAM 1024
#define ASC_REQ_DELEGATE 1
#define ASC_REQ_EXTENDED_ERROR 32768
#define ASC_REQ_INTEGRITY 131072
#define ASC_REQ_MUTUAL_AUTH 2
#define ASC_REQ_REPLAY_DETECT 4
#define ASC_REQ_SEQUENCE_DETECT 8
#define ASC_REQ_STREAM 65536
#define ASC_REQ_USE_DCE_STYLE 512
#define ASC_REQ_USE_SESSION_KEY 32
#define ISC_REQ_ALLOCATE_MEMORY 256
#define ISC_REQ_CONFIDENTIALITY 16
#define ISC_REQ_CONNECTION 2048
#define ISC_REQ_DATAGRAM 1024
#define ISC_REQ_DELEGATE 1
#define ISC_REQ_EXTENDED_ERROR 16384
#define ISC_REQ_HTTP 268435456
#define ISC_REQ_INTEGRITY 65536
#define ISC_REQ_MANUAL_CRED_VALIDATION 524288
#define ISC_REQ_MUTUAL_AUTH 2
#define ISC_REQ_PROMPT_FOR_CREDS 64
#define ISC_REQ_REPLAY_DETECT 4
#define ISC_REQ_SEQUENCE_DETECT 8
#define ISC_REQ_STREAM 32768
#define ISC_REQ_USE_DCE_STYLE 512
#define ISC_REQ_USE_SESSION_KEY 32
#define ISC_REQ_USE_SUPPLIED_CREDS 128
#define ISC_RET_EXTENDED_ERROR 16384
#define SECPKG_STATE_DOMAIN_CONTROLLER 0x04
#define SECPKG_STATE_ENCRYPTION_PERMITTED 0x01
#define SECPKG_STATE_STANDALONE 0x10
#define SECPKG_STATE_STRONG_ENCRYPTION_PERMITTED 0x02
#define SECPKG_STATE_WORKSTATION 0x08
#define SECURITY_NATIVE_DREP 16
#define SECURITY_NETWORK_DREP 0

#endif /* _NTSECPKG_ */
