/* msacm.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 10 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MSACM_
#define _MSACM_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ACM_FORMATSUGGESTF_WFORMATTAG 0x00010000
#define ACM_STREAMOPENF_NONREALTIME 4
#define ACM_STREAMSIZEF_DESTINATION 1
#define ACMDRIVERDETAILS_COPYRIGHT_CHARS 80
#define ACMDRIVERDETAILS_FEATURES_CHARS 256
#define ACMDRIVERDETAILS_LICENSING_CHARS 128
#define ACMDRIVERDETAILS_LONGNAME_CHARS 128
#define ACMDRIVERDETAILS_SHORTNAME_CHARS 32
#define ACMFORMATDETAILS_FORMAT_CHARS 256
#define ACMFORMATTAGDETAILS_FORMATTAG_CHARS 256

#endif /* _MSACM_ */
