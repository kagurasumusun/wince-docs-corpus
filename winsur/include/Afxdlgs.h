/* Afxdlgs.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 9 extra decls
 */
#ifndef _AFXDLGS_
#define _AFXDLGS_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void AddPage( CPropertyPage *pPage );
void CancelToClose( );
void Construct( UINT nIDTemplate, UINT nIDCaption = 0 );
static CFindReplaceDialog* PASCAL GetNotifier( LPARAM lParam );
int GetPageCount( );
BOOL PressButton( int nButton );
LRESULT QuerySiblings( WPARAM wParam, LPARAM lParam );
void RemovePage( CPropertyPage *pPage );
BOOL SetActivePage( int nPage );

#endif /* _AFXDLGS_ */
