/* physicsengine.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 5 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _PHYSICSENGINE_
#define _PHYSICSENGINE_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define PHYSICSENGINE_BOUNDARY_MODE_BOUNCE 2
#define PHYSICSENGINE_BOUNDARY_MODE_NONE 0
#define PHYSICSENGINE_BOUNDARY_MODE_RUBBERBAND 1
#define PHYSICSENGINE_FLAG_USERTIME 1
#define PHYSICSENGINE_MOVEMENT_MODE_DECELERATE 0

#endif /* _PHYSICSENGINE_ */
