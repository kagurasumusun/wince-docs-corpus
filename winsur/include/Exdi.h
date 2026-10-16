/* Exdi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _EXDI_
#define _EXDI_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DEBUG_ACCESS_CAPABILITIES_STRUCT  [struct; ce-only] */
typedef struct _DEBUG_ACCESS_CAPABILITIES_STRUCT{
 BOOL fWriteCBPWhileRunning;
 BOOL fReadCBPWhileRunning;
 BOOL fWriteDBPWhileRunning;
 BOOL fReadDBPWhileRunning;
 BOOL fWriteVMWhileRunning;
 BOOL fReadVMWhileRunning;
 BOOL fWritePMWhileRunning;
 BOOL fReadPMWhileRunning;
 BOOL fWriteRegWhileRunning;
 BOOL fReadRegWhileRunning;
}
DEBUG_ACCESS_CAPABILITIES_STRUCT, *PDEBUG_ACCESS_CAPABILITIES_STRUCT;

#endif /* _EXDI_ */
