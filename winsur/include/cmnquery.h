/* cmnquery.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 14 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CMNQUERY_
#define _CMNQUERY_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CQFF_ISOPTIONAL 0x00000002
#define CQFF_NOGLOBALPAGES 0x00000001
#define OQWF_DEFAULTFORM 0x00000002
#define OQWF_HIDEMENUS 0x00000400
#define OQWF_HIDESEARCHUI 0x00000800
#define OQWF_ISSUEONOPEN 0x00000040
#define OQWF_LOADQUERY 0x00000008
#define OQWF_OKCANCEL 0x00000001
#define OQWF_PARAMISPROPERTYBAG 0x80000000
#define OQWF_REMOVEFORMS 0x00000020
#define OQWF_REMOVESCOPES 0x00000010
#define OQWF_SAVEQUERYONOK 0x00000200
#define OQWF_SHOWOPTIONAL 0x00000080
#define OQWF_SINGLESELECT 0x00000004

#endif /* _CMNQUERY_ */
