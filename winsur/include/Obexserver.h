/* Obexserver.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 4 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _OBEXSERVER_
#define _OBEXSERVER_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* OBEXCOMMAND  [struct; ce-only] */
typedef struct _obex_command {
 unsigned int uiOp;
 unsigned int uiResp;
 unsigned int fFinal;
 ObexPacketData sPktData;
 unsigned int cProp;
 unsigned int * aPropID;
 ObexVariant * aPropVar;
} ObexCommand;

/* OBEXTRANSACTION  [struct; ce-only] */
typedef struct _obex_transaction {
 unsigned int uiConnectionId;
 unsigned int uiTransactionId;
 unsigned int uiOp;
 ObexCommand * pObex;
 MemAlloc ObexAlloc;
 MemFree ObexFree;
 ServerCallback ObexExecute;
} ObexTransaction;

/* ServerCallback  [struct; ce-only] */
typedef int (*ServerCallback)(
 unsigned int uiOp,
 unsigned int uiId,
 struct _obex_command * pCommand 
);

/* ServiceCallback  [struct; ce-only] */
typedef int (*ServiceCallback)(
 struct _obex_transaction * pTrans 
);

/* pCommand  [extra struct] */
typedef int (*ServerCallback)(unsigned int uiOp, unsigned int uiId, struct _obex_command * pCommand);

/* pTrans  [extra struct] */
typedef int (*ServiceCallback)(struct _obex_transaction * pTrans);

#endif /* _OBEXSERVER_ */
