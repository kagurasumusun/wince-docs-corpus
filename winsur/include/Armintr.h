/* Armintr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 37 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _ARMINTR_
#define _ARMINTR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* _AddSatInt  [function; ce-only; CE 4.0..699] */
int _AddSatInt(
 int Arg1,
 int Arg2
);

/* _DAddSatInt  [function; ce-only; CE 4.0..699] */
int _DAddSatInt(
 int Arg1, 
 int Arg2
);

/* _DSubSatInt  [function; ce-only; CE 4.0..699] */
int _DSubSatInt(
 int Arg1,
 int Arg2
);

/* _PreLoad  [function; ce-only; CE 4.0..699] */
void _PreLoad(
 unsigned long* addr
);

/* _ReadCoProcessor  [function; ce-only; CE 4.0..699] */
__int64 _ReadCoProcessor(
 int Arg1
);

/* _SmulAdd_SL_ACC  [function; ce-only; CE 4.0..699] */
void _SmulAdd_SL_ACC(
 int Arg1,
 int Arg2
);

/* _SmulAddHi_SW_ACC  [function; ce-only; CE 4.0..699] */
void _SmulAddHi_SW_ACC(
 int Arg1,
 int Arg2
);

/* _SmulAddHi_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulAddHi_SW_SL(
 int Arg1, 
 int Arg2,
 int Arg3
);

/* _SmulAddHi_SW_SQ  [function; ce-only; CE 4.0..699] */
__int64 _SmulAddHi_SW_SQ(
 __int64 Arg1, 
 int Arg2, 
 int Arg3
);

/* _SmulAddHiLo_SW_ACC  [function; ce-only; CE 4.0..699] */
void _SmulAddHiLo_SW_ACC(
 int Arg1,
 int Arg2
);

/* _SmulAddHiLo_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulAddHiLo_SW_SL(
 int Arg1, 
 int Arg2,
 int Arg3
);

/* _SmulAddHiLo_SW_SQ  [function; ce-only; CE 4.0..699] */
__int64 _SmulAddHiLo_SW_SQ(
 __int64 Arg1, 
 int Arg2, 
 int Arg3
);

/* _SmulAddLo_SW_ACC  [function; ce-only; CE 4.0..699] */
void _SmulAddLo_SW_ACC(
 int Arg1,
 int Arg2
);

/* _SmulAddLo_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulAddLo_SW_SL( 
 int Arg1, 
 int Arg2,
 int Arg3
);

/* _SmulAddLo_SW_SQ  [function; ce-only; CE 4.0..699] */
__int64 _SmulAddLo_SW_SQ(
 __int64 Arg1, 
 int Arg2, 
 int Arg3
);

/* _SmulAddLoHi_SW_ACC  [function; ce-only; CE 4.0..699] */
void _SmulAddLoHi_SW_ACC(
 int Arg1,
 int Arg2
);

/* _SmulAddLoHi_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulAddLoHi_SW_SL(
 int Arg1, 
 int Arg2,
 int Arg3
);

/* _SmulAddLoHi_SW_SQ  [function; ce-only; CE 4.0..699] */
__int64 _SmulAddLoHi_SW_SQ(
 __int64 Arg1, 
 int Arg2, 
 int Arg3
);

/* _SmulAddPack_2SW_ACC  [function; ce-only; CE 4.0..699] */
void _SmulAddPack_2SW_ACC(
 int Arg1,
 int Arg2
);

/* _SmulAddWHi_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulAddWHi_SW_SL(
 int Arg1, 
 int Arg2,
 int Arg3
);

/* _SmulAddWLo_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulAddWLo_SW_SL(
 int Arg1, 
 int Arg2
);

/* _SmulHi_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulHi_SW_SL(
 int Arg1, 
 int Arg2
);

/* _SmulHiLo_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulHiLo_SW_SL(
 int Arg1, 
 int Arg2
);

/* _SmulLo_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulLo_SW_SL(
 int Arg1, 
 int Arg2
);

/* _SmulLoHi_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulLoHi_SW_SL(
 int Arg1, 
 int Arg2
);

/* _SmulWHi_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulWHi_SW_SL(
 int Arg1,
 int Arg2
);

/* _SmulWLo_SW_SL  [function; ce-only; CE 4.0..699] */
int _SmulWLo_SW_SL(
 int Arg1, 
 int Arg2
);

/* _SubSatInt  [function; ce-only; CE 4.0..699] */
int _SubSatInt(
 int Arg1,
 int Arg2
);

/* _WriteCoProcessor  [function; ce-only; CE 4.0..699] */
void _WriteCoProcessor(
 __int64 Arg1,
 int Arg2
);

/* BKPT  [function; ce-only; CE 4.0..699] */
int __trap(
 int Arg1
);

/* CLZ  [function; ce-only; CE 4.0..699] */
unsigned cdecl _CountLeadingZeros(
 long Arg1
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* _MoveToCoprocessor2  [function; ce-only; CE 5.0..599; entity-headers] */
Void _MoveToCoprocessor( unsigned int value,
 unsigned int coproc,
 unsigned int opcode1,unsigned int crn,unsigned int crm,unsigned int opcode2
);
Void _MoveToCoprocessor2( unsigned int value,
 unsigned int coproc,
 unsigned int opcode1,unsigned int crn,unsigned int crm,unsigned int opcode2
);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* __emit  [function; ce-only; CE 5.0..699] */
void __emit(
 const unsigned __int32 opcode
);

/* _MoveFromCoprocessor  [function; ce-only; CE 5.0..699] */
int _MoveFromCoprocessor(
 unsigned int coproc,
 unsigned int opcode1,
 unsigned int crn,
 unsigned int crm,
 unsigned int opcode2
);
int _MoveFromCoprocessor2(
 unsigned int coproc,
 unsigned int opcode1,
 unsigned int crn,
 unsigned int crm,
 unsigned int opcode2
);

/* _MoveFromCoprocessor2  [function; ce-only; CE 5.0..699; entity-headers] */
int _MoveFromCoprocessor(
 unsigned int coproc,
 unsigned int opcode1,
 unsigned int crn,
 unsigned int crm,
 unsigned int opcode2
);
int _MoveFromCoprocessor2(
 unsigned int coproc,
 unsigned int opcode1,
 unsigned int crn,
 unsigned int crm,
 unsigned int opcode2
);

/* _MoveToCoprocessor  [function; ce-only; CE 5.0..699] */
Void _MoveToCoprocessor(
 unsigned int value,
 unsigned int coproc,
 unsigned int opcode1,
 unsigned int crn,
 unsigned int crm,
 unsigned int opcode2
);
Void _MoveToCoprocessor2(
 unsigned int value,
 unsigned int coproc,
 unsigned int opcode1,
 unsigned int crn,
 unsigned int crm,
 unsigned int opcode2
);

/* _swi  [function; ce-only; CE 5.0..699] */
unsigned int __swi(
 unsigned swi_number,
 arg2,
 arg3,
 arg4
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
int __swi( unsigned swi_number, arg2, arg3, arg4 );
unsigned int__swi(unsigned swi_number,arg2, arg3, arg4);

#endif /* _ARMINTR_ */
