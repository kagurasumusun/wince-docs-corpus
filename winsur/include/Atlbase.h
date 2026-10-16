/* Atlbase.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 10 outlines, 0 base types, 0 extra macros, 21 extra decls
 */
#ifndef _ATLBASE_
#define _ATLBASE_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* CComModule::UpdateRegistryFromResourceD  [struct; ce-only] */

/* CComModule::UpdateRegistryFromResourceS  [struct; ce-only] */

/* CComMultiThreadModel::AutoCriticalSection  [typedef; ce-only] */

/* CComMultiThreadModel::CriticalSection  [typedef; ce-only] */

/* CComMultiThreadModel::ThreadModelNoCS  [typedef; ce-only] */

/* CComMultiThreadModelNoCS::AutoCriticalSection  [typedef; ce-only] */

/* CComMultiThreadModelNoCS::CriticalSection  [typedef; ce-only] */

/* CComMultiThreadModelNoCS::ThreadModelNoCS  [typedef; ce-only] */

/* CComSingleThreadModel::AutoCriticalSection  [typedef; ce-only] */

/* CComSingleThreadModel::CriticalSection  [typedef; ce-only] */

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x212 && _WIN32_WCE < 0x400)) /* CE 2.12..399 */

/* AtlTrace  [function; ce-only; CE 2.12..399] */
void _cdecl AtlTrace( LPCTSTR lpszFormat, ... );
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
void Append( const CComBSTR& bstrSrc );
void CComAutoCriticalSection( );
ULONG CComPtr( VOID );
ULONG CComQIPtr( VOID );
static ULONG Decrement( LPLONG p);
LONG DeleteSubKey( LPCTSTR lpszSubKey );
void Empty( );
LONG GetLockCount( );
HINSTANCE GetModuleInstance( );
HINSTANCE GetResourceInstance( );
HINSTANCE GetTypeLibInstance( );
static ULONG Increment( LPLONG p);
LONG QueryValue( DWORD& dwValue, LPCTSTR lpszValueName );
LONG RecurseDeleteKey( LPCTSTR lpszKey );
HRESULT RevokeClassObjects( );
void Term( );

#endif /* _ATLBASE_ */
