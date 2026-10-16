/* Ddgpe.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 2 constants, 5 declarations, 1 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _DDGPE_
#define _DDGPE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ddgpePixelFormat_1bpp 0
#define ddgpePixelFormat_CustomFormat 0x1000

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* DDGPEStandardHeader  [macro; ce-only; Ddgpe.lib] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DDGPEDriverData  [struct; ce-only; Ddgpe.lib] */
typedef struct DDGPEDriverData {
 DDGPEStandardHeader;
 DWORD dwDriverFlag
} DDGPEDriverData;
typedef DDGPEDriverData *PDDGPEDriverData, *LPDDGPEDriverData;

/* EDDGPEPixelFormat  [enum; ce-only; Ddgpe.lib] */
typedef enum EDDGPEPixelFormat{
 ddgpePixelFormat_1bpp = 0,
 ddgpePixelFormat_2bpp, 
 ddgpePixelFormat_4bpp, 
 ddgpePixelFormat_8bpp, 
 ddgpePixelFormat_565, 
 ddgpePixelFormat_5551, 
 ddgpePixelFormat_4444, 
 ddgpePixelFormat_5550, 
 ddgpePixelFormat_8880, 
 ddgpePixelFormat_8888, 
 ddgpePixelFormat_YUYV422, 
 ddgpePixelFormat_UYVY422,
 ddgpePixelFormat_YV12,
 // some generic types
 // Use dwPixelFormatData in conjunction with this info
 ddgpePixelFormat_15bppGeneric, 
 ddgpePixelFormat_16bppGeneric, 
 ddgpePixelFormat_24bppGeneric, 
 ddgpePixelFormat_32bppGeneric, 
 ddgpePixelFormat_UnknownFormat,
 // you can assign custom formats starting with this value
 ddgpePixelFormat_CustomFormat = 0x1000
};

/* ddgpePixelFormat  [extra struct] */
#define DDGPEALLOCSURFACEDATA_VERSION0(0)
#define DDGPEALLOCSURFACEDATA_CURRENTVERSION \
(DDGPEBLTPARMS_VERSION0)
struct DDGPEAllocSurfaceData
{
  DDGPEStandardHeader;
  DWORD dwCreateFlags;
  int nWidth;
  int nHeight;
  int nStride;
  int nSurfaceFlags;
  unsigned char *pBits;
  EGPEFormat gpeFormat;
  EDDGPEPixelFormat *ddgpePixelFormat;
};

/* x1000  [extra enum] */
enum EDDGPEPixelFormat
{
  ddgpePixelFormat_1bpp = 0,
  ddgpePixelFormat_2bpp,
  ddgpePixelFormat_4bpp,
  ddgpePixelFormat_8bpp,
  ddgpePixelFormat_565,
  ddgpePixelFormat_5551,
  ddgpePixelFormat_4444,
  ddgpePixelFormat_5550,
  ddgpePixelFormat_8880,
  ddgpePixelFormat_8888,
  ddgpePixelFormat_YUYV422,
  ddgpePixelFormat_UYVY422,
  ddgpePixelFormat_15bppGeneric,
  ddgpePixelFormat_16bppGeneric,
  ddgpePixelFormat_24bppGeneric,
  ddgpePixelFormat_32bppGeneric,
  ddgpePixelFormat_UnknownFormat,
  ddgpePixelFormat_CustomFormat = 0x1000
};

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void SetOverlay();
void SetRotation( int width, int height, int iRotate );
int SurfaceSize();

#endif /* _DDGPE_ */
