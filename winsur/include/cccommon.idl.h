/* cccommon.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 5 declarations, 2 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _CCCOMMON_IDL_
#define _CCCOMMON_IDL_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* FileVerifyInfo  [struct; ce-only] */

/* FileVerifyReference  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FileCustomAction  [enum; ce-only] */
typedef enum tagFileCustomAction{
 FileCustomAction_None = 0x0000,
 FileCustomAction_COM = 0x0001,
} FileAction;

/* FileInfo  [struct; ce-only; coredll.lib] */
typedef struct tagFileInfo{
 LONG m_FileAttribues;
 LONGLONG m_FileSize;
 FILETIME m_CreationTime;
 FILETIME m_LastAccessTime;
 FILETIME m_LastWriteTime;
} FileInfo;
typedef FileInfo *PFileInfo, *LPFileInfo;

/* FileVerifyResult  [struct; ce-only] */
typedef struct tagFileVerifyResult{
 DWORD m_Version;
 FileVerifyInfo _Info;
} FileVerifyResult;
typedef FileVerifyResult *PFileVerifyResult, *LPFileVerifyResult;

/* FileVerifyVersion  [struct; ce-only] */
typedef struct tagFileVerifyVersion{
 DWORD m_Major;
 DWORD m_Minor;
 DWORD m_Build;
 DWORD m_Revision;
} FileVerifyVersion;
typedef FileVerifyVersion *PFileVerifyVersion, *LPFileVerifyVersion;

/* SystemInfo  [struct; ce-only] */
typedef struct tagPlatformInfo{
 DWORD m_OSMajor;
 DWORD m_OSMinor;
 DWORD m_BuildNo;
 DWORD m_ProcessorArchitecture;
 DWORD m_InstructionSet;
} SystemInfo;
typedef SystemInfo *PSystemInfo, *LPSystemInfo;

#endif /* _CCCOMMON_IDL_ */
