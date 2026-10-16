/* Hidpi.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 38 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _HIDPI_
#define _HIDPI_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* HIDP_DATA  [struct; ce-only] */
typedef struct _HIDP_DATA {
 USHORT DataIndex;
 USHORT Reserved;
 union {
 ULONG RawValue;
 BOOLEAN On;
 };
} HIDP_DATA, * PHIDP_DATA;

/* HIDP_EXTENDED_ATTRIBUTES  [struct; ce-only] */
typedef struct _HIDP_EXTENDED_ATTRIBUTES {
 UCHAR NumGlobalUnknowns;
 UCHAR Reserved[3];
 PHIDP_UNKNOWN_TOKEN GlobalUnknowns;
 ULONG Data[1];
} HIDP_EXTENDED_ATTRIBUTES, * PHIDP_EXTENDED_ATTRIBUTES;

/* HIDP_KEYBOARD_DIRECTION  [enum; ce-only] */
typedef enum _HIDP_KEYBOARD_DIRECTION {
 HidP_Keyboard_Break,
 HidP_Keyboard_Make
} HIDP_KEYBOARD_DIRECTION;
typedef HIDP_KEYBOARD_DIRECTION *PHIDP_KEYBOARD_DIRECTION, *LPHIDP_KEYBOARD_DIRECTION;

/* HIDP_REPORT_TYPE  [enum; ce-only] */
typedef enum _HIDP_REPORT_TYPE {
 HidP_Input,
 HidP_Output,
 HidP_Feature
} HIDP_REPORT_TYPE;
typedef HIDP_REPORT_TYPE *PHIDP_REPORT_TYPE, *LPHIDP_REPORT_TYPE;

/* HIDP_UNKNOWN_TOKEN  [struct; ce-only] */
typedef struct _HIDP_UNKNOWN_TOKEN {
 UCHAR Token;
 UCHAR Reserved[3];
 ULONG BitField;
} HIDP_UNKNOWN_TOKEN, * PHIDP_UNKNOWN_TOKEN;

#endif /* _HIDPI_ */
