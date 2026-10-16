/* FlashPdd.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 9 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _FLASHPDD_
#define _FLASHPDD_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* FLASH_BLOCK_STATUS  [enum; ce-only] */
enum FLASH_BLOCK_STATUS {
 FLASH_BLOCK_STATUS_BAD = 0x1,
 FLASH_BLOCK_STATUS_RESERVED = 0x2
};

/* FLASH_LIFE_CYCLE_INFO  [struct; ce-only] */
typedef struct __FLASH_LIFE_CYCLE_INFO {
 DWORD ErasePerBlock;
} FLASH_LIFE_CYCLE_INFO;
typedef FLASH_LIFE_CYCLE_INFO *PFLASH_LIFE_CYCLE_INFO, *LPFLASH_LIFE_CYCLE_INFO;

/* FLASH_READ_STATUS  [enum; ce-only] */
enum FLASH_READ_STATUS {
 FLASH_READ_STATUS_ECC_CORRECTION_REQUIRED = 0x1
};

#endif /* _FLASHPDD_ */
