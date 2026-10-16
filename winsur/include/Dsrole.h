/* Dsrole.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 4 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DSROLE_
#define _DSROLE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DSROLE_PRIMARY_DOMAIN_GUID_PRESENT 0x01000000
#define DSROLE_PRIMARY_DS_MIXED_MODE 0x00000002
#define DSROLE_PRIMARY_DS_RUNNING 0x00000001
#define DSROLE_UPGRADE_IN_PROGRESS 0x00000004

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* DsRoleFreeMemory  [function; shared; CE 5.0..599; Netapi32.lib] */
void DsRoleFreeMemory( 
 PVOID Buffer 
);
#endif /* _WIN32_WCE */

#endif /* _DSROLE_ */
