/* cs.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 32 declarations, 0 outlines, 0 base types, 0 extra macros, 1 extra decls
 */
#ifndef _CS_
#define _CS_


/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

/* DEFINE_CSPROPERTY_ITEM  [macro; ce-only] */
#define DEFINE_CSPROPERTY_ITEM(PropertyId, GetHandler,\
 MinProperty, MinData,\
 SetHandler, Values,\
 RelationsCount, Relations,\
 SupportHandler, SerializedSize)\
{\
 PropertyId, (BOOL)GetHandler,\
 MinProperty, MinData,\
 (BOOL)SetHandler, (PCSPROPERTY_VALUES)Values,\
 RelationsCount, (PCSPROPERTY)Relations,\
 NULL, 0\
}

/* DEFINE_CSPROPERTY_SET  [macro; ce-only] */
#define DEFINE_CSPROPERTY_SET(Set,\
 PropertiesCount,\
 PropertyItem,\
 FastIoCount,\
 FastIoTable)\
{\
 Set,\
 PropertiesCount,\
 PropertyItem,\
 FastIoCount,\
 FastIoTable\
}

/* DEFINE_CSPROPERTY_SET_TABLE  [macro; ce-only] */
#define DEFINE_CSPROPERTY_SET_TABLE(tablename) \
 const CSPROPERTY_SET tablename[] =

/* DEFINE_CSPROPERTY_TABLE  [macro; ce-only] */
#define DEFINE_CSPROPERTY_TABLE(tablename)\
 const CSPROPERTY_ITEM tablename[] =

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* CS_COMPRESSION  [struct; ce-only] */
typedef struct {
 ULONG RatioNumerator;
 ULONG RatioDenominator; 
 ULONG RatioConstantMargin;
} CS_COMPRESSION, *PCS_COMPRESSION;

/* CS_FRAMING_RANGE  [struct; ce-only] */
typedef struct {
 ULONG MinFrameSize;
 ULONG MaxFrameSize;
 ULONG Stepping;
} CS_FRAMING_RANGE, *PCS_FRAMING_RANGE;

/* CS_FRAMING_RANGE_WEIGHTED  [struct; ce-only] */
typedef struct {
 CS_FRAMING_RANGE Range;
 ULONG InPlaceWeight;
 ULONG NotInPlaceWeight;
} CS_FRAMING_RANGE_WEIGHTED, *PCS_FRAMING_RANGE_WEIGHTED;

/* CSALLOCATOR_FRAMING  [struct; ce-only] */
typedef struct {
 union {
 ULONG OptionsFlags;
 ULONG RequirementsFlags;
 };
 ULONG PoolType;
 ULONG Frames;
 ULONG FrameSize;
 ULONG FileAlignment;
 ULONG Reserved;
} CSALLOCATOR_FRAMING, *PCSALLOCATOR_FRAMING;

/* CSMULTIPLE_ITEM  [struct; ce-only] */
typedef struct {
 ULONG Size;
 ULONG Count;
} CSMULTIPLE_ITEM, *PCSMULTIPLE_ITEM;

/* CSPIN_CINSTANCES  [struct; ce-only] */
typedef struct {
 ULONG PossibleCount;
 ULONG CurrentCount;
} CSPIN_CINSTANCES, *PCSPIN_CINSTANCES;

/* CSPROPERTY_BOUNDS_LONG  [struct; ce-only] */
typedef union {
 struct _SIGNED {
 LONG SignedMinimum;
 LONG SignedMaximum;
 };
 struct _UNSIGNED {
 ULONG UnsignedMinimum;
 ULONG UnsignedMaximum;
 };
} CSPROPERTY_BOUNDS_LONG, *PCSPROPERTY_BOUNDS_LONG;

/* CSPROPERTY_CONNECTION  [enum; ce-only] */
typedef enum {
 CSPROPERTY_CONNECTION_STATE,
 CSPROPERTY_CONNECTION_DATAFORMAT,
 CSPROPERTY_CONNECTION_ALLOCATORFRAMING,
 CSPROPERTY_CONNECTION_PROPOSEDATAFORMAT,
 CSPROPERTY_CONNECTION_ALLOCATORFRAMING_EX
} CSPROPERTY_CONNECTION;
typedef CSPROPERTY_CONNECTION *PCSPROPERTY_CONNECTION, *LPCSPROPERTY_CONNECTION;

/* CSPROPERTY_MEMBERSHEADER  [struct; ce-only] */
typedef struct {
 ULONG MembersFlags;
 ULONG MembersSize;
 ULONG MembersCount;
 ULONG Flags;
} CSPROPERTY_MEMBERSHEADER, *PCSPROPERTY_MEMBERSHEADER;

/* CSPROPERTY_MEMBERSLIST  [struct; ce-only] */
typedef struct {
 CSPROPERTY_MEMBERSHEADER MembersHeader;
 const VOID* Members;
} CSPROPERTY_MEMBERSLIST, *PCSPROPERTY_MEMBERSLIST;

/* CSPROPERTY_PIN  [enum; ce-only] */
typedef enum {
 CSPROPERTY_PIN_CINSTANCES = 0,
 CSPROPERTY_PIN_CTYPES,
 CSPROPERTY_PIN_DATARANGES,
 CSPROPERTY_PIN_DATAINTERSECTION,
 CSPROPERTY_PIN_CATEGORY,
 CSPROPERTY_PIN_NAME,
} CSPROPERTY_PIN;
typedef CSPROPERTY_PIN *PCSPROPERTY_PIN, *LPCSPROPERTY_PIN;

/* CSPROPERTY_STEPPING_LONG  [struct; ce-only] */
typedef struct {
 ULONG SteppingDelta;
 ULONG Reserved;
 CSPROPERTY_BOUNDS_LONG Bounds;
} CSPROPERTY_STEPPING_LONG, *PCSPROPERTY_STEPPING_LONG;

/* CSSTATE  [enum; ce-only] */
typedef enum {
 CSSTATE_STOP,
 CSSTATE_PAUSE,
 CSSTATE_RUN
} CSSTATE, *PCSSTATE;

/* CSTIME  [struct; ce-only] */
typedef struct {
 LONGLONG Time;
 ULONG Numerator;
 ULONG Denominator;
} CSTIME, *PCSTIME;

/* CSSTREAM_HEADER  [struct; ce-only] */
typedef struct {
 ULONG Size;
 ULONG TypeSpecificFlags;
 CSTIME PresentationTime;
 LONGLONG Duration;
 ULONG FrameExtent;
 ULONG DataUsed;
 PVOID Data;
 ULONG OptionsFlags;
} CSSTREAM_HEADER, *PCSSTREAM_HEADER;

#endif /* _CS_ */
