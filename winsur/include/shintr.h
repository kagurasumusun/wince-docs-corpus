/* shintr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _SHINTR_
#define _SHINTR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* __fmac  [function; ce-only; CE 4.0..699] */
Float __fmac( 
 float Arg1, 
 float Arg1, 
 float Arg1 
);

/* __movca  [function; ce-only; CE 4.0..699] */
void __movca( 
 unsigned long value, 
 unsigned long* addr 
);

/* _Convolve  [function; ce-only; CE 4.0..699] */
Float _Convolve(
 int nelement,
 float* pstart,
 float* pend,
 float* pdata,
 float* pfilter
);

/* _Dot3dVW0  [function; ce-only; CE 4.0..699] */
float _Dot3dVW0( 
 float* vector1, 
 float* vector2 
);

/* _Dot3dVW1  [function; ce-only; CE 4.0..699] */
float _Dot3dVW1( 
 float* vector1, 
 float* vector2 
);

/* _Dot4dV  [function; ce-only; CE 4.0..699] */
float _Dot4dV( 
 float* vector1, 
 float* vector2 
);

/* _XDMultMatrix  [function; ce-only; CE 4.0..699] */
void _XDMultMatrix( 
 float* matrix 
);
#endif /* _WIN32_WCE */

#endif /* _SHINTR_ */
