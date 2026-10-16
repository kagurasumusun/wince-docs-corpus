/* pbt.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 14 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PBT_
#define _PBT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define PBT_APMBATTERYLOW 9
#define PBT_APMOEMEVENT 11
#define PBT_APMPOWERSTATUSCHANGE 10
#define PBT_APMQUERYSTANDBY 1
#define PBT_APMQUERYSTANDBYFAILED 3
#define PBT_APMQUERYSUSPEND 0
#define PBT_APMQUERYSUSPENDFAILED 2
#define PBT_APMRESUMEAUTOMATIC 18
#define PBT_APMRESUMECRITICAL 6
#define PBT_APMRESUMESTANDBY 8
#define PBT_APMRESUMESUSPEND 7
#define PBT_APMSTANDBY 5
#define PBT_APMSUSPEND 4
#define PBTF_APMRESUMEFROMFAILURE 1

#endif /* _PBT_ */
