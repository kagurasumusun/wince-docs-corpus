/* voiperrorcodes.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 14 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _VOIPERRORCODES_
#define _VOIPERRORCODES_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define VOIP_E_ALREADYINITIALIZED 0x80cc0003
#define VOIP_E_BUSY 0x80cc0006
#define VOIP_E_ENUMOUTOFDATE 0x80cc0000
#define VOIP_E_INVALIDCALLSTATUS 0x80cc0009
#define VOIP_E_NOACTIVECALL 0x80cc0007
#define VOIP_E_NODB 0x80cc0004
#define VOIP_E_NOMEDIAMGR 0x80cc000c
#define VOIP_E_NOTCURRENTCALL 0x80cc0005
#define VOIP_E_NOTINITIALIZED 0x80cc0001
#define VOIP_E_PROVISIONING_FAILED 0x80cc000b
#define VOIP_E_RECORDNOTINDB 0x80cc0002
#define VOIP_E_TIMENOTSET 0x80cc0008
#define VOIP_E_TOOMANYCONFERENCEPARTICIPANTS 0x80cc000d
#define VOIP_S_DONT_TERMINATE 0x00040000

#endif /* _VOIPERRORCODES_ */
