/* rpcproxy.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 9 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _RPCPROXY_
#define _RPCPROXY_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define CLSID_PSFACTORYBUFFER extern
#define DLLDATA_STANDARD_ROUTINES DLLDATA_ROUTINES(
#define DLLDUMMYPURECALL void
#define GET_DLL_CLSID (aProxyFileList[0]->pStubVtblList[0]
#define IID_BS_LOOKUP_SETUP int
#define PROXY_CLSID CLSID_PSFactoryBuffer
#define PROXYFILE_LIST_END 0
#define PROXYFILE_LIST_START const
#define STUB_FORWARDING_FUNCTION NdrStubForwardingFunction

#endif /* _RPCPROXY_ */
