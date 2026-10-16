/* Ppcload.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 7 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _PPCLOAD_
#define _PPCLOAD_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x200) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x213)) /* CE 1.0..199, 2.11..2.12 */

/* Load_AlreadyInstalled  [function; ce-only; CE 1.0..199, 2.11..2.12; Ppcload.dll] */
BOOL Load_AlreadyInstalled(LPSTR lpszAppName);

/* Load_Exit  [function; ce-only; CE 1.0..199, 2.11..2.12; Ppcload.dll] */
void Load_Exit(void);

/* Load_PegCpuType  [function; ce-only; CE 1.0..199, 2.11..2.12; Ppcload.dll] */
BOOL Load_PegCpuType(LPSTR lpszCpu);

/* Load_PegFreeSpace  [function; ce-only; CE 1.0..199, 2.11..2.12; Ppcload.dll] */
DWORD Load_PegFreeSpace(void);
#endif /* _WIN32_WCE */

#if defined(_WIN32_WCE) && ((_WIN32_WCE < 0x210) || (_WIN32_WCE >= 0x211 && _WIN32_WCE < 0x400)) /* CE 1.0..209, 2.11..399 */

/* Load  [function; ce-only; CE 1.0..209, 2.11..399; Ppcload.dll] */
Private Sub form_Load( );
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
Private Sub Form_Load( )
Private Sub form_Load( )

#endif /* _PPCLOAD_ */
