/* exdi.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 35 extra decls
 */
#ifndef _EXDI_IDL_
#define _EXDI_IDL_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT DelCodeBreakpoint( IeXdiCodeBreakpoint* pieXdiCodeBreakpoint );
HRESULT DelDataBreakpoint( IeXdiDataBreakpoint* pieXdiDataBreakpoint );
HRESULT DisableAll (void);
HRESULT DoMultipleStep( DWORD dwNbInstructions );
HRESULT DoSingleStep ();
HRESULT EnableAll (void);
HRESULT EnumAllCodeBreakpoints( IeXdiEnumCodeBreakpoint** ppieXdiEnumCodeBreakpoint );
HRESULT EnumAllDataBreakpoints( IeXdiEnumDataBreakpoint** ppieXdiEnumDataBreakpoint );
HRESULT GetNbCodeBpAvail( DWORD* pdwNbHwCodeBpAvail, DWORD* pdwNbSwCodeBpAvail );
HRESULT GetNbDataBpAvail( DWORD* pdwNbDataBpAvail );
HRESULT GetNext( IeXdiCodeBreakpoint** ppieXdiCodeBreakpoint );
HRESULT Halt ();
HRESULT Reboot ();
HRESULT StartNotifyingMemChg( IeXdiClientNotifyMemChg* pieXdiClientNotifyMemChg, DWORD* pdwConnectionCookie );
HRESULT StartNotifyingRunChg( IeXdiClientNotifyRunChg *pieXdiClientNotifyRunChg, DWORD* pdwConnectionCookie );
HRESULT StopNotifyingMemChg( DWORD dwConnectionCookie );
HRESULT StopNotifyingRunChg( DWORD dwConnectionCookie );

#endif /* _EXDI_IDL_ */
