/* Mipsintr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 199 declarations, 0 outlines, 0 base types, 0 extra macros, 5 extra decls
 */
#ifndef _MIPSINTR_
#define _MIPSINTR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x500)) /* CE 4.0..499 */

/* _abs_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _abs_ps(
 arg1
);

/* _abs_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _abs_sl(
 arg1
);

/* _abs_su  [function; ce-only; CE 4.0..499] */
float __cdecl _abs_su(
 arg1
);

/* _abs_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _abs_vl(
 arg1
);

/* _abs_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _abs_vu(
 arg1
);

/* _add_ob  [function; ce-only; CE 4.0..499] */
double _add_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _add_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _add_ps(
 arg1,
 arg2
);

/* _add_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _add_sl(
 arg1,
 arg2
);

/* _add_su  [function; ce-only; CE 4.0..499] */
float __cdecl _add_su(
 arg1,
 arg2
);

/* _add_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _add_vl(
 arg1,
 arg2
);

/* _add_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _add_vu(
 arg1,
 arg2
);

/* _alni_ob  [function; ce-only; CE 4.0..499] */
double _alni_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _and_ob  [function; ce-only; CE 4.0..499] */
double _and_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _c_eq_ob  [function; ce-only; CE 4.0..499] */
void _c_eq_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _c_eq_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_eq_sl(
 int,
 double1,
 double2
);

/* _c_eq_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_eq_sl(
 int,
 double,
 float
);

/* _c_eq_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_eq_su(
 int,
 double,
 float
);

/* _c_eq_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_eq_vl(
 int,
 double1,
 double2
);

/* _c_eq_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_eq_vu(
 int,
 double1,
 double2
);

/* _c_f_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_f_sl(
 int,
 double1,
 double2
);

/* _c_f_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_f_sl(
 int,
 double,
 float
);

/* _c_f_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_f_su(
 int,
 double,
 float
);

/* _c_f_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_f_vl(
 int,
 double1,
 double2
);

/* _c_f_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_f_vu(
 int,
 double1,
 double2
);

/* _c_le_ob  [function; ce-only; CE 4.0..499] */
void _c_le_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _c_le_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_le_ps(
 int,
 double1,
 double2
);

/* _c_le_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_le_sl(
 int,
 double,
 float
);

/* _c_le_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_le_su(
 int,
 double,
 float
);

/* _c_le_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_le_vl(
 int,
 double1,
 double2
);

/* _c_le_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_le_vu(
 int,
 double1,
 double2
);

/* _c_lt_ob  [function; ce-only; CE 4.0..499] */
void _c_lt_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _c_lt_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_lt_ps(
 int,
 double1,
 double2
);

/* _c_lt_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_lt_sl(
 int,
 double,
 float
);

/* _c_lt_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_lt_su(
 int,
 double,
 float
);

/* _c_lt_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_lt_vl(
 int,
 double1,
 double2
);

/* _c_lt_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_lt_vu(
 int,
 double1,
 double2
);

/* _c_nge_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_nge_ps(
 int,
 double1,
 double2
);

/* _c_nge_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_nge_sl(
 int,
 double,
 float
);

/* _c_nge_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_nge_su(
 int,
 double,
 float
);

/* _c_nge_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_nge_vl(
 int,
 double1,
 double2
);

/* _c_nge_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_nge_vu(
 int,
 double1,
 double2
);

/* _c_ngl_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngl_ps(
 int,
 double1,
 double2
);

/* _c_ngl_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngl_sl(
 int,
 double,
 float
);

/* _c_ngl_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngl_su(
 int,
 double,
 float
);

/* _c_ngl_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngl_vl(
 int,
 double1,
 double2
);

/* _c_ngl_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngl_vu(
 int,
 double1,
 double2
);

/* _c_ngle_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngle_ps(
 int,
 double1,
 double2
);

/* _c_ngle_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngle_sl(
 int,
 double,
 float
);

/* _c_ngle_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngle_su(
 int,
 double,
 float
);

/* _c_ngle_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngle_vl(
 int,
 double1,
 double2
);

/* _c_ngle_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngle_vu(
 int,
 double1,
 double2
);

/* _c_ngt_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngt_ps(
 int,
 double1,
 double2
);

/* _c_ngt_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngt_sl(
 int,
 double,
 float
);

/* _c_ngt_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngt_su(
 int,
 double,
 float
);

/* _c_ngt_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngt_vl(
 int,
 double1,
 double2
);

/* _c_ngt_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ngt_vu(
 int,
 double1,
 double2
);

/* _c_ole_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ole_ps(
 int,
 double1,
 double2
);

/* _c_ole_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ole_sl(
 int,
 double,
 float
);

/* _c_ole_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ole_su(
 int,
 double,
 float
);

/* _c_ole_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ole_vl(
 int,
 double1,
 double2
);

/* _c_ole_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ole_vu(
 int,
 double1,
 double2
);

/* _c_olt_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_olt_ps(
 int,
 double1,
 double2
);

/* _c_olt_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_olt_sl(
 int,
 double,
 float
);

/* _c_olt_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_olt_su(
 int,
 double,
 float
);

/* _c_olt_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_olt_vl(
 int,
 double1,
 double2
);

/* _c_olt_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_olt_vu(
 int,
 double1,
 double2
);

/* _c_seq_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_le_ps(
 int,
 double1,
 double2
);

/* _c_seq_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_seq_sl(
 int,
 double,
 float
);

/* _c_seq_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_seq_su(
 int,
 double,
 float
);

/* _c_seq_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_seq_vl(
 int,
 double1,
 double2
);

/* _c_seq_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_seq_vu(
 int,
 double1,
 double2
);

/* _c_sf_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_sf_ps(
 int,
 double1,
 double2
);

/* _c_sf_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_sf_sl(
 int,
 double,
 float
);

/* _c_sf_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_sf_su(
 int,
 double,
 float
);

/* _c_sf_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_sf_vl(
 int,
 double1,
 double2
);

/* _c_sf_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_sf_vu(
 int,
 double1,
 double2
);

/* _c_ueq_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ueq_ps(
 int,
 double1,
 double2
);

/* _c_ueq_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ueq_sl(
 int,
 double,
 float
);

/* _c_ueq_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ueq_su(
 int,
 double,
 float
);

/* _c_ueq_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ueq_vl(
 int,
 double1,
 double2
);

/* _c_ueq_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ueq_vu(
 int,
 double1,
 double2
);

/* _c_ule_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ule_ps(
 int,
 double1,
 double2
);

/* _c_ule_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ule_sl(
 int,
 double,
 float
);

/* _c_ule_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ule_su(
 int,
 double,
 float
);

/* _c_ule_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ule_vl(
 int,
 double1,
 double2
);

/* _c_ule_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ule_vu(
 int,
 double1,
 double2
);

/* _c_ult_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ult_ps(
 int,
 double1,
 double2
);

/* _c_ult_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ult_sl(
 int,
 double,
 float
);

/* _c_ult_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ult_su(
 int,
 double,
 float
);

/* _c_ult_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ult_vl(
 int,
 double1,
 double2
);

/* _c_ult_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_ult_vu(
 int,
 double1,
 double2
);

/* _c_un_ps  [function; ce-only; CE 4.0..499] */
void __cdecl _c_un_ps(
 int,
 double1,
 double2
);

/* _c_un_sl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_un_sl(
 int,
 double,
 float
);

/* _c_un_su  [function; ce-only; CE 4.0..499] */
void __cdecl _c_un_su(
 int,
 double,
 float
);

/* _c_un_vl  [function; ce-only; CE 4.0..499] */
void __cdecl _c_un_vl(
 int,
 double1,
 double2
);

/* _c_un_vu  [function; ce-only; CE 4.0..499] */
void __cdecl _c_un_vu(
 int,
 double1,
 double2
);

/* _cvt_ps_s  [function; ce-only; CE 4.0..499] */
double __cdecl _cvt_ps_s(
 float1,
 float2
);

/* _cvt_s_pl  [function; ce-only; CE 4.0..499] */
float __cdecl _cvt_s_pl(
 double
);

/* _cvt_s_pu  [function; ce-only; CE 4.0..499] */
float __cdecl _cvt_s_pu(
 double
);

/* _div_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _div_ps(
 arg1,
 arg2
);

/* _div_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _div_sl(
 arg1,
 arg2
);

/* _div_su  [function; ce-only; CE 4.0..499] */
float __cdecl _div_su(
 arg1,
 arg2
);

/* _div_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _div_vl(
 arg1,
 arg2
);

/* _div_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _div_vu(
 arg1,
 arg2
);

/* _ersqrt_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _esrqrt_ps(
 arg1
);

/* _ersqrt_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _esrqrt_sl(
 arg1
);

/* _ersqrt_su  [function; ce-only; CE 4.0..499] */
float __cdecl _esrqrt_su(
 arg1
);

/* _ersqrt_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _esrqrt_vl(
 arg1
);

/* _ersqrt_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _esrqrt_vu(
 arg1
);

/* _madd_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _madd_ps(
 arg1,
 arg2,
 arg3
);

/* _madd_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _madd_sl(
 arg1,
 arg2,
 arg3
);

/* _madd_su  [function; ce-only; CE 4.0..499] */
float __cdecl _madd_su(
 arg1,
 arg2,
 arg3
);

/* _madd_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _madd_vl(
 arg1,
 arg2,
 arg3
);

/* _madd_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _madd_vu(
 arg1,
 arg2,
 arg3
);

/* _max_ob  [function; ce-only; CE 4.0..499] */
double _max_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _min_ob  [function; ce-only; CE 4.0..499] */
double _min_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _mov_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _mov_ps(
 double
);

/* _mov_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _mov_sl(
 double
);

/* _mov_su  [function; ce-only; CE 4.0..499] */
float __cdecl _mov_su(
 double
);

/* _mov_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _mov_vl(
 double
);

/* _mov_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _mov_vu(
 double
);

/* _movf_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _movf_ps(
 double,
 int
);

/* _movn_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _movz_ps(
 double,
 int
);

/* _movt_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _movz_ps(
 double,
 int
);

/* _movz_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _movz_ps(
 double,
 int
);

/* _msub_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _msub_ps(
 double1, 
 double2,
 double3
);

/* _msub_sl  [function; ce-only; CE 4.0..499] */
double __cdecl _msub_sl(
 float1, 
 double,
 float2
);

/* _msub_su  [function; ce-only; CE 4.0..499] */
double __cdecl _msub_su(
 float1, 
 double,
 float2
);

/* _msub_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _msub_ps(
 double1, 
 double2,
 double3
);

/* _msub_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _msub_ps(
 double1, 
 double2,
 double3
);

/* _mul_ob  [function; ce-only; CE 4.0..499] */
double _mul_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _mul_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _mul_ps(
 double1,
 double2
);

/* _mul_sl  [function; ce-only; CE 4.0..499] */
double __cdecl _mul_sl(
 double1,
 float
);

/* _mul_su  [function; ce-only; CE 4.0..499] */
double __cdecl _mul_su(
 double1, 
 float
);

/* _mul_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _mul_vl(
 double1,
 double2
);

/* _mul_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _mul_vl(
 double1,
 double2
);

/* _mula_ob  [function; ce-only; CE 4.0..499] */
void _mula_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _mull_ob  [function; ce-only; CE 4.0..499] */
void _mull_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _muls_ob  [function; ce-only; CE 4.0..499] */
void _muls_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _mulsl_ob  [function; ce-only; CE 4.0..499] */
void _mulsl_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _neg_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _neg_ps(
 arg1
);

/* _neg_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _neg_sl(
 arg1
);

/* _neg_su  [function; ce-only; CE 4.0..499] */
float __cdecl _neg_su(
 arg1
);

/* _neg_vl  [function; ce-only; CE 4.0..499] */
float __cdecl _neg_vl(
 arg1
);

/* _neg_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _neg_sl(
 arg1
);

/* _nmadd_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _nmadd_ps(
 arg1,
 arg2,
 arg3
);

/* _nmadd_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _nmadd_sl(
 arg1,
 arg2,
 arg3
);

/* _nmadd_su  [function; ce-only; CE 4.0..499] */
float __cdecl _nmadd_su(
 arg1,
 arg2,
 arg3
);

/* _nmadd_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _nmadd_vl(
 arg1,
 arg2,
 arg3
);

/* _nmadd_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _nmadd_vu(
 arg1,
 arg2,
 arg3
);

/* _nmsub_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _nmsub_vl(
 arg1,
 arg2,
 arg3
);

/* _nmsub_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _nmsub_sl(
 arg1,
 arg2,
 arg3
);

/* _nmsub_su  [function; ce-only; CE 4.0..499] */
float __cdecl _nmsub_su(
 arg1,
 arg2,
 arg3
);

/* _nmsub_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _nmsub_vl(
 arg1,
 arg2,
 arg3
);

/* _nmsub_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _nmsub_vu(
 arg1,
 arg2,
 arg3
);

/* _nor_ob  [function; ce-only; CE 4.0..499] */
double _nor_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _or_ob  [function; ce-only; CE 4.0..499] */
double _or_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _pickf_ob  [function; ce-only; CE 4.0..499] */
double _pickf_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _pickt_ob  [function; ce-only; CE 4.0..499] */
double _pickt_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _pll_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _pll_ps(
 arg1,
 arg2
);

/* _plu_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _plu_ps(
 arg1,
 arg2
);

/* _pul_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _pul_ps(
 arg1,
 arg2
);

/* _puu_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _puu_ps(
 arg1,
 arg2
);

/* _rach_ob  [function; ce-only; CE 4.0..499] */
double _rach_ob(void);

/* _racl_ob  [function; ce-only; CE 4.0..499] */
double _racl_ob(void);

/* _racm_ob  [function; ce-only; CE 4.0..499] */
double _racm_ob(void);

/* _recip_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _recip_ps(
 arg1
);

/* _recip_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _recip_sl(
 arg1
);

/* _recip_su  [function; ce-only; CE 4.0..499] */
float __cdecl _recip_su(
 arg1
);

/* _recip_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _recip_vl(
 arg1
);

/* _recip_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _recip_vu(
 arg1
);

/* _rsqrt_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _rsqrt_ps(
 arg1
);

/* _rsqrt_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _rsqrt_sl(
 arg1
);

/* _rsqrt_su  [function; ce-only; CE 4.0..499] */
float __cdecl _rsqrt_su(
 arg1
);

/* _rsqrt_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _rsqrt_vl(
 arg1
);

/* _rsqrt_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _rsqrt_vu(
 arg1
);

/* _rzu_ob  [function; ce-only; CE 4.0..499] */
double _rzu_ob(
 double Arg1, 
 int Arg2
);

/* _setjmpex  [function; ce-only; CE 4.0..499] */
int setjumpex(
 jmp_buf Buffer
);

/* _shfl_mixh_ob  [function; ce-only; CE 4.0..499] */
double _shfl_mixh_ob(
 double Arg1,
 double Arg2
);

/* _shfl_mixl_ob  [function; ce-only; CE 4.0..499] */
double _shfl_mixl_ob(
 double Arg1,
 double Arg2
);

/* _shfl_pach_ob  [function; ce-only; CE 4.0..499] */
double _shfl_pach_ob(
 double Arg1,
 double Arg2
);

/* _shfl_pacl_ob  [function; ce-only; CE 4.0..499] */
double _shfl_pacl_ob(
 double Arg1,
 double Arg2
);

/* _sll_ob  [function; ce-only; CE 4.0..499] */
double _sll_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _sqrt_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _sqrt_ps(
 arg1
);

/* _sqrt_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _sqrt_sl(
 arg1
);

/* _sqrt_su  [function; ce-only; CE 4.0..499] */
float __cdecl _sqrt_su(
 arg1
);

/* _sqrt_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _sqrt_vl(
 arg1
);

/* _sqrt_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _sqrt_vu(
 arg1
);

/* _srl_ob  [function; ce-only; CE 4.0..499] */
double _srl_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _sub_ob  [function; ce-only; CE 4.0..499] */
double _sub_ob(
 double Arg1,
 double Arg2,
 int Arg3
);

/* _sub_ps  [function; ce-only; CE 4.0..499] */
double __cdecl _sub_ps(
 arg1,
 arg2
);

/* _sub_sl  [function; ce-only; CE 4.0..499] */
float __cdecl _sub_sl(
 arg1,
 arg2
);

/* _sub_su  [function; ce-only; CE 4.0..499] */
float __cdecl _sub_su(
 arg1,
 arg2
);

/* _sub_vl  [function; ce-only; CE 4.0..499] */
double __cdecl _sub_vl(
 arg1,
 arg2
);

/* _sub_vu  [function; ce-only; CE 4.0..499] */
double __cdecl _sub_vu(
 arg1,
 arg2
);

/* _wach_ob  [function; ce-only; CE 4.0..499] */
void _wach_ob(
 double Arg1
);

/* _wacl_ob  [function; ce-only; CE 4.0..499] */
void _wacl_ob(
 double Arg1,
 double Arg2
);

/* _xor_ob  [function; ce-only; CE 4.0..499] */
double _xor_ob(
 double Arg1,
 double Arg2,
 int Arg3
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
double __cdecl _esrqrt_ps( arg1 );
float __cdecl _esrqrt_sl( arg1 );
float __cdecl _esrqrt_su( arg1 );
double __cdecl _esrqrt_vl( arg1 );
double __cdecl _esrqrt_vu( arg1 );

#endif /* _MIPSINTR_ */
