/* Afxcmn.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 39 extra decls
 */
#ifndef _AFXCMN_
#define _AFXCMN_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL DeleteAllItems( );
BOOL DeleteColumn( int nCol );
BOOL DeleteImageList( );
static BOOL DragShowNolock( BOOL bShow );
CEdit* EditLabel( int nItem );
static void EndDrag( );
BOOL EnsureVisible( int nItem, BOOL bPartialOK );
UINT GetIndent( );
UINT GetVisibleCount( );
int OffsetPos( int nPos );
BOOL RedrawItems( int nFirst, int nLast );
BOOL Replace( int nImage, CBitmap* pbmImage, CBitmap* pbmMask );
int SetBase( int nBase );
BOOL SetCallbackMask( UINT nMask );
CImageList* SetImageList( CImageList* pImageList, int nImageList );
void SetIndent( UINT nIndent );
void SetItemCount( int nItems );
BOOL SetItemPosition( int nItem, POINT pt );
BOOL SetItemText( int nItem, int nSubItem, LPTSTR lpszText );
int SetLineSize( int nSize );
BOOL SetOverlayImage( int nImage, int nOverlay );
int SetPageSize( int nSize );
int SetPos( int nPos );
void SetRange( int nLower, int nUpper );
void SetSelection( int nMin, int nMax );
int SetStep( int nStep );
BOOL SetTextBkColor( COLORREF cr );
BOOL SetTic( int nTic );
void SetTicFreq( int nFreq );
int StepIt( );
void VerifyPos( );

#endif /* _AFXCMN_ */
