/* verrsrc.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 42 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _VERRSRC_
#define _VERRSRC_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define VFT2_DRV_COMM 0x0000000AL
#define VFT2_DRV_DISPLAY 0x00000004L
#define VFT2_DRV_INSTALLABLE 0x00000008L
#define VFT2_DRV_KEYBOARD 0x00000002L
#define VFT2_DRV_LANGUAGE 0x00000003L
#define VFT2_DRV_MOUSE 0x00000005L
#define VFT2_DRV_NETWORK 0x00000006L
#define VFT2_DRV_PRINTER 0x00000001L
#define VFT2_DRV_SOUND 0x00000009L
#define VFT2_DRV_SYSTEM 0x00000007L
#define VFT2_DRV_VERSIONED_PRINTER 0x0000000CL
#define VFT2_FONT_RASTER 0x00000001L
#define VFT2_FONT_TRUETYPE 0x00000003L
#define VFT2_FONT_VECTOR 0x00000002L
#define VFT2_UNKNOWN 0x00000000L
#define VFT_APP 0x00000001L
#define VFT_DLL 0x00000002L
#define VFT_DRV 0x00000003L
#define VFT_FONT 0x00000004L
#define VFT_STATIC_LIB 0x00000007L
#define VFT_UNKNOWN 0x00000000L
#define VFT_VXD 0x00000005L
#define VOS__PM16 0x00000002L
#define VOS__PM32 0x00000003L
#define VOS__WINDOWS16 0x00000001L
#define VOS__WINDOWS32 0x00000004L
#define VOS_DOS 0x00010000L
#define VOS_DOS_WINDOWS16 0x00010001L
#define VOS_DOS_WINDOWS32 0x00010004L
#define VOS_NT 0x00040000L
#define VOS_NT_WINDOWS32 0x00040004L
#define VOS_OS216 0x00020000L
#define VOS_OS216_PM16 0x00020002L
#define VOS_OS232 0x00030000L
#define VOS_OS232_PM32 0x00030003L
#define VOS_UNKNOWN 0x00000000L
#define VS_FF_DEBUG 0x00000001L
#define VS_FF_INFOINFERRED 0x00000010L
#define VS_FF_PATCHED 0x00000004L
#define VS_FF_PRERELEASE 0x00000002L
#define VS_FF_PRIVATEBUILD 0x00000008L
#define VS_FF_SPECIALBUILD 0x00000020L

#endif /* _VERRSRC_ */
