/* camera.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 3 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _CAMERA_
#define _CAMERA_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* BUFFER_COMMANDS  [enum; ce-only] */
typedef enum {
 CS_ALLOCATE,
 CS_ENQUEUE,
 CS_DEALLOCATE
} BUFFER_COMMANDS;
typedef BUFFER_COMMANDS *PBUFFER_COMMANDS, *LPBUFFER_COMMANDS;

/* CSPROPERTY_BUFFER_MODE  [enum; ce-only] */
typedef enum {
 CSPROPERTY_BUFFER_DRIVER = 1,
 CSPROPERTY_BUFFER_CLIENT_LIMITED = 2,
 CSPROPERTY_BUFFER_CLIENT_UNLIMITED = 4
} CSPROPERTY_BUFFER_MODE;
typedef CSPROPERTY_BUFFER_MODE *PCSPROPERTY_BUFFER_MODE, *LPCSPROPERTY_BUFFER_MODE;

#endif /* _CAMERA_ */
