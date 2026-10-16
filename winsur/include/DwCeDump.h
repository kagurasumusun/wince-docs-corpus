/* DwCeDump.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 11 constants, 16 declarations, 0 outlines, 0 base types, 0 extra macros, 16 extra decls
 */
#ifndef _DWCEDUMP_
#define _DWCEDUMP_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ceStreamBucketParameters 0x800A
#define ceStreamException 0x8002
#define ceStreamMemoryPhysicalList 0x8009
#define ceStreamMemoryVirtualList 0x8008
#define ceStreamModuleList 0x8003
#define ceStreamNull 0x8000
#define ceStreamProcessList 0x8004
#define ceStreamSystemInfo 0x8001
#define ceStreamThreadCallStackList 0x8007
#define ceStreamThreadContextList 0x8006
#define ceStreamThreadList 0x8005

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* _MINIDUMP_STREAM_TYPE  [enum; ce-only] */
typedef enum _MINIDUMP_STREAM_TYPE {
 UnusedStream = 0,
 ceStreamNull = 0x8000,
 ceStreamSystemInfo = 0x8001,
 ceStreamException = 0x8002,
 ceStreamModuleList = 0x8003,
 ceStreamProcessList = 0x8004,
 ceStreamThreadList = 0x8005, 
 ceStreamThreadContextList = 0x8006,
 ceStreamThreadCallStackList = 0x8007,
 ceStreamMemoryVirtualList = 0x8008,
 ceStreamMemoryPhysicalList = 0x8009,
 ceStreamBucketParameters = 0x800A, 
 LastReservedStream = 0xffff
} MINIDUMP_STREAM_TYPE;

#endif /* _DWCEDUMP_ */
