/* Wincrypt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 580 constants, 195 declarations, 3 outlines, 0 base types, 0 extra macros, 16 extra decls
 */
#ifndef _WINCRYPT_
#define _WINCRYPT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ALG_CLASS_ALL 57344
#define ALG_CLASS_ANY 0
#define ALG_CLASS_DATA_ENCRYPT 24576
#define ALG_CLASS_HASH 32768
#define ALG_CLASS_KEY_EXCHANGE 40960
#define ALG_CLASS_MSG_ENCRYPT 16384
#define ALG_CLASS_SIGNATURE 8192
#define ALG_SID_3DES 3
#define ALG_SID_3DES_112 9
#define ALG_SID_AES 17
#define ALG_SID_AES_128 14
#define ALG_SID_AES_192 15
#define ALG_SID_AES_256 16
#define ALG_SID_ANY 0
#define ALG_SID_CAST 6
#define ALG_SID_CYLINK_MEK 12
#define ALG_SID_DES 1
#define ALG_SID_DESX 4
#define ALG_SID_DSS_ANY 0
#define ALG_SID_DSS_DMS 2
#define ALG_SID_DSS_PKCS 1
#define ALG_SID_EXAMPLE 80
#define ALG_SID_HMAC 9
#define ALG_SID_IDEA 5
#define ALG_SID_MAC 5
#define ALG_SID_MD2 1
#define ALG_SID_MD4 2
#define ALG_SID_MD5 3
#define ALG_SID_RC2 2
#define ALG_SID_RC4 1
#define ALG_SID_RC5 13
#define ALG_SID_RIPEMD 6
#define ALG_SID_RIPEMD160 7
#define ALG_SID_RSA_ANY 0
#define ALG_SID_RSA_ENTRUST 3
#define ALG_SID_RSA_MSATWORK 2
#define ALG_SID_RSA_PGP 4
#define ALG_SID_RSA_PKCS 1
#define ALG_SID_SAFERSK128 8
#define ALG_SID_SAFERSK64 7
#define ALG_SID_SEAL 2
#define ALG_SID_SHA 4
#define ALG_SID_SKIPJACK 10
#define ALG_SID_SSL3SHAMD5 8
#define ALG_SID_TEK 11
#define ALG_SID_TLS1PRF 10
#define ALG_TYPE_ANY 0
#define ALG_TYPE_BLOCK 1536
#define ALG_TYPE_DH 2560
#define ALG_TYPE_DSS 512
#define ALG_TYPE_RSA 1024
#define ALG_TYPE_SECURECHANNEL 3072
#define ALG_TYPE_STREAM 2048
#define AT_KEYEXCHANGE 1
#define AT_SIGNATURE 2
#define CALG_3DES (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|3)
#define CALG_AES (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES)
#define CALG_AES_128 (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_128)
#define CALG_AES_192 (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_192)
#define CALG_AES_256 (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_AES_256)
#define CALG_CYLINK_MEK (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|12)
#define CALG_DES (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_DES)
#define CALG_DESX (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_DESX)
#define CALG_DH_EPHEM (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_STREAM|ALG_TYPE_DSS|ALG_SID_DSS_DMS)
#define CALG_DSS_SIGN (ALG_CLASS_SIGNATURE|ALG_TYPE_DSS|ALG_SID_DSS_ANY)
#define CALG_KEA_KEYX (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_STREAM|ALG_TYPE_DSS|4)
#define CALG_MAC (ALG_CLASS_HASH|ALG_TYPE_ANY|ALG_SID_MAC)
#define CALG_MD2 (ALG_CLASS_HASH|ALG_TYPE_ANY|ALG_SID_MD2)
#define CALG_MD4 (ALG_CLASS_HASH|ALG_TYPE_ANY|ALG_SID_MD4)
#define CALG_MD5 (ALG_CLASS_HASH|ALG_TYPE_ANY|ALG_SID_MD5)
#define CALG_RC2 (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_RC2)
#define CALG_RC4 (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_STREAM|ALG_SID_RC4)
#define CALG_RSA_KEYX (ALG_CLASS_KEY_EXCHANGE|ALG_TYPE_RSA|ALG_SID_RSA_ANY)
#define CALG_RSA_SIGN (ALG_CLASS_SIGNATURE|ALG_TYPE_RSA|ALG_SID_RSA_ANY)
#define CALG_SEAL (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_STREAM|ALG_SID_SEAL)
#define CALG_SHA (ALG_CLASS_HASH|ALG_TYPE_ANY|ALG_SID_SHA)
#define CALG_SHA1 CALG_SHA
#define CALG_SKIPJACK (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|10)
#define CALG_SSL3_SHAMD5 (ALG_CLASS_HASH
#define CALG_TLS1PRF (ALG_CLASS_DHASH|ALG_TYPE_ANY|ALG_SID_TLS1PRF)
#define CERT_ACCESS_STATE_PROP_ID 14
#define CERT_ARCHIVED_PROP_ID 19
#define CERT_AUTO_ENROLL_PROP_ID 21
#define CERT_CASE_INSENSITIVE_IS_RDN_ATTRS_FLAG 2
#define CERT_CHAIN_CACHE_END_CERT 0x00000001
#define CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL 0x00000004
#define CERT_CHAIN_DISABLE_AIA 0x00002000
#define CERT_CHAIN_DISABLE_AUTH_ROOT_AUTO_UPDATE 0x00000100
#define CERT_CHAIN_DISABLE_MY_PEER_TRUST 0x00000800
#define CERT_CHAIN_ENABLE_CACHE_AUTO_UPDATE 0x00000010
#define CERT_CHAIN_ENABLE_PEER_TRUST 0x00000400
#define CERT_CHAIN_ENABLE_SHARE_STORE 0x00000020
#define CERT_CHAIN_EXCLUSIVE_ENABLE_CA_FLAG 0x00000001
#define CERT_CHAIN_FIND_BY_ISSUER 1
#define CERT_CHAIN_FIND_BY_ISSUER_CACHE_ONLY_FLAG 32768
#define CERT_CHAIN_FIND_BY_ISSUER_CACHE_ONLY_URL_FLAG 4
#define CERT_CHAIN_FIND_BY_ISSUER_COMPARE_KEY_FLAG 1
#define CERT_CHAIN_FIND_BY_ISSUER_COMPLEX_CHAIN_FLAG 2
#define CERT_CHAIN_FIND_BY_ISSUER_LOCAL_MACHINE_FLAG 8
#define CERT_CHAIN_FIND_BY_ISSUER_NO_KEY_FLAG 16384
#define CERT_CHAIN_OPT_IN_WEAK_SIGNATURE 0x00010000
#define CERT_CHAIN_POLICY_AUTHENTICODE ((LPCSTR)
#define CERT_CHAIN_POLICY_AUTHENTICODE_TS ((LPCSTR)
#define CERT_CHAIN_POLICY_BASE ((LPCSTR)
#define CERT_CHAIN_POLICY_BASIC_CONSTRAINTS ((LPCSTR)
#define CERT_CHAIN_POLICY_NT_AUTH ((LPCSTR)
#define CERT_CHAIN_POLICY_SSL ((LPCSTR)
#define CERT_CHAIN_RETURN_LOWER_QUALITY_CONTEXTS 0x00000080
#define CERT_CHAIN_REVOCATION_ACCUMULATIVE_TIMEOUT 0x08000000
/* NOT SUPPORTED per chm/windows-ce-5.0/wcecertificates5/html: The desktop operating system supports the following dwFlags flags that Windows CE does not support: [corpus/chm/windows-ce-5.0/wcecertificates5/html/wce50lrfCertGetCertificateChain.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: The desktop operating system supports the following dwFlags flags that Windows CE does not support: [corpus/learn/windows-ce-5.0/ms937660(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-ce-net-4x: The desktop platform supports the following dwFlags flags that Windows CE does not support: [corpus/learn/windows-ce-net-4x/ms883844(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: The desktop operating system supports the following dwFlags flags that Windows Embedded CE does not support: [corpus/learn/windows-embedded-ce-6.0/ee498136(v=winembedded.60).html] */
#define CERT_CHAIN_REVOCATION_CHECK_CACHE_ONLY 0x80000000
/* NOT SUPPORTED per chm/windows-ce-5.0/wcecertificates5/html: The desktop operating system supports the following dwFlags flags that Windows CE does not support: [corpus/chm/windows-ce-5.0/wcecertificates5/html/wce50lrfCertGetCertificateChain.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: The desktop operating system supports the following dwFlags flags that Windows CE does not support: [corpus/learn/windows-ce-5.0/ms937660(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-ce-net-4x: The desktop platform supports the following dwFlags flags that Windows CE does not support: [corpus/learn/windows-ce-net-4x/ms883844(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: The desktop operating system supports the following dwFlags flags that Windows Embedded CE does not support: [corpus/learn/windows-embedded-ce-6.0/ee498136(v=winembedded.60).html] */
#define CERT_CHAIN_REVOCATION_CHECK_CHAIN 0x20000000
/* NOT SUPPORTED per chm/windows-ce-5.0/wcecertificates5/html: The desktop operating system supports the following dwFlags flags that Windows CE does not support: [corpus/chm/windows-ce-5.0/wcecertificates5/html/wce50lrfCertGetCertificateChain.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: The desktop operating system supports the following dwFlags flags that Windows CE does not support: [corpus/learn/windows-ce-5.0/ms937660(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-ce-net-4x: The desktop platform supports the following dwFlags flags that Windows CE does not support: [corpus/learn/windows-ce-net-4x/ms883844(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: The desktop operating system supports the following dwFlags flags that Windows Embedded CE does not support: [corpus/learn/windows-embedded-ce-6.0/ee498136(v=winembedded.60).html] */
#define CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT 0x40000000
/* NOT SUPPORTED per chm/windows-ce-5.0/wcecertificates5/html: The desktop operating system supports the following dwFlags flags that Windows CE does not support: [corpus/chm/windows-ce-5.0/wcecertificates5/html/wce50lrfCertGetCertificateChain.html] */
/* NOT SUPPORTED per learn/windows-ce-5.0: The desktop operating system supports the following dwFlags flags that Windows CE does not support: [corpus/learn/windows-ce-5.0/ms937660(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-ce-net-4x: The desktop platform supports the following dwFlags flags that Windows CE does not support: [corpus/learn/windows-ce-net-4x/ms883844(v=msdn.10).html] */
/* NOT SUPPORTED per learn/windows-embedded-ce-6.0: The desktop operating system supports the following dwFlags flags that Windows Embedded CE does not support: [corpus/learn/windows-embedded-ce-6.0/ee498136(v=winembedded.60).html] */
#define CERT_CHAIN_REVOCATION_CHECK_END_CERT 0x10000000
#define CERT_CHAIN_REVOCATION_CHECK_OCSP_CERT 0x04000000
#define CERT_CHAIN_STRONG_SIGN_DISABLE_END_CHECK_FLAG 0x00000001
#define CERT_CHAIN_TIMESTAMP_TIME 0x00000200
#define CERT_CHAIN_USE_LOCAL_MACHINE_STORE 0x00000008
#define CERT_CROSS_CERT_DIST_POINTS_PROP_ID 23
#define CERT_CTL_USAGE_PROP_ID CERT_ENHKEY_USAGE_PROP_ID
#define CERT_DATE_STAMP_PROP_ID 27
#define CERT_DESCRIPTION_PROP_ID 13
#define CERT_E_CHAINING (-2146762486)
#define CERT_E_CN_NO_MATCH (-2146762481)
#define CERT_E_CRITICAL (-2146762491)
#define CERT_E_EXPIRED (-2146762495)
#define CERT_E_ISSUERCHAINING (-2146762489)
#define CERT_E_MALFORMED (-2146762488)
#define CERT_E_PATHLENCONST (-2146762492)
#define CERT_E_PURPOSE (-2146762490)
#define CERT_E_REVOCATION_FAILURE (-2146762482)
#define CERT_E_REVOKED (-2146762484)
#define CERT_E_ROLE (-2146762493)
#define CERT_E_UNTRUSTEDROOT (-2146762487)
#define CERT_E_UNTRUSTEDTESTROOT (-2146762483)
#define CERT_E_VALIDITYPERIODNESTING (-2146762494)
#define CERT_E_WRONG_USAGE (-2146762480)
#define CERT_EFS_PROP_ID 17
#define CERT_ENHKEY_USAGE_PROP_ID 9
#define CERT_ENROLLMENT_PROP_ID 26
#define CERT_EXTENDED_ERROR_INFO_PROP_ID 30
#define CERT_FIND_ANY 0
#define CERT_FIND_CERT_ID 1048576
#define CERT_FIND_CTL_USAGE 655360
#define CERT_FIND_ENHKEY_USAGE 655360
#define CERT_FIND_EXISTING 851968
#define CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG 2
#define CERT_FIND_HASH 65536
#define CERT_FIND_ISSUER_ATTR 196612
#define CERT_FIND_ISSUER_NAME 131076
#define CERT_FIND_ISSUER_OF 786432
#define CERT_FIND_ISSUER_STR CERT_FIND_ISSUER_STR_W
#define CERT_FIND_ISSUER_STR_A 458756
#define CERT_FIND_ISSUER_STR_W 524292
#define CERT_FIND_KEY_IDENTIFIER 983040
#define CERT_FIND_KEY_SPEC 589824
#define CERT_FIND_MD5_HASH 262144
#define CERT_FIND_NO_ENHKEY_USAGE_FLAG 8
#define CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG 1
#define CERT_FIND_OR_ENHKEY_USAGE_FLAG 16
#define CERT_FIND_PROPERTY 327680
#define CERT_FIND_PUBLIC_KEY 393216
#define CERT_FIND_SHA1_HASH 65536
#define CERT_FIND_SIGNATURE_HASH 917504
#define CERT_FIND_SUBJECT_ATTR 196615
#define CERT_FIND_SUBJECT_CERT 720896
#define CERT_FIND_SUBJECT_NAME 131079
#define CERT_FIND_SUBJECT_STR CERT_FIND_SUBJECT_STR_W
#define CERT_FIND_SUBJECT_STR_A 458759
#define CERT_FIND_SUBJECT_STR_W 524295
#define CERT_FIND_VALID_ENHKEY_USAGE_FLAG 32
#define CERT_FORTEZZA_DATA_PROP_ID 18
#define CERT_FRIENDLY_NAME_PROP_ID 11
#define CERT_HASH_PROP_ID CERT_SHA1_HASH_PROP_ID
#define CERT_IE30_RESERVED_PROP_ID 7
#define CERT_ISSUER_PUBLIC_KEY_MD5_HASH_PROP_ID 24
#define CERT_ISSUER_SERIAL_NUMBER_MD5_HASH_PROP_ID 28
#define CERT_KEY_CONTEXT_PROP_ID 5
#define CERT_KEY_IDENTIFIER_PROP_ID 20
#define CERT_KEY_PROV_HANDLE_PROP_ID 1
#define CERT_KEY_PROV_INFO_PROP_ID 2
#define CERT_KEY_SPEC_PROP_ID 6
#define CERT_MD5_HASH_PROP_ID 4
#define CERT_NAME_ATTR_TYPE 3
#define CERT_NAME_DISABLE_IE4_UTF8_FLAG 0x00010000
#define CERT_NAME_DNS_TYPE 6
#define CERT_NAME_EMAIL_TYPE 1
#define CERT_NAME_FRIENDLY_DISPLAY_TYPE 5
#define CERT_NAME_ISSUER_FLAG 0x1
#define CERT_NAME_RDN_TYPE 2
#define CERT_NAME_SEARCH_ALL_NAMES_FLAG 0x2
#define CERT_NAME_SIMPLE_DISPLAY_TYPE 4
#define CERT_NAME_STR_COMMA_FLAG 0x04000000
#define CERT_NAME_STR_CRLF_FLAG 0x08000000
#define CERT_NAME_STR_DISABLE_IE4_UTF8_FLAG 0x00010000
#define CERT_NAME_STR_DISABLE_UTF8_DIR_STR_FLAG 0x00100000
#define CERT_NAME_STR_ENABLE_PUNYCODE_FLAG 0x00200000
#define CERT_NAME_STR_ENABLE_T61_UNICODE_FLAG 0x00020000
#define CERT_NAME_STR_ENABLE_UTF8_UNICODE_FLAG 0x00040000
#define CERT_NAME_STR_FORCE_UTF8_DIR_STR_FLAG 0x00080000
#define CERT_NAME_STR_NO_PLUS_FLAG 0x20000000
#define CERT_NAME_STR_NO_QUOTING_FLAG 0x10000000
#define CERT_NAME_STR_REVERSE_FLAG 0x02000000
#define CERT_NAME_STR_SEMICOLON_FLAG 0x40000000
#define CERT_NAME_UPN_TYPE 8
#define CERT_NAME_URL_TYPE 7
#define CERT_NEXT_UPDATE_LOCATION_PROP_ID 10
#define CERT_OID_NAME_STR 2
#define CERT_PUBKEY_ALG_PARA_PROP_ID 22
#define CERT_PUBKEY_HASH_RESERVED_PROP_ID 8
#define CERT_PVK_FILE_PROP_ID 12
#define CERT_REVOKED 0x00000001
#define CERT_SET_KEY_CONTEXT_PROP_ID 0x00000001
#define CERT_SET_KEY_PROV_HANDLE_PROP_ID 0x00000001
#define CERT_SHA1_HASH_PROP_ID 3
#define CERT_SIGNATURE_HASH_PROP_ID 15
#define CERT_SIMPLE_NAME_STR 1
#define CERT_SMART_CARD_DATA_PROP_ID 16
#define CERT_STORE_ADD_ALWAYS 4
#define CERT_STORE_ADD_NEW 1
#define CERT_STORE_ADD_NEWER 6
#define CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES 7
#define CERT_STORE_ADD_REPLACE_EXISTING 3
#define CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES 5
#define CERT_STORE_ADD_USE_EXISTING 2
#define CERT_STORE_PROV_SYSTEM 10
#define CERT_STORE_SAVE_AS_PKCS7 2
#define CERT_STORE_SAVE_AS_STORE 1
#define CERT_STORE_SAVE_TO_FILE 1
#define CERT_STORE_SAVE_TO_FILENAME 4
#define CERT_STORE_SAVE_TO_FILENAME_A 3
#define CERT_STORE_SAVE_TO_FILENAME_W 4
#define CERT_STORE_SAVE_TO_MEMORY 2
#define CERT_STORE_UNKNOWN 0x00000002
#define CERT_STORE_VALID 0x00000004
#define CERT_SUBJECT_NAME_MD5_HASH_PROP_ID 29
#define CERT_SUBJECT_PUBLIC_KEY_MD5_HASH_PROP_ID 25
#define CERT_SYSTEM_STORE_LOCAL_MACHINE 131072
#define CERT_TRUST_CTL_IS_NOT_SIGNATURE_VALID 0x00040000
#define CERT_TRUST_CTL_IS_NOT_TIME_VALID 0x00020000
#define CERT_TRUST_CTL_IS_NOT_VALID_FOR_USAGE 0x00080000
#define CERT_TRUST_HAS_CRL_VALIDITY_EXTENDED 0x00001000
#define CERT_TRUST_HAS_EXACT_MATCH_ISSUER 0x00000001
#define CERT_TRUST_HAS_EXCLUDED_NAME_CONSTRAINT 0x00008000
#define CERT_TRUST_HAS_ISSUANCE_CHAIN_POLICY 0x00000400
#define CERT_TRUST_HAS_KEY_MATCH_ISSUER 0x00000002
#define CERT_TRUST_HAS_NAME_MATCH_ISSUER 0x00000004
#define CERT_TRUST_HAS_NOT_DEFINED_NAME_CONSTRAINT 0x00002000
#define CERT_TRUST_HAS_NOT_PERMITTED_NAME_CONSTRAINT 0x00004000
#define CERT_TRUST_HAS_NOT_SUPPORTED_CRITICAL_EXT 0x08000000
#define CERT_TRUST_HAS_NOT_SUPPORTED_NAME_CONSTRAINT 0x00001000
#define CERT_TRUST_HAS_PREFERRED_ISSUER 0x00000100
#define CERT_TRUST_HAS_VALID_NAME_CONSTRAINTS 0x00000400
#define CERT_TRUST_HAS_WEAK_SIGNATURE 0x00100000
#define CERT_TRUST_INVALID_BASIC_CONSTRAINTS 0x00000400
#define CERT_TRUST_INVALID_EXTENSION 0x00000100
#define CERT_TRUST_INVALID_NAME_CONSTRAINTS 0x00000800
#define CERT_TRUST_INVALID_POLICY_CONSTRAINTS 0x00000200
#define CERT_TRUST_IS_CA_TRUSTED 0x00004000
#define CERT_TRUST_IS_COMPLEX_CHAIN 0x00010000
#define CERT_TRUST_IS_CYCLIC 0x00000080
#define CERT_TRUST_IS_EXPLICIT_DISTRUST 0x04000000
#define CERT_TRUST_IS_FROM_EXCLUSIVE_TRUST_STORE 0x00002000
#define CERT_TRUST_IS_NOT_SIGNATURE_VALID 0x00000008
#define CERT_TRUST_IS_NOT_TIME_NESTED 2
#define CERT_TRUST_IS_NOT_TIME_VALID 0x00000001
#define CERT_TRUST_IS_NOT_VALID_FOR_USAGE 0x00000010
#define CERT_TRUST_IS_OFFLINE_REVOCATION 0x01000000
#define CERT_TRUST_IS_PARTIAL_CHAIN 0x00010000
#define CERT_TRUST_IS_PEER_TRUSTED 0x00000800
#define CERT_TRUST_IS_REVOKED 0x00000004
#define CERT_TRUST_IS_SELF_SIGNED 0x00000008
#define CERT_TRUST_IS_UNTRUSTED_ROOT 0x00000020
#define CERT_TRUST_NO_ERROR 0x00000000
#define CERT_TRUST_NO_ISSUANCE_CHAIN_POLICY 0x02000000
#define CERT_TRUST_REVOCATION_STATUS_UNKNOWN 0x00000040
#define CERT_UNICODE_IS_RDN_ATTRS_FLAG 1
#define CERT_UNKNOWN 0x00000000
#define CERT_V1 0
#define CERT_V2 1
#define CERT_V3 2
#define CERT_X500_NAME_STR 3
#define CMC_ADD_ATTRIBUTES (LPCSTR)
#define CMC_ADD_EXTENSIONS (LPCSTR)
#define CMC_DATA (LPCSTR)
#define CMC_RESPONSE (LPCSTR)
#define CMC_STATUS (LPCSTR)
#define CMS_SIGNER_INFO (LPCSTR)
#define CNG_RSA_PUBLIC_KEY_BLOB (LPCSTR)
#define CRYPT_ACQUIRE_CACHE_FLAG 0x00000001
#define CRYPT_ACQUIRE_COMPARE_KEY_FLAG 0x00000004
#define CRYPT_ACQUIRE_SILENT_FLAG 0x00000040
#define CRYPT_ACQUIRE_USE_PROV_INFO_FLAG 0x00000002
#define CRYPT_ARCHIVABLE 0x00004000
#define CRYPT_BLOB_VER3 0x00000080
#define CRYPT_CREATE_IV 0x200
#define CRYPT_CREATE_SALT 4
#define CRYPT_DATA_KEY 0x800
#define CRYPT_DECRYPT 2
#define CRYPT_DECRYPT_RSA_NO_PADDING_CHECK 0x00000020
#define CRYPT_DELETE_DEFAULT 0x00000004
#define CRYPT_DELETEKEYSET 16
#define CRYPT_DESTROYKEY 0x00000004
#define CRYPT_ENCODE_ALLOC_FLAG 0x8000
#define CRYPT_ENCRYPT 1
#define CRYPT_EXPORT 4
#define CRYPT_EXPORTABLE 0x00000001
#define CRYPT_FAILED FALSE
#define CRYPT_FIRST 1
#define CRYPT_FLAG_IPSEC 0x0010
#define CRYPT_FLAG_PCT1 0x0001
#define CRYPT_FLAG_SIGNING 0x0020
#define CRYPT_FLAG_SSL2 0x0002
#define CRYPT_FLAG_SSL3 0x0004
#define CRYPT_FLAG_TLS1 0x0008
#define CRYPT_IMPL_HARDWARE 0x01
#define CRYPT_IMPL_MIXED 0x03
#define CRYPT_IMPL_REMOVABLE 0x08
#define CRYPT_IMPL_SOFTWARE 0x02
#define CRYPT_IMPL_UNKNOWN 0x04
#define CRYPT_INITIATOR 0x40
#define CRYPT_IPSEC_HMAC_KEY 0x00000100
#define CRYPT_KEK 0x400
#define CRYPT_KEYID_DELETE_FLAG 0x00000010
#define CRYPT_KEYID_SET_NEW_FLAG 0x00002000
#define CRYPT_LITTLE_ENDIAN 0x00000001
#define CRYPT_MAC 32
#define CRYPT_MAC_RESOURCE_NUMBER 0x29B
#define CRYPT_MACHINE_DEFAULT 0x00000001
#define CRYPT_MACHINE_KEYSET 0x00000020
#define CRYPT_MODE_CBC 1
#define CRYPT_MODE_CBCI 6
#define CRYPT_MODE_CBCOFM 9
#define CRYPT_MODE_CBCOFMI 10
#define CRYPT_MODE_CFB 4
#define CRYPT_MODE_CFBP 7
#define CRYPT_MODE_CTS 5
#define CRYPT_MODE_ECB 2
#define CRYPT_MODE_OFB 3
#define CRYPT_MODE_OFBP 8
#define CRYPT_NEWKEYSET 8
#define CRYPT_NEXT 2
#define CRYPT_NO_SALT 0x10
#define CRYPT_NOHASHOID 0x00000001
#define CRYPT_OAEP 0x00000040
#define CRYPT_ONLINE 0x80
#define CRYPT_OWF_REPL_LM_HASH 0x00000001
#define CRYPT_PREGEN 0x40
#define CRYPT_READ 8
#define CRYPT_RECIPIENT 0x10
#define CRYPT_SECRETDIGEST 0x00000001
#define CRYPT_SERVER 0x00000400
#define CRYPT_SF 0x100
#define CRYPT_SGCKEY 0x2000
#define CRYPT_SIG_RESOURCE_NUMBER 0x29A
#define CRYPT_SILENT 64
#define CRYPT_SSL2_FALLBACK 0x00000002
#define CRYPT_SUCCEED TRUE
#define CRYPT_TYPE2_FORMAT 0x00000002
#define CRYPT_UNICODE_NAME_ENCODE_DISABLE_CHECK_TYPE_FLAG 0x40000000
#define CRYPT_UNICODE_NAME_ENCODE_ENABLE_T61_UNICODE_FLAG 0x80000000
#define CRYPT_UNICODE_NAME_ENCODE_ENABLE_UTF8_UNICODE_FLAG 0x20000000
#define CRYPT_UNICODE_NAME_ENCODE_FORCE_UTF8_UNICODE_FLAG 0x10000000
#define CRYPT_UPDATE_KEY 8
#define CRYPT_USER_DEFAULT 0x00000002
#define CRYPT_USER_KEYSET 0x00001000
#define CRYPT_USER_PROTECTED 0x00000002
#define CRYPT_USERDATA 1
#define CRYPT_VERIFYCONTEXT 0xF0000000
#define CRYPT_VOLATILE 0x1000
#define CRYPT_WRITE 16
#define CRYPT_X931_FORMAT 0x00000004
#define CRYPT_Y_ONLY 0x00000001
#define CRYPTPROTECT_LOCAL_MACHINE 0x4
#define CRYPTPROTECT_UI_FORBIDDEN 0x1
#define CUR_BLOB_VERSION 2
#define ECC_CMS_SHARED_INFO (LPCSTR)
#define EXPORT_PRIVATE_KEYS 0x0004
#define HP_ALGID 1
#define HP_HASHSIZE 4
#define HP_HASHVAL 2
#define HP_HMAC_INFO 5
#define INTERNATIONAL_USAGE 0x00000001
#define KEY_LENGTH_MASK 0xFFFF0000
#define KEYSTATEBLOB 0xC
#define KP_ALGID 0x00000007
#define KP_BLOCKLEN 0x00000008
#define KP_EFFECTIVE_KEYLEN 0x00000013
#define KP_G 0x0000000c
#define KP_INFO 0x00000012
#define KP_IV 0x00000001
#define KP_KEYLEN 0x00000009
#define KP_MODE 0x00000004
#define KP_MODE_BITS 0x00000005
#define KP_P 0x0000000b
#define KP_PADDING 0x00000003
#define KP_PERMISSIONS 0x00000006
#define KP_PUB_PARAMS 0x00000027
#define KP_Q 0x0000000d
#define KP_RA 0x00000010
#define KP_RB 0x00000011
#define KP_SALT 0x00000002
#define KP_SALT_EX 0x0000000a
#define KP_SCHANNEL_ALG 0x00000014
#define KP_X 0x0000000e
#define KP_Y 0x0000000f
#define MAXUIDLEN 64
#define MS_DEF_DH_SCHANNEL_PROV MS_DEF_DH_SCHANNEL_PROV_W
#define MS_DEF_DSS_DH_PROV MS_DEF_DSS_DH_PROV_W
#define MS_DEF_DSS_PROV MS_DEF_DSS_PROV_W
#define MS_DEF_PROV MS_DEF_PROV_W
#define MS_DEF_RSA_SCHANNEL_PROV MS_DEF_RSA_SCHANNEL_PROV_W
#define MS_DEF_RSA_SIG_PROV MS_DEF_RSA_SIG_PROV_W
#define MS_ENH_DSS_DH_PROV MS_ENH_DSS_DH_PROV_W
#define MS_ENH_RSA_AES_PROV MS_ENH_RSA_AES_PROV_W
#define MS_ENHANCED_PROV MS_ENHANCED_PROV_W
#define MS_SCARD_PROV MS_SCARD_PROV_W
#define MS_STRONG_PROV MS_STRONG_PROV_W
#define OCSP_BASIC_RESPONSE (LPCSTR)
#define OCSP_BASIC_SIGNED_RESPONSE (LPCSTR)
#define OCSP_REQUEST (LPCSTR)
#define OCSP_RESPONSE (LPCSTR)
#define OCSP_SIGNED_REQUEST (LPCSTR)
#define OPAQUEKEYBLOB 0x9
#define PKCS12_ALLOW_OVERWRITE_KEY 0x00004000
#define PKCS12_ALWAYS_CNG_KSP 0x00000200
#define PKCS12_EXPORT_PBES2_PARAMS 0x0080
#define PKCS12_INCLUDE_EXTENDED_PROPERTIES 0x0010
#define PKCS12_NO_PERSIST_KEY 0x00008000
#define PKCS12_PREFER_CNG_KSP 0x00000100
#define PKCS12_PROTECT_TO_DOMAIN_SIDS 0x0020
#define PKCS5_PADDING 1
#define PKCS7_SIGNER_INFO (LPCSTR)
#define PKCS_7_ASN_ENCODING 65536
#define PKCS_ATTRIBUTE (LPCSTR)
#define PKCS_CONTENT_INFO (LPCSTR)
#define PKCS_CONTENT_INFO_SEQUENCE_OF_ANY (LPCSTR)
#define PKCS_CTL (LPCSTR)
#define PKCS_RC2_CBC_PARAMETERS (LPCSTR)
#define PKCS_RSA_SSA_PSS_PARAMETERS (LPCSTR)
#define PKCS_RSAES_OAEP_PARAMETERS (LPCSTR)
#define PKCS_SMIME_CAPABILITIES (LPCSTR)
#define PKCS_TIME_REQUEST (LPCSTR)
#define PKCS_UTC_TIME (LPCSTR)
#define PLAINTEXTKEYBLOB 0x8
#define PP_ADMIN_PIN 31
#define PP_APPLI_CERT 18
#define PP_CERTCHAIN 9
#define PP_CHANGE_PASSWORD 7
#define PP_CLIENT_HWND 0x1
#define PP_CONTAINER 6
#define PP_ENUMALGS 1
#define PP_ENUMALGS_EX 22
#define PP_ENUMCONTAINERS 2
#define PP_ENUMELECTROOTS 26
#define PP_ENUMEX_SIGNING_PROT 40
#define PP_ENUMMANDROOTS 25
#define PP_IMPTYPE 3
#define PP_KEY_TYPE_SUBTYPE 10
#define PP_KEYEXCHANGE_PIN 32
#define PP_KEYSET_SEC_DESCR 8
#define PP_KEYSET_TYPE 27
#define PP_KEYSPEC 39
#define PP_KEYSTORAGE 17
#define PP_KEYX_KEYSIZE_INC 35
#define PP_NAME 4
#define PP_PROVTYPE 16
#define PP_SESSION_KEYSIZE 20
#define PP_SGC_INFO 37
#define PP_SIG_KEYSIZE_INC 34
#define PP_SIGNATURE_PIN 33
#define PP_SYM_KEYSIZE 19
#define PP_UI_PROMPT 21
#define PP_UNIQUE_CONTAINER 36
#define PP_USE_HARDWARE_RNG 38
#define PP_VERSION 5
#define PRIVATEKEYBLOB 0x7
#define PROV_DH_SCHANNEL 18
#define PROV_DSS 3
#define PROV_DSS_DH 13
#define PROV_EC_ECDSA_FULL 16
#define PROV_EC_ECDSA_SIG 14
#define PROV_EC_ECNRA_FULL 17
#define PROV_EC_ECNRA_SIG 15
#define PROV_FORTEZZA 4
#define PROV_INTEL_SEC 22
#define PROV_MS_EXCHANGE 5
#define PROV_MS_MAIL 5
#define PROV_RNG 21
#define PROV_RSA_AES 24
#define PROV_RSA_FULL 1
#define PROV_RSA_SCHANNEL 12
#define PROV_RSA_SIG 2
#define PROV_SPYRUS_LYNKS 20
#define PROV_SSL 6
#define PROV_STT_ACQ 8
#define PROV_STT_BRND 9
#define PROV_STT_ISS 11
#define PROV_STT_MER 7
#define PROV_STT_ROOT 10
#define PUBLICKEYBLOB 0x6
#define PUBLICKEYBLOBEX 0xA
#define REPORT_NO_PRIVATE_KEY 0x0001
#define REPORT_NOT_ABLE_TO_EXPORT_PRIVATE_KEY 0x0002
#define RSA1024BIT_KEY 0x04000000
#define RSA_CSP_PUBLICKEYBLOB (LPCSTR)
#define SCHANNEL_ENC_KEY 0x00000001
#define SCHANNEL_MAC_KEY 0x00000000
#define SIMPLEBLOB 0x1
#define SYMMETRICWRAPKEYBLOB 0xB
#define TRUST_E_FAIL (-2146762485)
#define USAGE_MATCH_TYPE_AND 0
#define USAGE_MATCH_TYPE_OR 1
#define X509_ALGORITHM_IDENTIFIER (LPCSTR)
#define X509_ALTERNATE_NAME (LPCSTR)
#define X509_ASN_ENCODING 1
#define X509_AUTHORITY_INFO_ACCESS (LPCSTR)
#define X509_AUTHORITY_KEY_ID (LPCSTR)
#define X509_AUTHORITY_KEY_ID2 (LPCSTR)
#define X509_BASIC_CONSTRAINTS (LPCSTR)
#define X509_BASIC_CONSTRAINTS2 (LPCSTR)
#define X509_BIOMETRIC_EXT (LPCSTR)
#define X509_BITS (LPCSTR)
#define X509_CERT (LPCSTR)
#define X509_CERT_CRL_TO_BE_SIGNED (LPCSTR)
#define X509_CERT_PAIR (LPCSTR)
#define X509_CERT_POLICIES (LPCSTR)
#define X509_CERT_REQUEST_TO_BE_SIGNED (LPCSTR)
#define X509_CERT_TO_BE_SIGNED (LPCSTR)
#define X509_CERTIFICATE_TEMPLATE (LPCSTR)
#define X509_CHOICE_OF_TIME (LPCSTR)
#define X509_CRL_DIST_POINTS (LPCSTR)
#define X509_CROSS_CERT_DIST_POINTS (LPCSTR)
#define X509_DSS_PARAMETERS (LPCSTR)
#define X509_DSS_SIGNATURE (LPCSTR)
#define X509_ECC_SIGNATURE (LPCSTR)
#define X509_ENHANCED_KEY_USAGE (LPCSTR)
#define X509_ENUMERATED (LPCSTR)
#define X509_EXTENSIONS (LPCSTR)
#define X509_INTEGER (LPCSTR)
#define X509_ISSUING_DIST_POINT (LPCSTR)
#define X509_KEY_ATTRIBUTES (LPCSTR)
#define X509_KEY_USAGE (LPCSTR)
#define X509_KEY_USAGE_RESTRICTION (LPCSTR)
#define X509_KEYGEN_REQUEST_TO_BE_SIGNED (LPCSTR)
#define X509_LOGOTYPE_EXT (LPCSTR)
#define X509_MULTI_BYTE_INTEGER (LPCSTR)
#define X509_MULTI_BYTE_UINT (LPCSTR)
#define X509_NAME (LPCSTR)
#define X509_NAME_CONSTRAINTS (LPCSTR)
#define X509_NAME_VALUE (LPCSTR)
#define X509_OBJECT_IDENTIFIER (LPCSTR)
#define X509_OCTET_STRING (LPCSTR)
#define X509_POLICY_CONSTRAINTS (LPCSTR)
#define X509_POLICY_MAPPINGS (LPCSTR)
#define X509_PUBLIC_KEY_INFO (LPCSTR)
#define X509_SEQUENCE_OF_ANY (LPCSTR)
#define X509_UNICODE_NAME (LPCSTR)
#define X509_UNICODE_NAME_VALUE (LPCSTR)

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CRYPT_OID_INFO  [struct, macro; shared] */
typedef struct _CRYPT_OID_INFO {
 DWORD cbSize;
 LPCSTR pszOID;
 LPCWSTR pwszName;
 DWORD dwGroupId;
 union {
 DWORD dwValue;
 ALG_ID Algid;
 DWORD dwLength;
 };
 CRYPT_DATA_BLOB ExtraInfo;
} CRYPT_OID_INFO, *PCRYPT_OID_INFO;
typedef const CRYPT_OID_INFO CCRYPT_OID_INFO, *PCCRYPT_OID_INFO;

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ALG_ID  [typedef; ce-only] */
typedef unsigned int ALG_ID;

/* CERT_BASIC_CONSTRAINTS2_INFO  [struct; shared] */
typedef struct _CERT_BASIC_CONSTRAINTS2_INFO {
 BOOL fCA;
 BOOL fPathLenConstraint;
 DWORD dwPathLenConstraint;
} CERT_BASIC_CONSTRAINTS2_INFO, *PCERT_BASIC_CONSTRAINTS2_INFO;

/* CERT_POLICY_ID  [struct; shared] */
typedef struct _CERT_POLICY_ID {
 DWORD cCertPolicyElementId;
 LPSTR* rgpszCertPolicyElementId;
} CERT_POLICY_ID, *PCERT_POLICY_ID;

/* CERT_PRIVATE_KEY_VALIDITY  [struct; shared] */
typedef struct _CERT_PRIVATE_KEY_VALIDITY {
 FILETIME NotBefore;
 FILETIME NotAfter;
} CERT_PRIVATE_KEY_VALIDITY, *PCERT_PRIVATE_KEY_VALIDITY;

/* CERT_SYSTEM_STORE_INFO  [struct; shared] */
typedef struct _CERT_SYSTEM_STORE_INFO {
 DWORD cbSize;
} CERT_SYSTEM_STORE_INFO, *PCERT_SYSTEM_STORE_INFO;

/* CERT_SYSTEM_STORE_RELOCATE_PARA  [struct; shared] */
typedef struct _CERT_SYSTEM_STORE_RELOCATE_PARA {
 union {
 HKEY hKeyBase;
 void* pvBase;
 };
 union {
 void* pvSystemStore;
 LPCSTR pszSystemStore;
 LPCWSTR pwszSystemStore;
 };
} CERT_SYSTEM_STORE_RELOCATE_PARA, *PCERT_SYSTEM_STORE_RELOCATE_PARA;

/* CERT_TRUST_STATUS  [struct; shared] */
typedef struct _CERT_TRUST_STATUS {
 DWORD dwErrorStatus;
 DWORD dwInfoStatus;
} CERT_TRUST_STATUS, *PCERT_TRUST_STATUS;

/* CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA  [struct; shared] */
typedef struct _CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA {
 DWORD cbSize;
 DWORD dwSignerIndex;
 DWORD dwUnauthAttrIndex;
} CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA, *PCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA;

/* CRYPT_BIT_BLOB  [struct; shared] */
typedef struct _CRYPT_BIT_BLOB {
 DWORD cbData;
 BYTE* pbData;
 DWORD cUnusedBits;
} CRYPT_BIT_BLOB, *PCRYPT_BIT_BLOB;

/* CRYPT_KEY_PROV_INFO  [struct; shared] */
typedef struct _CRYPT_KEY_PROV_INFO {
 LPWSTR pwszContainerName;
 LPWSTR pwszProvName;
 DWORD dwProvType;
 DWORD dwFlags;
 DWORD cProvParam;
 PCRYPT_KEY_PROV_PARAM rgProvParam;
 DWORD dwKeySpec;
} CRYPT_KEY_PROV_INFO, *PCRYPT_KEY_PROV_INFO;

/* CRYPT_KEY_PROV_PARAM  [struct; shared] */
typedef struct _CRYPT_KEY_PROV_PARAM {
 DWORD dwParam;
 BYTE* pbData;
 DWORD cbData;
 DWORD dwFlags;
} CRYPT_KEY_PROV_PARAM, *PCRYPT_KEY_PROV_PARAM;

/* CRYPT_OID_FUNC_ENTRY  [struct; shared] */
typedef struct _CRYPT_OID_FUNC_ENTRY {
 LPCSTR pszOID;
 void* pvFuncAddr;
} CRYPT_OID_FUNC_ENTRY, *PCRYPT_OID_FUNC_ENTRY;

/* HCRYPTHASH  [typedef; ce-only] */
typedef unsigned long HCRYPTHASH;

/* HCRYPTKEY  [typedef; ce-only] */
typedef unsigned long HCRYPTKEY;

/* HCRYPTPROV  [typedef; ce-only] */
typedef unsigned long HCRYPTPROV;

/* HMAC_INFO  [struct; shared] */
typedef struct _HMAC_Info {
 ALG_ID HashAlgid;
 BYTE* pbInnerString;
 DWORD cbInnerString;
 BYTE* pbOuterString;
 DWORD cbOuterString;
} HMAC_INFO, *PHMAC_INFO;

/* PROV_ENUMALGS  [struct; shared] */
typedef struct _PROV_ENUMALGS {
 ALG_ID aiAlgid; 
 DWORD dwBitLen; 
 DWORD dwNameLen; 
 WCHAR szName[20]; 
} PROV_ENUMALGS;
typedef PROV_ENUMALGS *PPROV_ENUMALGS, *LPPROV_ENUMALGS;

/* PROV_ENUMALGS_EX  [struct; shared] */
typedef struct _PROV_ENUMALGS_EX {
 ALG_ID aiAlgid; 
 DWORD dwDefaultLen; 
 DWORD dwMinLen; 
 DWORD dwMaxLen; 
 DWORD dwProtocols; 
 DWORD dwNameLen; 
 WCHAR szName[20]; 
 DWORD dwLongNameLen;
 WCHAR szLongName[40]; 
} PROV_ENUMALGS_EX;
typedef PROV_ENUMALGS_EX *PPROV_ENUMALGS_EX, *LPPROV_ENUMALGS_EX;

/* RSAPUBKEY  [struct; shared] */
typedef struct _RSAPUBKEY {
 DWORD magic; 
 DWORD bitlen; 
 DWORD pubexp; 
} RSAPUBKEY;
typedef RSAPUBKEY *PRSAPUBKEY, *LPRSAPUBKEY;

/* VTableProvStruc  [struct; ce-only] */
typedef struct _VTableProvStruc {
 DWORD Version; 
 FARPROC FuncVerifyImage; 
 FARPROC FuncReturnhWnd; 
 DWORD dwProvType; 
 BYTE* pbContextInfo; 
 DWORD cbContextInfo; 
 LPWSTR pszProvName;
} VTableProvStruc, *PVTableProvStruc;
BOOL FuncVerifyImage(LPCSTR lpszImage, BYTE *pSigData);
BOOL FuncReturnhWnd(DWORD *phWnd);

/* CERT_KEY_CONTEXT  [struct; shared] */
typedef struct _CERT_KEY_CONTEXT {
 DWORD cbSize;
 HCRYPTPROV hCryptProv;
 DWORD dwKeySpec;
} CERT_KEY_CONTEXT, *PCERT_KEY_CONTEXT;

/* CERT_KEY_USAGE_RESTRICTION_INFO  [struct; shared] */
typedef struct _CERT_KEY_USAGE_RESTRICTION_INFO {
 DWORD cCertPolicyId;
 PCERT_POLICY_ID rgCertPolicyId;
 CRYPT_BIT_BLOB RestrictedKeyUsage;
} CERT_KEY_USAGE_RESTRICTION_INFO, *PCERT_KEY_USAGE_RESTRICTION_INFO;

/* CMSG_CTRL_DECRYPT_PARA  [struct; shared] */
typedef struct _CMSG_CTRL_DECRYPT_PARA {
 DWORD cbSize;
 HCRYPTPROV hCryptProv;
 DWORD dwKeySpec;
 DWORD dwRecipientIndex;
} CMSG_CTRL_DECRYPT_PARA, *PCMSG_CTRL_DECRYPT_PARA;

/* CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA  [struct; shared] */
typedef struct _CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA {
 DWORD cbSize;
 HCRYPTPROV hCryptProv;
 DWORD dwSignerIndex;
 DWORD dwSignerType;
 void* pvSigner;
} CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA, *PCMSG_CTRL_VERIFY_SIGNATURE_EX_PARA;

/* CERT_SIGNED_CONTENT_INFO  [struct; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   ToBeSigned */
/*   SignatureAlgorithm */
/*   Signature */

/* CMSG_STREAM_INFO  [struct; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   cbContent */
/*   pfnStreamOutput */
/*   pvArg */

/* CRYPT_ENCODE_PARA  [struct; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   cbSize */
/*   pfnAlloc */
/*   pfnFree */

/* SECURITY_INFORMATION  [extra typedef] */
typedef DWORD SECURITY_INFORMATION;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..699 */

/* CryptContextAddRef  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptContextAddRef( 
 HCRYPTPROV hProv,
 DWORD* pdwReserved, 
 DWORD dwFlags
);

/* CryptDuplicateHash  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptDuplicateHash( 
 HCRYPTHASH hHash,
 DWORD* pdwReserved, 
 DWORD dwFlags, 
 HCRYPTHASH* phHash
);

/* CryptDuplicateKey  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptDuplicateHash( 
 HCRYPTKEY hKey,
 DWORD* pdwReserved, 
 DWORD dwFlags, 
 HCRYPTKEY* phKey
);

/* CryptEnumProviders  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib; A/W CryptEnumProvidersA,CryptEnumProvidersW (CE is W-side)] */
BOOL WINAPI CryptEnumProviders( 
 DWORD dwIndex, 
 DWORD* pdwReserved, 
 DWORD dwFlags, 
 DWORD* pdwProvType, 
 LPTSTR pszProvName, 
 DWORD* pcbProvName
);

/* CryptEnumProviderTypes  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib; A/W CryptEnumProviderTypesA,CryptEnumProviderTypesW (CE is W-side)] */
BOOL WINAPI CryptEnumProviderTypes( 
 DWORD dwIndex,
 DWORD* pdwReserved, 
 DWORD dwFlags, 
 DWORD* pdwProvType,
 LPTSTR pszTypeName, 
 DWORD* pcbTypeName
);

/* CryptGetDefaultProvider  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib; A/W CryptGetDefaultProviderA,CryptGetDefaultProviderW (CE is W-side)] */
BOOL WINAPI CryptGetDefaultProvider( 
 DWORD dwProvType,
 DWORD* pdwReserved, 
 DWORD dwFlags, 
 LPTSTR pszProvName,
 DWORD* pcbProvName
);

/* CryptGetProvParam  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptGetProvParam( 
 HCRYPTPROV hProv,
 DWORD dwParam, 
 BYTE* pbData, 
 DWORD* pdwDataLen, 
 DWORD dwFlags
);

/* CryptGetUserKey  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptGetUserKey( 
 HCRYPTPROV hProv,
 DWORD dwKeySpec, 
 HCRYPTKEY* phUserKey
);

/* CryptHashData  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptHashData( 
 HCRYPTHASH hHash, 
 BYTE* pbData,
 DWORD dwDataLen, 
 DWORD dwFlags
);

/* CryptHashSessionKey  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptHashSessionKey( 
 HCRYPTHASH hHash,
 HCRYPTKEY hKey, 
 DWORD dwFlags
);

/* CryptImportKey  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptImportKey( 
 HCRYPTPROV hProv, 
 BYTE* pbData, 
 DWORD dwDataLen, 
 HCRYPTKEY hPubKey, 
 DWORD dwFlags, 
 HCRYPTKEY* phKey
);

/* CryptReleaseContext  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptReleaseContext( 
 HCRYPTPROV hProv,
 DWORD dwFlags
);

/* CryptSetHashParam  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptSetHashParam( 
 HCRYPTHASH hHash,
 DWORD dwParam, 
 BYTE* pbData, 
 DWORD dwFlags
);

/* CryptSetKeyParam  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib] */
BOOL WINAPI CryptSetKeyParam( 
 HCRYPTKEY hKey, 
 DWORD dwParam, 
 BYTE* pbData, 
 DWORD dwFlags
);

/* CryptSetProviderEx  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib; A/W CryptSetProviderExA,CryptSetProviderExW (CE is W-side)] */
BOOL WINAPI CryptSetProviderEx( 
 LPCTSTR pszProvName, 
 DWORD dwProvType, 
 DWORD* pdwReserved, 
 DWORD dwFlags
);

/* CryptSignHash  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib; A/W CryptSignHashA,CryptSignHashW (CE is W-side)] */
BOOL WINAPI CryptSignHash( 
 HCRYPTHASH hHash, 
 DWORD dwKeySpec, 
 LPCTSTR sDescription, 
 DWORD dwFlags,
 BYTE* pbSignature, 
 DWORD* pdwSigLen
);

/* CryptVerifySignature  [function; shared; CE 2.11..2.12, 3.0..699; Coredll.lib, coredll.lib, Cryptapi.lib, cryptapi.lib; A/W CryptVerifySignatureA,CryptVerifySignatureW (CE is W-side)] */
BOOL WINAPI CryptVerifySignature( 
 HCRYPTHASH hHash,
 BYTE* pbSignature, 
 DWORD dwSigLen, 
 HCRYPTKEY hPubKey,
 LPCTSTR sDescription, 
 DWORD dwFlags
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x700)) /* CE 3.0..699 */

/* CertAlgIdToOID  [function; shared; CE 3.0..699; Crypt32.lib, crypt32.lib] */
LPCSTR WINAPI CertAlgIdToOID(
 DWORD dwAlgId
);

/* CertifyModule  [function; ce-only; CE 3.0..699; Loadauth.lib, loadauth.lib; heuristic-prefix] */
BOOL CertifyModule(
 PBYTE pbBlock,
 DWORD cbBlock 
);

/* CertifyModuleFinal  [function; ce-only; CE 3.0..699; Loadauth.lib, loadauth.lib; heuristic-prefix] */
BOOL CertifyModuleFinal(
 PBYTE* ppbSignData,
 PDWORD pcbSignData 
);

/* CertifyModuleInit  [function; ce-only; CE 3.0..699; Loadauth.lib, loadauth.lib; heuristic-prefix] */
BOOL CertifyModuleInit (void);

/* CertOIDToAlgId  [function; shared; CE 3.0..699; Crypt32.lib, crypt32.lib] */
DWORD WINAPI CertOIDToAlgId(
 LPCSTR pszObjId
);

/* CertStrToName  [function; shared; CE 3.0..699; Crypt32.lib, crypt32.lib; A/W CertStrToNameA,CertStrToNameW (CE is W-side)] */
BOOL WINAPI CertStrToName(
 DWORD dwCertEncodingType,
 LPCTSTR pszX500,
 DWORD dwStrType,
 void* pvReserved,
 BYTE* pbEncoded,
 DWORD* pcbEncoded,
 LPCTSTR* ppszError
);

/* CryptEncodeObjectEx  [function; shared; CE 3.0..699; Crypt32.lib, crypt32.lib] */
BOOL WINAPI CryptEncodeObjectEx(
 DWORD dwCertEncodingType, 
 LPCSTR lpszStructType, 
 const void* pvStructInfo, 
 DWORD dwFlags, 
 PCRYPT_ENCODE_PARA pEncodePara, 
 void* pvEncoded, 
 DWORD* pcbEncoded
);

/* CryptHashCertificate  [function; shared; CE 3.0..699; Crypt32.lib, crypt32.lib] */
BOOL WINAPI CryptHashCertificate(
 HCRYPTPROV hCryptProv,
 ALG_ID Algid,
 DWORD dwFlags,
 const BYTE* pbEncoded,
 DWORD cbEncoded,
 BYTE* pbComputedHash,
 DWORD* pcbComputedHash
);

/* CryptHashToBeSigned  [function; shared; CE 3.0..699; Crypt32.lib, crypt32.lib] */
BOOL WINAPI CryptHashToBeSigned(
 HCRYPTPROV hCryptProv,
 DWORD dwCertEncodingType,
 const BYTE* pbEncoded,
 DWORD cbEncoded,
 BYTE* pbComputedHash,
 DWORD* pcbComputedHash
);

/* CryptInstallOIDFunctionAddress  [function; shared; CE 3.0..699; Crypt32.lib, crypt32.lib] */
BOOL WINAPI CryptInstallOIDFunctionAddress(
 HMODULE hModule,
 DWORD dwEncodingType,
 LPCSTR pszFuncName,
 DWORD cFuncEntry,
 CRYPT_OID_FUNC_ENTRY rgFuncEntry[ ],
 DWORD dwFlags
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* CPAcquireContext  [function; ce-only; CE 4.0..699] */
BOOL CPAcquireContext(
 HCRYPTPROV* phProv,
 WCHAR* pszContainer,
 DWORD dwFlags,
 PVTableProvStruc pVTable 
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CryptFindLocalizedName  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
LPCWSTR WINAPI CryptFindLocalizedName(
 LPCWSTR pwszCryptName
);

/* CryptMsgCalculateEncodedLength  [function; shared; CE 5.0..699; Coredll.lib, crypt32.lib] */
DWORD WINAPI CryptMsgCalculateEncodedLength(
 DWORD dwMsgEncodingType,
 DWORD dwFlags,
 DWORD dwMsgType,
 const void* pvMsgEncodeInfo,
 LPSTR pszInnerContentObjID,
 DWORD cbData
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL CRYPTFUNCCryptDestroyHash( HCRYPTHASHhHash);
BOOL CRYPTFUNCCryptExportKey(HCRYPTKEY hKey,HCRYPTKEY hExpKey,DWORD dwBlobType,DWORD dwFlags,BYTE* pbData,DWORD* pdwbDataLen);
VOID WINAPI CertEnumStoreLocationCallback( LPCWSTR pvszStoreLoocations DWORD dwFlags, void *pvReserved, void *pvArg );
VOID WINAPI CertEnumSystemStoreCallback( const void *pvSystemStore, DWORD dwFlags, PCERT_SYSTEM_STORE_INFO pStoreInfo, void *pvReserved, void *pvArg );
VOID WINAPI CmsgStreamOutputCallback( const void *pvArg, //in BYTE *pbData, //in DWORD cbData, //in BOOL fFinal //in );

#endif /* _WINCRYPT_ */
