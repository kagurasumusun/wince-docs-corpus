/* Sspi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 39 constants, 12 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _SSPI_
#define _SSPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ACQUIRE_CREDENTIALS_HANDLE_FN ACQUIRE_CREDENTIALS_HANDLE_FN_W
#define APPLY_CONTROL_TOKEN_FN APPLY_CONTROL_TOKEN_FN_W
#define ENUMERATE_SECURITY_PACKAGES_FN ENUMERATE_SECURITY_PACKAGES_FN_W
#define INIT_SECURITY_INTERFACE INIT_SECURITY_INTERFACE_W
#define INITIALIZE_SECURITY_CONTEXT_FN INITIALIZE_SECURITY_CONTEXT_FN_W
#define QUERY_CONTEXT_ATTRIBUTES_FN QUERY_CONTEXT_ATTRIBUTES_FN_W
#define QUERY_CREDENTIALS_ATTRIBUTES_FN QUERY_CREDENTIALS_ATTRIBUTES_FN_W
#define QUERY_SECURITY_PACKAGE_INFO_FN QUERY_SECURITY_PACKAGE_INFO_FN_W
#define SECBUFFER_ATTRMASK 0xf0000000
#define SECBUFFER_DATA 2
#define SECBUFFER_EMPTY 4
#define SECBUFFER_EXTRA 5
#define SECBUFFER_MISSING 4
#define SECBUFFER_PADDING 9
#define SECBUFFER_PKG_PARAMS 3
#define SECBUFFER_READONLY 0x80000000
#define SECBUFFER_STREAM 10
#define SECBUFFER_STREAM_HEADER 1
#define SECBUFFER_STREAM_TRAILER 3
#define SECBUFFER_TOKEN 2
#define SECBUFFER_VERSION 0
#define SECPKG_ATTR_AUTHORITY 6
#define SECPKG_ATTR_CONNECTION_INFO 90
#define SECPKG_ATTR_ISSUER_LIST 80
#define SECPKG_ATTR_ISSUER_LIST_EX 89
#define SECPKG_ATTR_KEY_INFO 5
#define SECPKG_ATTR_LIFESPAN 2
#define SECPKG_ATTR_LOCAL_CERT_CONTEXT 84
#define SECPKG_ATTR_LOCAL_CRED 82
#define SECPKG_ATTR_NAMES 1
#define SECPKG_ATTR_PROTO_INFO 7
#define SECPKG_ATTR_REMOTE_CERT_CONTEXT 83
#define SECPKG_ATTR_REMOTE_CRED 81
#define SECPKG_ATTR_STREAM_SIZES 4
#define SECPKG_CRED_ATTR_NAMES 1
#define SECPKG_CRED_BOTH (SECPKG_CRED_OUTBOUND|SECPKG_CRED_INBOUND)
#define UNISP_NAME UNISP_NAME_W

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SecBuffer  [struct, typedef; shared] */
typedef struct _SecBuffer {
 ULONG cbBuffer;
 ULONG BufferType;
 PVOID pvBuffer;
} SecBuffer, *PSecBuffer;

/* SecBufferDesc  [struct, typedef; shared] */
typedef struct _SecBufferDesc {
 ULONG ulVersion;
 ULONG cBuffers;
 PSecBuffer pBuffers;
} SecBufferDesc, *PSecBufferDesc;

/* SecPkgContext_StreamSizes  [struct, typedef; shared] */
typedef struct _SecPkgContext_StreamSizes {
 unsigned long cbHeader;
 unsigned long cbTrailer;
 unsigned long cbMaximumMessage;
 unsigned long cBuffers;
 unsigned long cbBlockSize;
}SecPkgContext_StreamSizes, *PSecPkgContext_StreamSizes;

#endif /* _SSPI_ */
