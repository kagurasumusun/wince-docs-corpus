/* Bthapi.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 1 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _BTHAPI_IDL_
#define _BTHAPI_IDL_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* NodeDataUnion  [typedef; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* NodeData  [struct; ce-only] */
typedef struct NodeData {
 USHORT type;
 USHORT specificType;
 NodeDataUnion u;
} NodeData;
typedef NodeData *PNodeData, *LPNodeData;

#endif /* _BTHAPI_IDL_ */
