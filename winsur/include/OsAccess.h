/* OsAccess.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 21 extra decls
 */
#ifndef _OSACCESS_
#define _OSACCESS_


/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT Disable(void);
HRESULT GetFullThdContextRegList( IeXdi2EnumCpuRegs**ppiOsAxsEnumCpuRegThreadCtx);
HRESULT GetPageSize( DWORD*pdwVmPageSize);
HRESULT NotifyModuledOle( VARIANTvtModId, VARIANTvtLoaded);
HRESULT SingleStepInCurThread( BOOL fIgnoreCurrentExcept, BOOL fOneCycleOnly );

#endif /* _OSACCESS_ */
