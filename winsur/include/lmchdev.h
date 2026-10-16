/* lmchdev.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 17 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMCHDEV_
#define _LMCHDEV_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CHARDEV_CLOSE 0
#define CHARDEV_STAT_ERROR 4
#define CHARDEV_STAT_OPENED 2
#define CHARDEVQ_DEF_PRIORITY 5
#define CHARDEVQ_DEV_PARMNUM 1
#define CHARDEVQ_DEVS_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+CHARDEVQ_DEVS_PARMNUM)
#define CHARDEVQ_DEVS_PARMNUM 3
#define CHARDEVQ_MAX_PRIORITY 1
#define CHARDEVQ_MIN_PRIORITY 9
#define CHARDEVQ_NO_REQUESTS (-1)
#define CHARDEVQ_NUMAHEAD_PARMNUM 5
#define CHARDEVQ_NUMUSERS_PARMNUM 4
#define CHARDEVQ_PRIORITY_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+CHARDEVQ_PRIORITY_PARMNUM)
#define CHARDEVQ_PRIORITY_PARMNUM 2
#define HANDLE_CHARCOUNT_PARMNUM 2
#define HANDLE_CHARTIME_PARMNUM 1
#define HANDLE_INFO_LEVEL_1 1

#endif /* _LMCHDEV_ */
