/* BaseTsd.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 10 constants, 15 declarations, 4 outlines, 21 base types, 0 extra macros, 0 extra decls
 */
#ifndef _BASETSD_
#define _BASETSD_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ADDRESS_TAG_BIT 0x40000000000UI64
#define MAXHALF_PTR ((HALF_PTR)(MAXUHALF_PTR
#define MAXINT_PTR ((INT_PTR)(MAXUINT_PTR
#define MAXLONG_PTR ((LONG_PTR)(MAXULONG_PTR
#define MAXUHALF_PTR ((UHALF_PTR)~0)
#define MAXUINT_PTR (~((UINT_PTR)0))
#define MAXULONG_PTR (~((ULONG_PTR)0))
#define MINHALF_PTR (~MAXHALF_PTR)
#define MININT_PTR (~MAXINT_PTR)
#define MINLONG_PTR (~MAXLONG_PTR)

/* ==================================================================
 * base types -- fundamental Windows type definitions
 * CE-specific types are marked; verify sizes for your platform
 * ================================================================ */

/* DWORD32
 * source: win32/common/windows-data-types.md */
typedef unsigned int DWORD32;

/* DWORDLONG
 * source: win32/common/windows-data-types.md */
typedef unsigned __int64 DWORDLONG;

/* HACCEL
 * source: win32/common/windows-data-types.md */
typedef HANDLE HACCEL;

/* INT16
 * source: win32/common/windows-data-types.md */
typedef signed short INT16;

/* INT32
 * source: win32/common/windows-data-types.md */
typedef signed int INT32;

/* INT8
 * source: win32/common/windows-data-types.md */
typedef signed char INT8;

/* INT_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef long INT_PTR;

/* LONG32
 * source: win32/common/windows-data-types.md */
typedef signed int LONG32;

/* LONGLONG
 * source: win32/common/windows-data-types.md */
typedef __int64 LONGLONG;

/* LONG_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef long LONG_PTR;

/* SHORT
 * source: win32/common/windows-data-types.md */
typedef short SHORT;

/* UCHAR
 * source: win32/common/windows-data-types.md */
typedef unsigned char UCHAR;

/* UINT16
 * source: win32/common/windows-data-types.md */
typedef unsigned  short UINT16;

/* UINT32
 * source: win32/common/windows-data-types.md */
typedef unsigned int UINT32;

/* UINT8
 * source: win32/common/windows-data-types.md */
typedef unsigned  char UINT8;

/* UINT_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef unsigned long UINT_PTR;

/* ULONG32
 * source: win32/common/windows-data-types.md */
typedef unsigned int ULONG32;

/* ULONGLONG
 * source: win32/common/windows-data-types.md */
typedef unsigned __int64 ULONGLONG;

/* ULONG_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef unsigned long ULONG_PTR;

/* DWORD_PTR
 * CE is 32-bit: pointer-sized integer
 * source: win32/common/windows-data-types.md */
typedef unsigned long DWORD_PTR;

/* SIZE_T [CE-SPECIFIC]
 * Size type for memory operations
 * Pointer-sized (32-bit on 32-bit CE platforms)
 * source: win32/common/windows-data-types.md */
typedef ULONG_PTR SIZE_T;

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* POINTER_32  [typedef, macro; shared; entity-headers] */

/* POINTER_64  [typedef, macro; shared; entity-headers] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DWORD64  [typedef; shared; entity-headers; win32-reference] */
typedef unsigned __int64 DWORD64;

/* INT64  [typedef; shared; entity-headers; win32-reference] */
typedef signed __int64 INT64;

/* LONG64  [typedef; shared; entity-headers; win32-reference] */
typedef __int64 LONG64;

/* UINT64  [typedef; shared; entity-headers; win32-reference] */
typedef unsigned __int64 UINT64;

/* ULONG64  [typedef; shared; entity-headers; win32-reference] */
typedef unsigned __int64 ULONG64;

#endif /* _BASETSD_ */
