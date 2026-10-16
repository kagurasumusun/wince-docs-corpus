/* Winddi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 52 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINDDI_
#define _WINDDI_


/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* DisplayInit  [function; ce-only; CE 4.0..699; Ddi_ati_lib.lib, Ddi_flat_lib.lib, Ddi_gx_lib.lib, Ddi_mq200_lib.lib, Ddi_nop_lib.lib, Ddi_perm3_lib.lib, Ddi_rflat_lib.lib, Ddi_rgx_lib.lib, Ddi_tvia5_lib.lib] */
BOOL APIENTRY DisplayInit(
 LPCTSTR pszInstance, 
 DWORD dwNumMonitors
);

/* DrvDisableDriver  [function; shared; CE 4.0..699; Ddi_ati_lib.lib, Ddi_flat_lib.lib, Ddi_gx_lib.lib, Ddi_mq200_lib.lib, Ddi_nop_lib.lib, Ddi_perm3_lib.lib, Ddi_rflat_lib.lib, Ddi_rgx_lib.lib, Ddi_tvia5_lib.lib] */
VOID DrvDisableDriver(VOID);

/* DrvRealizeColor  [function; ce-only; CE 4.0..699; Ddi_ati_lib.lib, Ddi_flat_lib.lib, Ddi_gx_lib.lib, Ddi_mq200_lib.lib, Ddi_nop_lib.lib, Ddi_perm3_lib.lib, Ddi_rflat_lib.lib, Ddi_rgx_lib.lib, Ddi_tvia5_lib.lib] */
ULONG DrvRealizeColor(
 USHORT iDstType,
 ULONG cEntries,
 ULONG* pPalette,
 ULONG rgbColor
);

/* DrvUnrealizeColor  [function; ce-only; CE 4.0..699; Ddi_ati_lib.lib, Ddi_flat_lib.lib, Ddi_gx_lib.lib, Ddi_mq200_lib.lib, Ddi_nop_lib.lib, Ddi_perm3_lib.lib, Ddi_rflat_lib.lib, Ddi_rgx_lib.lib, Ddi_tvia5_lib.lib] */
ULONG APIENTRY DrvUnrealizeColor(
 USHORT iSrcType,
 ULONG cEntries,
 ULONG* pPalette,
 ULONG iRealizedColor
);
#endif /* _WIN32_WCE */

#endif /* _WINDDI_ */
