/* mcx.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 28 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _MCX_
#define _MCX_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DIALOPTION_BILLING 64
#define DIALOPTION_DIALTONE 256
#define DIALOPTION_QUIET 128
#define MDM_BLIND_DIAL 512
#define MDM_CCITT_OVERRIDE 64
#define MDM_CELLULAR 8
#define MDM_COMPRESSION 1
#define MDM_ERROR_CONTROL 2
#define MDM_FLOWCONTROL_HARD 16
#define MDM_FLOWCONTROL_SOFT 32
#define MDM_FORCED_EC 4
#define MDM_SPEED_ADJUST 128
#define MDM_TONE_DIAL 256
#define MDM_V23_OVERRIDE 1024
#define MDMSPKR_CALLSETUP 3
#define MDMSPKR_DIAL 1
#define MDMSPKR_OFF 0
#define MDMSPKR_ON 2
#define MDMSPKRFLAG_CALLSETUP 8
#define MDMSPKRFLAG_DIAL 2
#define MDMSPKRFLAG_OFF 1
#define MDMSPKRFLAG_ON 4
#define MDMVOL_HIGH 2
#define MDMVOL_LOW 0
#define MDMVOL_MEDIUM 1
#define MDMVOLFLAG_HIGH 4
#define MDMVOLFLAG_LOW 1
#define MDMVOLFLAG_MEDIUM 2

#endif /* _MCX_ */
