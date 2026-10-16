/* dsquery.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DSQUERY_
#define _DSQUERY_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DSCOLUMNPROP_ADSPATH -1
#define DSCOLUMNPROP_OBJECTCLASS -2
#define DSQPF_ENABLEADMINFEATURES 0x00000008
#define DSQPF_ENABLEADVANCEDFEATURES 0x00000010
#define DSQPF_HASCREDENTIALS 0x00000020
#define DSQPF_NOCHOOSECOLUMNS 0x00000040
#define DSQPF_NOSAVE 0x00000001
#define DSQPF_SAVELOCATION 0x00000002
#define DSQPF_SHOWHIDDENOBJECTS 0x00000004

#endif /* _DSQUERY_ */
