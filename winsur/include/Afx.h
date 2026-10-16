/* Afx.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 1 declarations, 1 outlines, 0 base types, 0 extra macros, 25 extra decls
 */
#ifndef _AFX_
#define _AFX_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CRuntimeClass  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CFileStatus  [struct; ce-only] */
struct CFileStatus
{
CTime m_ctime;
CTime m_mtime;
CTime m_atime;
LONG m_size;
BYTE m_attribute;
TCHAR m_szFullName[_MAX_PATH];
};

/* _MAX_PATH  [extra struct] */
struct CFileStatus
{
  CTime m_ctime;
  CTime m_mtime;
  CTime m_atime;
  LONG m_size;
  BYTE m_attribute;
  TCHAR m_szFullName[_MAX_PATH];
};

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
static int PASCAL ErrnoToException( int nErrno );
LPTSTR GetBufferSetLength( int nNewLength ); throw( CMemoryException );
void GrowFile( DWORD dwNewLen );
void HexDump( LPCTSTR lpszLine, BYTE* pby, int nBytes, int nWidth ); throw( CFileException );
void MakeLower( );
void MakeReverse( );
void MakeUpper( );
BYTE * Memcpy( BYTE* lpMemTarget, BYTE* lpMemSource, UINT nBytes );
static int PASCAL OsErrorToException( LONG lOsError );
DWORD ReadHuge( void* lpBuffer, DWORD dwCount ); throw( CFileException );
static void PASCAL Rename( LPCTSTR lpszOldName, LPCTSTR lpszNewName ); throw( CFileException );
void SeekToBegin( ); throw( CFileException );
DWORD SeekToEnd( ); throw( CFileException );
void SerializeClass( const CRuntimeClass* pRuntimeClass );
void SetDepth( int nNewDepth );
void SetLoadParams( UINT nGrowBy = 1024 );
void SetObjectSchema( UINT nSchema );
void SetStoreParams( UINT nHashSize = 2053, UINT nBlockSize = 128 );
static void PASCAL ThrowErrno( int nErrno );
void TrimLeft( );
void TrimRight( );
void WriteClass( const CRuntimeClass* pClassRef );
void WriteHuge( const void* lpBuf, DWORD dwCount ); throw( CFileException );
void WriteString( LPCTSTR lpsz ); throw( CFileException );

#endif /* _AFX_ */
