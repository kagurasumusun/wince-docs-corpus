/* Extfile.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 2 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _EXTFILE_
#define _EXTFILE_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FILECHANGEINFO  [struct; ce-only; ceshell.lib] */
struct _FILECHANGEINFO {
 DWORD cbSize;
 LONG wEventId;
 ULONG uFlags;
 DWORD dwItem1;
 DWORD dwItem2;
 DWORD dwAttributes;
 FILETIME ftModified;
 ULONG nFileSize;
} FILECHANGEINFO, *LPFILECHANGEINFO;

#endif /* _EXTFILE_ */
