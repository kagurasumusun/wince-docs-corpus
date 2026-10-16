/* Gpe.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 2 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _GPE_
#define _GPE_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* GPEBltParms  [struct; ce-only] */

/* GPELineParms  [struct; ce-only] */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* GPEMode  [struct; ce-only] */
struct GPEMode {
 int modeId;
 int width;
 int height;
 int Bpp;
 int frequency;
 EGPEFormat format;
};

/* format  [extra struct] */
struct GPEMode {int modeId;int width;int height;int Bpp;int frequency;EGPEFormat format;};

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* ContrastControl  [function; ce-only; CE 6.0..699; Gpe_lib.lib] */
BOOL ContrastControl(
 ULONG cmd,
 ULONG * pValue
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
int NumModes();

#endif /* _GPE_ */
