/* Addrstor.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 21 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _ADDRSTOR_
#define _ADDRSTOR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200)) /* CE 1.0..199 */

/* CloseAddressBook  [function; ce-only; CE 1.0..199] */
void CloseAddressBook( );

/* FreeAddressCard  [function; ce-only; CE 1.0..199] */
void FreeAddressCard(AddressCard *pac);

/* GetNumberOfAddressCards  [function; ce-only; CE 1.0..199] */
int GetNumberOfAddressCards(void);

/* GetPropertyDataStruct  [function; ce-only; CE 1.0..199] */
int GetPropertyDataStruct(int fFlag, ULONG uValue, PropertyDataStruct *ppds);

/* RecountCards  [function; ce-only; CE 1.0..199] */
void RecountCards();
#endif /* _WIN32_WCE */

#endif /* _ADDRSTOR_ */
