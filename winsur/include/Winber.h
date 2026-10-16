/* Winber.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 4 constants, 11 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINBER_
#define _WINBER_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define LBER_DEFAULT ((ber_tag_t)-1)
#define LBER_ERROR ((ber_tag_t)-1)
#define LBER_USE_DER 0x01
#define WINBERAPI DECLSPEC_IMPORT

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* ber_alloc_t  [function; shared; CE 4.0..699; Wldap32.lib, wldap32.lib] */
BerElement* ber_alloc_t(
 INT iOptions
);

/* ber_first_element  [function; shared; CE 4.0..699; Wldap32.lib, wldap32.lib] */
ULONG ber_first_element(
 BerElement* pBerElement,
 ULONG* pLen,
 CHAR** ppOpaque
);

/* ber_free  [function; shared; CE 4.0..699; Wldap32.lib, wldap32.lib] */
void ber_free(
 BerElement* pBerElement,
 INT fbuf
);

/* ber_next_element  [function; shared; CE 4.0..699; Wldap32.lib, wldap32.lib] */
ULONG ber_next_element(
 BerElement* pBerElement,
 ULONG* pLen,
 CHAR* pOpaque
);

/* ber_peek_tag  [function; shared; CE 4.0..699; Wldap32.lib, wldap32.lib] */
ULONG ber_peek_tag(
 BerElement* pBerElement,
 ULONG* pLen
);

/* ber_skip_tag  [function; shared; CE 4.0..699; Wldap32.lib, wldap32.lib] */
ULONG ber_skip_tag(
 BerElement* pBerElement,
 ULONG* pLen
);
#endif /* _WIN32_WCE */

#endif /* _WINBER_ */
