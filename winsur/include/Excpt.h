/* Excpt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 3 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _EXCPT_
#define _EXCPT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define EXCEPTION_EXECUTE_HANDLER 1

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* EXCEPTION_POINTERS  [struct; shared] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   ExceptionRecord */
/*   ContextRecord */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x400) || (_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 2.11..2.12, 3.0..399, 5.0..699 */

/* AbnormalTermination  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
BOOL AbnormalTermination(void);

/* GetExceptionCode  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
DWORD GetExceptionCode(void);

/* GetExceptionInformation  [function; ce-only; CE 2.11..2.12, 3.0..399, 5.0..699; Coredll.lib, coredll.lib] */
LPEXCEPTION_POINTERS GetExceptionInformation(void);
#endif /* _WIN32_WCE */

#endif /* _EXCPT_ */
