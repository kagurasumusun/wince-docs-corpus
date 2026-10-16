/* mgmtapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 10 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MGMTAPI_
#define _MGMTAPI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define MGMCTL_SETAGENTPORT 1
#define SNMP_MGMTAPI_AGAIN 45
#define SNMP_MGMTAPI_INVALID_BUFFER 48
#define SNMP_MGMTAPI_INVALID_CTL 46
#define SNMP_MGMTAPI_INVALID_SESSION 47
#define SNMP_MGMTAPI_NOTRAPS 44
#define SNMP_MGMTAPI_SELECT_FDERRORS 41
#define SNMP_MGMTAPI_TIMEOUT 40
#define SNMP_MGMTAPI_TRAP_DUPINIT 43
#define SNMP_MGMTAPI_TRAP_ERRORS 42

#endif /* _MGMTAPI_ */
