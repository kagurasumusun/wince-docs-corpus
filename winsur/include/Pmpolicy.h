/* Pmpolicy.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 4 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PMPOLICY_
#define _PMPOLICY_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define PPN_APPBUTTONPRESSED 0x0006
#define PPN_POWERCHANGE 0x0002
#define PPN_REEVALUATESTATE 0x0001
#define PPN_SUSPENDKEYRELEASED 0x0005

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* PowerPolicyNotify  [function; ce-only; CE 5.0..699; Coredll.lib] */
BOOL PowerPolicyNotify(
 DWORD dwMessage,
 DWORD dwData
);
#endif /* _WIN32_WCE */

#endif /* _PMPOLICY_ */
