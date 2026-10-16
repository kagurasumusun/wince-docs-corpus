/* aclui.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 31 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ACLUI_
#define _ACLUI_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ACLUIAPI DECLSPEC_IMPORT
#define INTERFACE ISecurityInformation
#define PSPCB_SI_INITDIALOG (WM_USER
#define SI_ACCESS_CONTAINER 0x00040000L
#define SI_ACCESS_GENERAL 0x00020000L
#define SI_ACCESS_PROPERTY 0x00080000L
#define SI_ACCESS_SPECIFIC 0x00010000L
#define SI_ADVANCED 0x00000010L
#define SI_CONTAINER 0x00000004L
#define SI_EDIT_ALL (SI_EDIT_PERMS
#define SI_EDIT_AUDITS 0x00000002L
#define SI_EDIT_EFFECTIVE 0x00020000L
#define SI_EDIT_OWNER 0x00000001L
#define SI_EDIT_PERMS 0x00000000L
#define SI_EDIT_PROPERTIES 0x00000080L
#define SI_MAY_WRITE 0x10000000L
#define SI_NO_ACL_PROTECT 0x00000200L
#define SI_NO_ADDITIONAL_PERMISSION 0x00200000L
#define SI_NO_TREE_APPLY 0x00000400L
#define SI_OBJECT_GUID 0x00010000L
#define SI_OWNER_READONLY 0x00000040L
#define SI_OWNER_RECURSE 0x00000100L
#define SI_PAGE_TITLE 0x00000800L
#define SI_READONLY 0x00000008L
#define SI_RESET 0x00000020L
#define SI_RESET_DACL 0x00040000L
#define SI_RESET_DACL_TREE 0x00004000L
#define SI_RESET_OWNER 0x00100000L
#define SI_RESET_SACL 0x00080000L
#define SI_RESET_SACL_TREE 0x00008000L
#define SI_SERVER_IS_DC 0x00001000L

#endif /* _ACLUI_ */
