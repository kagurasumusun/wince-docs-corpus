/* Atapi2.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ATAPI2_
#define _ATAPI2_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* INQUIRY_DATA  [struct; ce-only] */
typedef struct _INQUIRY_DATA {
 UCHAR inqDevType; 
 UCHAR inqRMB; 
 UCHAR inqVersion; 
 UCHAR inqAtapiVersion; 
 UCHAR inqLength; 
 UCHAR inqReserved[3]; 
 UCHAR inqVendor[8]; 
 UCHAR inqProdID[16]; 
 UCHAR inqRev[4]; 
 UCHAR inqReserved2[60]; 
} INQUIRY_DATA, *PINQUIRY_DATA;

#endif /* _ATAPI2_ */
