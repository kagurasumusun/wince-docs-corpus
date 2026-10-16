/* Autodial.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 5 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _AUTODIAL_
#define _AUTODIAL_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* AutoDialCleanupModule  [function; ce-only; CE 4.0..699; Autodial.lib] */
DWORD AutoDialCleanupModule(void);

/* AutoDialEndConnection  [function; ce-only; CE 4.0..699; Autodial.lib] */
DWORD AutoDialEndConnection(void);

/* AutoDialInitializeModule  [function; ce-only; CE 4.0..699; Autodial.lib] */
DWORD AutoDialInitializeModule(void);

/* AutoDialStartConnection  [function; ce-only; CE 4.0..699; Autodial.lib] */
DWORD AutoDialStartConnection(
 TCHAR* szUseDialEntry
);
#endif /* _WIN32_WCE */

#endif /* _AUTODIAL_ */
