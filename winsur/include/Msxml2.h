/* Msxml2.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 39 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 11 extra decls
 */
#ifndef _MSXML2_
#define _MSXML2_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define COMPLETED 4
#define INTERACTIVE 3
#define LOADED 2
#define LOADING 1
#define NODE_ATTRIBUTE 2
#define NODE_CDATA_SECTION 4
#define NODE_COMMENT 8
#define NODE_DOCUMENT 9
#define NODE_DOCUMENT_FRAGMENT 11
#define NODE_DOCUMENT_TYPE 10
#define NODE_ELEMENT 1
#define NODE_ENTITY 6
#define NODE_ENTITY_REFERENCE 5
#define NODE_NOTATION 12
#define NODE_PROCESSING_INSTRUCTION 7
#define NODE_TEXT 3
#define XML_ATTRIBUTE_FIXED 0xC00CE016L
#define XML_ATTRIBUTE_NOT_DEFINED 0xC00CE015L
#define XML_ATTRIBUTE_VALUE 0xC00CE017L
#define XML_DTD_EXPECTING 0xC00CE026L
#define XML_E_NODTD 0xC00CE224
#define XML_E_NOTWF 0xC00CE223
#define XML_ELEMENT_ID_NOT_FOUND 0xC00CE00EL
#define XML_ELEMENT_NOT_COMPLETE 0xC00CE012L
#define XML_ELEMENT_UNDECLARED 0xC00CE00DL
#define XML_ELEMENT_UNDEFINED 0xC00CE01CL
#define XML_EMPTY_NOT_ALLOWED 0xC00CE011L
#define XML_ENTITY_UNDEFINED 0xC00CE002L
#define XML_EXTENT_IN_ATTR 0xC00CE007L
#define XML_ILLEGAL_TEXT 0xC00CE018L
#define XML_INFINITE_ENTITY_LOOP 0xC00CE003L
#define XML_INVALID_CONTENT 0xC00CE014L
#define XML_MULTI_FIXED_VALUES 0xC00CE019L
#define XML_NDATA_INVALID_PE 0xC00CE004L
#define XML_NDATA_INVALID_REF 0xC00CE006L
#define XML_REQUIRED_ATTRIBUTE_MISSING 0xC00CE020L
#define XML_REQUIRED_NDATA 0xC00CE005L
#define XML_ROOT_NAME_MISMATCH 0xC00CE013L
#define XML_XMLNS_FIXED 0xC00CE01E

/* ==================================================================
 * extra declarations -- corpus pages the main
 * parser did not turn into an entity declaration
 * ================================================================ */

/* function */
HRESULT EndEntity( const wchar_t* pwchName,  int cchName );
HRESULT ParseURL(const wchar_t* pwchUrl);
HRESULT get_length(long* dataLength);
HRESULT get_readyState(long* value);
HRESULT get_responseXML(Idispatch** ppBody);
HRESULT get_status(long* plStatus);
HRESULT put_data(BSTRdata);

#endif /* _MSXML2_ */
