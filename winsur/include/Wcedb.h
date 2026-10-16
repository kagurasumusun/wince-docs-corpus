/* Wcedb.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 26 extra decls
 */
#ifndef _WCEDB_
#define _WCEDB_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
BOOL AddProp( CCeDBProp* pProp );
BOOL AddProps( CCeDBProp* pPropArray, int nNumProps );
BOOL AddRecord( CCeDBRecord* pRecord );
void DeleteAllProps( );
BOOL DeleteCurrRecord( );
void DeleteProp( WORD wPropIdent );
static BOOL Exists( LPCWSTR szName );
CEOID SeekFirst( );
CEOID SeekFirstEqual( CCeDBProp& Prop );
CEOID SeekNext( );
CEOID SeekNextEqual( CCeDBProp& Prop );
CEOID SeekPrev( );
CEOID SeekToRecord( CEOID CeOID );
CEOID SeekValueGreater( CCeDBProp& Prop );
CEOID SeekValueSmaller( CCeDBProp& Prop );
void SetFiletime( FILETIME filetime );
BOOL SetIdent( DWORD dwIdent );
BOOL SetLastModified( FILETIME ftLastModified );
void SetLong( long lVal );
void SetShort( short iVal );
void SetSortFlags( WORD wSortFlags );
BOOL SetSortProps( int nSize, const CCeDBProp *pSortProps );
void SetString( LPWSTR lpwstr, UINT nMode = Copy );
void SetULong( ULONG ulVal );
void SetUShort( USHORT uiVal );

#endif /* _WCEDB_ */
