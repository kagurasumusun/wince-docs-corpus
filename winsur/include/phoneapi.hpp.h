/* phoneapi.hpp -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 5 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PHONEAPI_HPP_
#define _PHONEAPI_HPP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define MPCF_DEFAULT 0x00000000

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* PH_MAKEPHONECALL_PARAMETERS  [struct; ce-only; PhCommon.dll] */
typedef struct _PH_MAKEPHONECALL_PARAMETERS{
 DWORD StructSize; // Struct size in bytes
 DWORD Flags; // Flags
 WCHAR DestAddress[MAX_PATH]; 
 WCHAR ApplicationName[MAX_PATH]; 
 WCHAR CalledParty[MAX_PATH]; 
 WCHAR Comment[MAX_PATH]; 
} PH_MAKEPHONECALL_PARAMETERS;
typedef PH_MAKEPHONECALL_PARAMETERS *PPH_MAKEPHONECALL_PARAMETERS, *LPPH_MAKEPHONECALL_PARAMETERS;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* PHMakePhoneCall  [function; ce-only; CE 6.0..699; PhCommon.dll] */
HRESULT PHMakePhoneCall(
 const PH_MAKEPHONECALL_PARAMETERS* pParameters
 );

/* PHOnHookDialing  [function; ce-only; CE 6.0..699; PhCommon.dll] */
HRESULT PHOnHookDialing(
 const WCHAR CurrentChar
);

/* PHProcessProvisionXML  [function; ce-only; CE 6.0..699; PhCommon.dll] */
HRESULT PHProcessProvisionXML(
const WCHAR* pInputBuffer,
WCHAR** ppOutputBuffer
);

/* PHValidateProvisionXML  [function; ce-only; CE 6.0..699; PhCommon.dll] */
HRESULT PHValidateProvisionXML(
const WCHAR* pInputBuffer
);
#endif /* _WIN32_WCE */

#endif /* _PHONEAPI_HPP_ */
