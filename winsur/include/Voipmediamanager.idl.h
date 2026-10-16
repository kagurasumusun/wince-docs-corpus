/* Voipmediamanager.idl -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 1 constants, 1 declarations, 0 outlines, 0 base types, 0 extra macros, 11 extra decls
 */
#ifndef _VOIPMEDIAMANAGER_IDL_
#define _VOIPMEDIAMANAGER_IDL_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define e_vptInvalid 0

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* VoIPProgressTone  [enum; ce-only] */
typedef enum VoIPProgressTone { 
 e_vptInvalid = 0, 
 e_vptDial, 
 e_vptStutter, 
 e_vptOffHookWarning, 
 e_vptConfirmation, 
 e_vptMessageWaiting, 
 e_vptRingback, 
 e_vptCallWaiting, 
 e_vptReorder, 
 e_vptCongestion, 
 e_vptClientBusy, 
 e_vptNetworkBusy 
} VoIPProgressTone;
typedef VoIPProgressTone *PVoIPProgressTone, *LPVoIPProgressTone;

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT PlayProgressTone( VoIPProgressTone vpt );
HRESULT StopProgressTone();
HRESULT StopSound();
HRESULT get_MicrophoneVolume( float* pfpVolume );
HRESULT get_SpeakerVolume( float* pfpVolume );
HRESULT put_MicrophoneVolume( float fpVolume );
HRESULT put_SpeakerVolume( float fpVolume );

#endif /* _VOIPMEDIAMANAGER_IDL_ */
