/* Iltiming.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ILTIMING_
#define _ILTIMING_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* ILTIMING_MESSAGE  [struct; ce-only] */
typedef struct tILTIMING_MESSAGE {
 WORD wMsg;
 WORD wNumInterrupts;
 DWORD dwIsrTime1;
 DWORD dwIsrTime2;
 DWORD dwSPC;
 DWORD dwFrequency;
 PVOID pfnPerfCountSinceTick;
} ILTIMING_MESSAGE, *PILTIMING_MESSAGE;

#endif /* _ILTIMING_ */
