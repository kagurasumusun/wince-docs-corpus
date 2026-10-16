/* Loadauth.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 6 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LOADAUTH_
#define _LOADAUTH_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define WIN_CERT_REVISION_1_0 0x0100
#define WIN_CERT_REVISION_2_0 0x0200
#define WIN_CERT_TYPE_PKCS1_SIGN 0x0009
#define WIN_CERT_TYPE_PKCS_SIGNED_DATA 0x0002
#define WIN_CERT_TYPE_RESERVED_1 0x0003
#define WIN_CERT_TYPE_X509 0x0001

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* WIN_CERTIFICATE  [struct; shared] */
typedef struct WIN_CERTIFICATE {
 DWORD dwLength;
 WORD wRevision;
 WORD wCertificateType;
 BYTE bCertificate[];
} WIN_CERTIFICATE, *LPWIN_CERTIFICATE;

#endif /* _LOADAUTH_ */
