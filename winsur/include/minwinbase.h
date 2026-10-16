/* minwinbase.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 19 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MINWINBASE_
#define _MINWINBASE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CREATE_PROCESS_DEBUG_EVENT 3
#define CREATE_THREAD_DEBUG_EVENT 2
#define EXIT_PROCESS_DEBUG_EVENT 5
#define EXIT_THREAD_DEBUG_EVENT 4
#define IO_REPARSE_TAG_CSV 0x80000009
#define IO_REPARSE_TAG_DEDUP 0x80000013
#define IO_REPARSE_TAG_DFS 0x8000000A
#define IO_REPARSE_TAG_DFSR 0x80000012
#define IO_REPARSE_TAG_HSM 0xC0000004
#define IO_REPARSE_TAG_HSM2 0x80000006
#define IO_REPARSE_TAG_MOUNT_POINT 0xA0000003
#define IO_REPARSE_TAG_NFS 0x80000014
#define IO_REPARSE_TAG_SIS 0x80000007
#define IO_REPARSE_TAG_SYMLINK 0xA000000C
#define IO_REPARSE_TAG_WIM 0x80000008
#define LOAD_DLL_DEBUG_EVENT 6
#define OUTPUT_DEBUG_STRING_EVENT 8
#define RIP_EVENT 9
#define UNLOAD_DLL_DEBUG_EVENT 7

#endif /* _MINWINBASE_ */
