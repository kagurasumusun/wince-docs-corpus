/* winver.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 33 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINVER_
#define _WINVER_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define VFF_BUFFTOOSMALL 4
#define VFF_CURNEDEST 1
#define VFF_FILEINUSE 2
#define VFFF_ISSHAREDFILE 1
#define VFT2_DRV_INPUTMETHOD 11
#define VIF_ACCESSVIOLATION 512
#define VIF_BUFFTOOSMALL 0x40000
#define VIF_CANNOTCREATE 2048
#define VIF_CANNOTDELETE 4096
#define VIF_CANNOTDELETECUR 16384
#define VIF_CANNOTREADDST 0x20000
#define VIF_CANNOTREADSRC 65536
#define VIF_CANNOTRENAME 8192
#define VIF_DIFFCODEPG 16
#define VIF_DIFFLANG 8
#define VIF_DIFFTYPE 32
#define VIF_FILEINUSE 128
#define VIF_MISMATCH 2
#define VIF_OUTOFMEMORY 32768
#define VIF_OUTOFSPACE 256
#define VIF_SHARINGVIOLATION 1024
#define VIF_SRCOLD 4
#define VIF_TEMPFILE 1
#define VIF_WRITEPROT 64
#define VIFF_DONTDELETEOLD 2
#define VIFF_FORCEINSTALL 1
#define VOS__BASE 0
#define VS_FFI_FILEFLAGSMASK 0x3F
#define VS_FFI_SIGNATURE 0xFEEF04BD
#define VS_FFI_STRUCVERSION 0x10000
#define VS_FILE_INFO RT_VERSION
#define VS_USER_DEFINED 100
#define VS_VERSION_INFO 1

#endif /* _WINVER_ */
