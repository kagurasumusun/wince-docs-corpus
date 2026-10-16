/* Cmnintrin.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 33 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _CMNINTRIN_
#define _CMNINTRIN_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x500)) /* CE 4.0..499 */

/* _debugbreak  [function; ce-only; CE 4.0..499] */
void __cdecl __debugbreak(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x600)) /* CE 4.0..599 */

/* _byteswap_uint64  [function; ce-only; CE 4.0..599] */
unsigned __int64 __cdecl _byteswap_uint64( unsigned __int64 arg1);

/* _byteswap_ulong  [function; ce-only; CE 4.0..599] */
unsigned long __cdecl _byteswap_ulong( unsigned long arg1);

/* _byteswap_ushort  [function; ce-only; CE 4.0..599] */
unsigned short __cdecl _byteswap_ushort( unsigned short arg1);

/* _CacheRelease  [function; ce-only; CE 4.0..599] */
void __cdecl __CacheRelease( void *);

/* _CacheWriteBack  [function; ce-only; CE 4.0..599] */
void __cdecl __CacheWriteback( void *);

/* _trap  [function; ce-only; CE 4.0..599] */
int __cdecl __trap(arg1,);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* _CopyDoubleFromInt64  [function; ce-only; CE 4.0..699] */
double _CopyInt64FromDouble(
 __int64 arg1
);

/* _CopyFloatFromInt32  [function; ce-only; CE 4.0..699] */
float _CopyFloatFromInt32(
 ___int32 arg1
);

/* _CopyInt32FromFloat  [function; ce-only; CE 4.0..699] */
__int32 _CopyInt32FromFloat(
 float arg1
);

/* _CopyInt64FromDouble  [function; ce-only; CE 4.0..699] */
__int64 _CopyInt64FromDouble(
 double arg1
);

/* _CountLeadingOnes  [function; ce-only; CE 4.0..699] */
unsigned __cdecl _CountLeadingOnes(
 long arg1
);
unsigned __cdecl _CountLeadingOnes64(
 __int64 arg1
);

/* _CountLeadingOnes64  [function; ce-only; CE 4.0..699] */
unsigned __cdecl _CountLeadingOnes(
 long arg1
);
unsigned __cdecl _CountLeadingOnes64(
 __int64 arg1
);

/* _CountLeadingSigns  [function; ce-only; CE 4.0..699] */
unsigned __cdecl _CountLeadingSigns(
 long arg1
);
unsigned __cdecl _CountLeadingSigns64(
 __int64 arg1
);

/* _CountLeadingSigns64  [function; ce-only; CE 4.0..699] */
unsigned __cdecl _CountLeadingSigns(
 long arg1
);
unsigned __cdecl _CountLeadingSigns64(
 __int64 arg1
);

/* _CountLeadingZeros  [function; ce-only; CE 4.0..699] */
unsigned __cdecl _CountLeadingZeros(
 long arg1
);
unsigned __cdecl _CountLeadingZeros64(
 __int64 arg1
);

/* _CountLeadingZeros64  [function; ce-only; CE 4.0..699] */
unsigned __cdecl _CountLeadingZeros(
 long arg1
);
unsigned __cdecl _CountLeadingZeros64(
 __int64 arg1
);

/* _CountOneBits  [function; ce-only; CE 4.0..699] */
unsigned __cdecl _CountOneBits(
 long arg1
);
unsigned __cdecl _CountOneBits64(
 __int64 arg1
);

/* _CountOneBits64  [function; ce-only; CE 4.0..699] */
unsigned __cdecl _CountOneBits(
 long arg1
);
unsigned __cdecl _CountOneBits64(
 __int64 arg1
);

/* _ICacheRefresh  [function; ce-only; CE 4.0..699] */
void __cdecl __ICacheRefresh(
 void *
);

/* _isunordered  [function; ce-only; CE 4.0..699] */
int __cdecl _isunordered(
 double arg1,
 double arg2
);
int __cdecl _isunorderedf(
 float arg1,
 float arg2
);

/* _isunorderedf  [function; ce-only; CE 4.0..699] */
int __cdecl _isunordered(
 double arg1,
 double arg2
);
int __cdecl _isunorderedf(
 float arg1,
 float arg2
);

/* _MulHigh  [function; ce-only; CE 4.0..699] */
long __cdecl _MulHigh(
 long arg1,
 long arg2
);
unsigned long __cdecl _MulUnsignedHigh(
 unsigned long arg1,
 unsigned long arg2
);

/* _MulUnsignedHigh  [function; ce-only; CE 4.0..699] */
long __cdecl _MulHigh(
 long arg1,
 long arg2
);
unsigned long __cdecl _MulUnsignedHigh(
 unsigned long arg1,
 unsigned long arg2
);

/* _prefetch  [function; ce-only; CE 4.0..699] */
void __cdecl __prefetch(
 void *
);

/* _ReadWriteBarrier  [function; ce-only; CE 4.0..699] */
void __cdecl _ReadWriteBarrier(void);
void __cdecl _WriteBarrier(void);
void __cdecl _ReadBarrier(void);

/* _ReturnAddress  [function; ce-only; CE 4.0..699] */
void _ReturnAddress(void);

/* _WriteBarrier  [function; ce-only; CE 4.0..699] */
void __cdecl _ReadWriteBarrier(void);
void __cdecl _WriteBarrier(void);
void __cdecl _ReadBarrier(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* _ReadBarrier  [function; ce-only; CE 6.0..699; entity-headers] */
void __cdecl _ReadWriteBarrier(void);
void __cdecl _WriteBarrier(void);
void __cdecl _ReadBarrier(void);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void __cdecl __CacheWriteback( void *);
void __cdecl __ICacheRefresh( void *);

#endif /* _CMNINTRIN_ */
