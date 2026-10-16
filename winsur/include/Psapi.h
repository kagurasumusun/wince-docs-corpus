/* Psapi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PSAPI_
#define _PSAPI_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* MODULEINFO  [struct; shared] */
typedef struct _MODULEINFO {
 LPVOID lpBaseOfDll;
 DWORD SizeOfImage;
 LPVOID EntryPoint;
} MODULEINFO, *LPMODULEINFO;

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x700)) /* CE 5.0..699 */

/* CeSetProcessVersion  [function; ce-only; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL CeSetProcessVersion(
 HANDLE hProcess,
 DWORD dwVersion
);

/* GetModuleInformation  [function; shared; CE 5.0..699; Coredll.lib, coredll.lib] */
BOOL GetModuleInformation(
 HANDLE hProcess,
 HMODULE hModule,
 LPMODULEINFO lpmodinfo,
 DWORD cb
);
#endif /* _WIN32_WCE */

#endif /* _PSAPI_ */
