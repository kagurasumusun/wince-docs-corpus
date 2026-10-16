/* FlashMdd.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 8 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _FLASHMDD_
#define _FLASHMDD_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FLASH_PARTITION_FLAGS  [enum; ce-only] */
enum FLASH_PARTITION_FLAGS {
 FLASH_PARTITION_FLAG_DIRECT_MAP = 0x00000001,
 FLASH_PARTITION_FLAG_READ_ONLY = 0x00000002,
 FLASH_PARTITION_FLAG_RESERVED = 0x00000004,
};

/* FLASH_TRANSFER_REQUEST_FLAGS  [enum; ce-only] */
enum FLASH_TRANSFER_REQUEST_FLAGS {
 FLASH_SECTOR_REQUEST_FLAG_ATOMIC = 0x00000001,
 FLASH_SECTOR_REQUEST_FLAG_WRITE_THROUGH = 0x00000002,
};

#endif /* _FLASHMDD_ */
