/* Keybddr.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 6 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _KEYBDDR_
#define _KEYBDDR_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213) || (_WIN32_WCE >= 0x300 && _WIN32_WCE < 0x500)) /* CE 2.11..2.12, 3.0..499 */

/* KeybdDriverGetInfo  [function; ce-only; CE 2.11..2.12, 3.0..499; LayoutManager.lib] */
BOOL KeybdDriverGetInfo(
 INT iKeybdId,
 INT iIndex,
 LPVOID lpOutput 
);

/* KeybdDriverPowerHandler  [function; ce-only; CE 2.11..2.12, 3.0..499; LayoutManager.lib] */
void KeybdDriverPowerHandler(
 BOOL bOff 
);

/* KeybdDriverSetMode  [function; ce-only; CE 2.11..2.12, 3.0..499; LayoutManager.lib] */
BOOL KeybdDriverSetMode(
 INT iKeybdId,
 INT iIndex,
 LPVOID lpInput 
);
#endif /* _WIN32_WCE */

#endif /* _KEYBDDR_ */
