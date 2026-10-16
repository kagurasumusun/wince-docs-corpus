/* Afxext.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 11 extra decls
 */
#ifndef _AFXEXT_
#define _AFXEXT_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
int GetColumnCount( );
void GetColumnInfo( int col, int& cxCur, int& cxMin );
int GetRowCount( );
void GetRowInfo( int row, int& cyCur, int& cyMin );
int IdFromRowCol( int row, int col );
void RecalcLayout( );
void SerializeRaw( CArchive& ar );
void SetColumnInfo( int col, int cxIdeal, int cxMin );
void SetRowInfo( int row, int cyIdeal, int cyMin );
void SetScrollStyle( DWORD dwStyle );
void SizeToContent( );

#endif /* _AFXEXT_ */
