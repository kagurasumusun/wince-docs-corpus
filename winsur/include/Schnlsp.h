/* Schnlsp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 3 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SCHNLSP_
#define _SCHNLSP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define SECPKG_ATTR_CIPHER_STRENGTHS 87
#define SECPKG_ATTR_SUPPORTED_ALGS 86
#define SECPKG_ATTR_SUPPORTED_PROTOCOLS 88

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* SecPkgContext_MasterKeyInfo  [struct; ce-only] */
typedef struct _SecPkgContext_MasterKeyInfo {
 DWORD dwVersion;
 DWORD cbMasterKey;
 BYTE rgbMasterKey[512];
 DWORD cbClientRandom;
 BYTE rgbClientRandom[512];
 DWORD cbServerRandom;
 BYTE rgbServerRandom[512];
}SecPkgContext_MasterKeyInfo, *PSecPkgContext_MasterKeyInfo;

/* SecPkgCred_CipherStrengths  [struct; ce-only] */
typedef struct _SecPkgCred_CipherStrengths { 
 DWORD dwMinimumCipherStrength; 
 DWORD dwMaximumCipherStrength; 
} SecPkgCred_CipherStrengths, *PSecPkgCred_CipherStrengths;

/* SecPkgCred_SupportedProtocols  [struct; ce-only] */
typedef struct _SecPkgCred_SupportedProtocols { 
 DWORD grbitProtocol; 
} SecPkgCred_SupportedProtocols, *PSecPkgCred_SupportedProtocols;

#endif /* _SCHNLSP_ */
