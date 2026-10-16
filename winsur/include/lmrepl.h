/* lmrepl.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 19 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _LMREPL_
#define _LMREPL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define REPL_EXPORT_EXTENT_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+1)
#define REPL_EXPORT_INTEGRITY_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+0)
#define REPL_EXTENT_FILE 1
#define REPL_EXTENT_TREE 2
#define REPL_GUARDTIME_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+2)
#define REPL_INTEGRITY_FILE 1
#define REPL_INTEGRITY_TREE 2
#define REPL_INTERVAL_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+0)
#define REPL_PULSE_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+1)
#define REPL_RANDOM_INFOLEVEL (PARMNUM_BASE_INFOLEVEL+3)
#define REPL_ROLE_BOTH 3
#define REPL_ROLE_EXPORT 1
#define REPL_ROLE_IMPORT 2
#define REPL_STATE_NEVER_REPLICATED 3
#define REPL_STATE_NO_MASTER 1
#define REPL_STATE_NO_SYNC 2
#define REPL_STATE_OK 0
#define REPL_UNLOCK_FORCE 1
#define REPL_UNLOCK_NOFORCE 0

#endif /* _LMREPL_ */
