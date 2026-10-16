/* dsclient.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 40 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _DSCLIENT_
#define _DSCLIENT_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DSB_MAX_DISPLAYNAME_CHARS 64
#define DSBF_DISPLAYNAME 0x00000004
#define DSBF_ICONLOCATION 0x00000002
#define DSBF_STATE 0x00000001
#define DSBI_CHECKBOXES 0x00000100
#define DSBI_DONTSIGNSEAL 0x02000000
#define DSBI_ENTIREDIRECTORY 0x00090000
#define DSBI_EXPANDONOPEN 0x00040000
#define DSBI_HASCREDENTIALS 0x00200000
#define DSBI_IGNORETREATASLEAF 0x00400000
#define DSBI_INCLUDEHIDDEN 0x00020000
#define DSBI_NOBUTTONS 0x00000001
#define DSBI_NOLINES 0x00000002
#define DSBI_NOLINESATROOT 0x00000004
#define DSBI_NOROOT 0x00010000
#define DSBI_RETURN_FORMAT 0x00100000
#define DSBI_RETURNOBJECTCLASS 0x01000000
#define DSBI_SIMPLEAUTHENTICATE 0x00800000
#define DSBM_CHANGEIMAGESTATE 0x0066
#define DSBM_CONTEXTMENU 0x0068
#define DSBM_HELP 0x0067
#define DSBM_QUERYINSERT DSBM_QUERYINSERTW
#define DSBM_QUERYINSERTA 0x0065
#define DSBM_QUERYINSERTW 0x0064
#define DSBS_CHECKED 0x00000001
#define DSBS_HIDDEN 0x00000002
#define DSBS_ROOT 0x00000004
#define DSCCIF_HASWIZARDDIALOG 0x00000001
#define DSCCIF_HASWIZARDPRIMARYPAGE 0x00000002
#define DSDSOF_DONTSIGNSEAL 0x00000004
#define DSDSOF_DSAVAILABLE 0x40000000
#define DSDSOF_HASUSERANDSERVERINFO 0x00000001
#define DSDSOF_SIMPLEAUTHENTICATE 0x00000002
#define DSOBJECT_ISCONTAINER 0x00000001
#define DSOBJECT_READONLYPAGES 0x80000000
#define DSPROVIDER_ADVANCED 0x00000010
#define DSPROVIDER_UNUSED_0 0x00000001
#define DSPROVIDER_UNUSED_1 0x00000002
#define DSPROVIDER_UNUSED_2 0x00000004
#define DSPROVIDER_UNUSED_3 0x00000008

#endif /* _DSCLIENT_ */
