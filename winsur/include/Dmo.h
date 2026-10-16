/* Dmo.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 6 constants, 20 declarations, 8 outlines, 0 base types, 0 extra macros, 33 extra decls
 */
#ifndef _DMO_
#define _DMO_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define DMO_E_INVALIDSTREAMINDEX 0x80040201
#define DMO_E_INVALIDTYPE 0x80040202
#define DMO_E_NO_MORE_ITEMS 0x80040206
#define DMO_E_NOTACCEPTING 0x80040204
#define DMO_E_TYPE_NOT_ACCEPTED 0x80040205
#define DMO_E_TYPE_NOT_SET 0x80040203

/* ==================================================================
 * macros -- the macro/#define blocks the pages print (verbatim)
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x500 && _WIN32_WCE < 0x600)) /* CE 5.0..599 */

/* IDMOQualityControl  [interface; shared; CE 5.0..599; Dmoguid.lib] */

/* IDMOVideoOutputOptimizations  [interface; shared; CE 5.0..599; Dmoguid.lib] */

/* IEnumDMO  [interface; shared; CE 5.0..599; Dmoguid.lib] */

/* IMediaBuffer  [interface; shared; CE 5.0..599; Dmoguid.lib] */

/* IMediaObject  [interface; shared; CE 5.0..599; Dmoguid.lib] */

/* IMediaObjectInPlace  [interface; shared; CE 5.0..599; Dmoguid.lib] */
#endif /* _WIN32_WCE */

/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DMO_ENUM_FLAGS  [enum; shared] */
enum DMO_ENUM_FLAGS {
 DMO_ENUMF_INCLUDE_KEYED = 0x00000001
};

/* DMO_INPUT_DATA_BUFFER_FLAGS  [enum; ce-only] */
enum _DMO_INPUT_DATA_BUFFER_FLAGS {
 DMO_INPUT_DATA_BUFFERF_SYNCPOINT = 0x00000001,
 DMO_INPUT_DATA_BUFFERF_TIME = 0x00000002,
 DMO_INPUT_DATA_BUFFERF_TIMELENGTH = 0x00000004
};

/* DMO_INPUT_STREAM_INFO_FLAGS  [enum; ce-only] */
enum _DMO_INPUT_STREAM_INFO_FLAGS {
 DMO_INPUT_STREAMF_WHOLE_SAMPLES = 0x00000001,
 DMO_INPUT_STREAMF_SINGLE_SAMPLE_PER_BUFFER = 0x00000002,
 DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE = 0x00000004,
 DMO_INPUT_STREAMF_HOLDS_BUFFERS = 0x00000008
};

/* DMO_OUTPUT_DATA_BUFFER_FLAGS  [enum; ce-only] */
enum _DMO_OUTPUT_DATA_BUFFER_FLAGS {
 DMO_OUTPUT_DATA_BUFFERF_SYNCPOINT = 0x00000001,
 DMO_OUTPUT_DATA_BUFFERF_TIME = 0x00000002,
 DMO_OUTPUT_DATA_BUFFERF_TIMELENGTH = 0x00000004,
 DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE = 0x01000000
};

/* DMO_OUTPUT_STREAM_INFO_FLAGS  [enum; ce-only] */
enum _DMO_OUTPUT_STREAM_INFO_FLAGS {
 DMO_OUTPUT_STREAMF_WHOLE_SAMPLES = 0x00000001,
 DMO_OUTPUT_STREAMF_SINGLE_SAMPLE_PER_BUFFER = 0x00000002,
 DMO_OUTPUT_STREAMF_FIXED_SAMPLE_SIZE = 0x00000004,
 DMO_OUTPUT_STREAMF_DISCARDABLE = 0x00000008,
 DMO_OUTPUT_STREAMF_OPTIONAL = 0x00000010
};

/* DMO_PROCESS_OUTPUT_FLAGS  [enum; ce-only] */
enum _DMO_PROCESS_OUTPUT_FLAGS {
 DMO_PROCESS_OUTPUT_DISCARD_WHEN_NO_BUFFER = 0x00000001
};

/* DMO_REGISTER_FLAGS  [enum; shared] */
enum DMO_REGISTER_FLAGS {
 DMO_REGISTERF_IS_KEYED = 0x00000001
};

/* DMO_SET_TYPE_FLAGS  [enum; ce-only] */
enum _DMO_SET_TYPE_FLAGS {
 DMO_SET_TYPEF_TEST_ONLY = 0x00000001,
 DMO_SET_TYPEF_CLEAR = 0x00000002
};

/* DMO_VIDEO_OUTPUT_STREAM_FLAGS  [enum; ce-only] */
enum _DMO_VIDEO_OUTPUT_STREAM_FLAGS {
 DMO_VOSF_NEEDS_PREVIOUS_SAMPLE = 0x00000001
};

/* DMO_MEDIA_TYPE  [struct, typedef; shared; Dmoguid.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   majortype */
/*   subtype */
/*   bFixedSizeSamples */
/*   bTemporalCompression */
/*   lSampleSize */
/*   formattype */
/*   pUnk */
/*   cbFormat */
/*   pbFormat */

/* DMO_OUTPUT_DATA_BUFFER  [struct, typedef; shared; Dmoguid.lib] */
/* DERIVED member outline -- documented order, types/offsets not stated */
/*   pBuffer */
/*   dwStatus */
/*   rtTimestamp */
/*   rtTimelength */

/* x00000008  [extra enum] */
enum _DMO_INPUT_STREAM_INFO_FLAGS {
  DMO_INPUT_STREAMF_WHOLE_SAMPLES = 0x00000001,
  DMO_INPUT_STREAMF_SINGLE_SAMPLE_PER_BUFFER = 0x00000002,
  DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE = 0x00000004,
  DMO_INPUT_STREAMF_HOLDS_BUFFERS = 0x00000008
};

/* x01000000  [extra enum] */
enum _DMO_OUTPUT_DATA_BUFFER_FLAGS {
  DMO_OUTPUT_DATA_BUFFERF_SYNCPOINT = 0x00000001,
  DMO_OUTPUT_DATA_BUFFERF_TIME = 0x00000002,
  DMO_OUTPUT_DATA_BUFFERF_TIMELENGTH = 0x00000004,
  DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE = 0x01000000
};

/* x00000010  [extra enum] */
enum _DMO_OUTPUT_STREAM_INFO_FLAGS {
  DMO_OUTPUT_STREAMF_WHOLE_SAMPLES = 0x00000001,
  DMO_OUTPUT_STREAMF_SINGLE_SAMPLE_PER_BUFFER = 0x00000002,
  DMO_OUTPUT_STREAMF_FIXED_SAMPLE_SIZE = 0x00000004,
  DMO_OUTPUT_STREAMF_DISCARDABLE = 0x00000008,
  DMO_OUTPUT_STREAMF_OPTIONAL = 0x00000010
};

/* x00000002  [extra enum] */
enum _DMO_SET_TYPE_FLAGS {  DMO_SET_TYPEF_TEST_ONLY = 0x00000001,  DMO_SET_TYPEF_CLEAR = 0x00000002  };

/* ==================================================================
 * functions and callbacks
 * ================================================================ */

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x400 && _WIN32_WCE < 0x700)) /* CE 4.0..699 */

/* MoCopyMediaType  [function; shared; CE 4.0..699; Msdmo.lib, msdmo.lib] */
HRESULT MoCopyMediaType(
 DMO_MEDIA_TYPE* pmtDest, 
 const DMO_MEDIA_TYPE* pmtSrc
);

/* MoCreateMediaType  [function; shared; CE 4.0..699; Msdmo.lib, msdmo.lib] */
HRESULT MoCreateMediaType(
 DMO_MEDIA_TYPE** ppmt, 
 DWORD cbFormat
);

/* MoDeleteMediaType  [function; shared; CE 4.0..699; Msdmo.lib, msdmo.lib] */
HRESULT MoDeleteMediaType(
 DMO_MEDIA_TYPE* pmt
);

/* MoDuplicateMediaType  [function; shared; CE 4.0..699; Msdmo.lib, msdmo.lib] */
HRESULT MoDuplicateMediaType(
 DMO_MEDIA_TYPE** ppmtDest, 
 const DMO_MEDIA_TYPE* pmtSrc
);

/* MoFreeMediaType  [function; shared; CE 4.0..699; Msdmo.lib, msdmo.lib] */
HRESULT MoFreeMediaType(
 DMO_MEDIA_TYPE* pmt
);

/* MoInitMediaType  [function; shared; CE 4.0..699; Msdmo.lib, msdmo.lib] */
HRESULT MoInitMediaType(
 DMO_MEDIA_TYPE* pmt, 
 DWORD cbFormat
);
#endif /* _WIN32_WCE */

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT AllocateStreamingResources(void);
HRESULT Discontinuity( DWORD dwInputStreamIndex );
HRESULT FreeStreamingResources(void);
HRESULT GetBufferAndLength( BYTE** ppBuffer, DWORD* pcbLength );
HRESULT GetCurrentOperationMode( ULONG ulOutputStreamIndex, DWORD* pdwEnabledFeatures );
HRESULT GetCurrentSampleRequirements( ULONG ulOutputStreamIndex, DWORD* pdwRequestedFeatures );
HRESULT GetInputCurrentType( DWORD dwInputStreamIndex, DMO_MEDIA_TYPE* pmt );
HRESULT GetInputSizeInfo( DWORD dwInputStreamIndex, DWORD* pcbSize, DWORD* pcbMaxLookahead, DWORD* pcbAlignment );
HRESULT GetInputStatus( DWORD dwInputStreamIndex, DWORD* dwFlags );
HRESULT GetInputStreamInfo( DWORD dwInputStreamIndex, DWORD* pdwFlags );
HRESULT GetInputType( DWORD dwInputStreamIndex, DWORD dwTypeIndex, DMO_MEDIA_TYPE* pmt );
HRESULT GetMaxLength( DWORD* pcbMaxLength );
HRESULT GetOutputCurrentType( DWORD dwOutputStreamIndex, DMO_MEDIA_TYPE* pmt );
HRESULT GetOutputSizeInfo( DWORD dwOutputStreamIndex, DWORD* pcbSize, DWORD* pcbAlignment );
HRESULT GetOutputStreamInfo( DWORD dwOutputStreamIndex, DWORD* pdwFlags );
HRESULT GetOutputType( DWORD dwOutputStreamIndex, DWORD dwTypeIndex, DMO_MEDIA_TYPE* pmt );
HRESULT GetStreamCount( DWORD* pcInputStreams, DWORD* pcOutputStreams );
HRESULT ProcessOutput( DWORD dwFlags, DWORD cOutputBufferCount, DMO_OUTPUT_DATA_BUFFER* pOutputBuffers, DWORD* pdwStatus );
HRESULT QueryOperationModePreferences( ULONG ulOutputStreamIndex, DWORD* pdwRequestedCapabilities );
HRESULT SetInputType( DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE* pmt, DWORD dwFlags );
HRESULT SetLength( DWORD cbLength );
HRESULT SetOperationMode( ULONG ulOutputStreamIndex, DWORD dwEnabledFeatures );
HRESULT SetOutputType( DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE* pmt, DWORD dwFlags );
HRESULT SetStatus( DWORD dwFlags );

#endif /* _DMO_ */
