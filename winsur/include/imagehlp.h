/* imagehlp.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 49 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _IMAGEHLP_
#define _IMAGEHLP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define API_VERSION_NUMBER 7
#define BIND_ALL_IMAGES 0x00000004
#define BIND_CACHE_IMPORT_DLLS 0x00000008
#define BIND_NO_BOUND_IMPORTS 0x00000001
#define BIND_NO_UPDATE 0x00000002
#define CBA_DEFERRED_SYMBOL_LOAD_COMPLETE 2
#define CBA_DEFERRED_SYMBOL_LOAD_FAILURE 3
#define CBA_DEFERRED_SYMBOL_LOAD_START 1
#define CBA_DUPLICATE_SYMBOL 5
#define CBA_SYMBOLS_UNLOADED 4
#define CERT_PE_IMAGE_DIGEST_ALL_IMPORT_INFO 4
#define CERT_PE_IMAGE_DIGEST_DEBUG_INFO 1
#define CERT_PE_IMAGE_DIGEST_NON_PE_INFO 8
#define CERT_PE_IMAGE_DIGEST_RESOURCES 2
#define CERT_SECTION_TYPE_ANY 255
#define CHECKSUM_MAP_FAILURE 2
#define CHECKSUM_MAPVIEW_FAILURE 3
#define CHECKSUM_OPEN_FAILURE 1
#define CHECKSUM_SUCCESS 0
#define CHECKSUM_UNICODE_FAILURE 4
#define IMAGE_SEPARATION 65536
#define SPLITSYM_EXTRACT_ALL 2
#define SPLITSYM_REMOVE_PRIVATE 1
#define SPLITSYM_SYMBOLPATH_IS_SRC 4
#define SYMF_OMAP_GENERATED 1
#define SYMF_OMAP_MODIFIED 2
#define SYMOPT_CASE_INSENSITIVE 1
#define SYMOPT_DEFERRED_LOADS 4
#define SYMOPT_LOAD_LINES 16
#define SYMOPT_NO_CPP 8
#define SYMOPT_OMAP_FIND_NEAREST 32
#define SYMOPT_UNDNAME 2
#define UNDNAME_32_BIT_DECODE 2048
#define UNDNAME_COMPLETE 0
#define UNDNAME_NAME_ONLY 4096
#define UNDNAME_NO_ACCESS_SPECIFIERS 128
#define UNDNAME_NO_ALLOCATION_LANGUAGE 16
#define UNDNAME_NO_ALLOCATION_MODEL 8
#define UNDNAME_NO_ARGUMENTS 8192
#define UNDNAME_NO_CV_THISTYPE 64
#define UNDNAME_NO_FUNCTION_RETURNS 4
#define UNDNAME_NO_LEADING_UNDERSCORES 1
#define UNDNAME_NO_MEMBER_TYPE 512
#define UNDNAME_NO_MS_KEYWORDS 2
#define UNDNAME_NO_MS_THISTYPE 32
#define UNDNAME_NO_RETURN_UDT_MODEL 1024
#define UNDNAME_NO_SPECIAL_SYMS 16384
#define UNDNAME_NO_THISTYPE 96
#define UNDNAME_NO_THROW_SIGNATURES 256

#endif /* _IMAGEHLP_ */
