/* dmamif.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 0 constants, 26 declarations, 0 outlines, 0 base types, 0 extra macros, 2 extra decls
 */
#ifndef _DMAMIF_
#define _DMAMIF_


/* ==================================================================
 * types -- structures, enumerations and typedefs; the member
 * outlines marked DERIVED below document a structure whose
 * declaration body no page prints
 * ================================================================ */

/* DMA_MDD_TRANFER_CONTEXT  [struct; ce-only] */
typedef struct _DMA_MDD_TRANFER_CONTEXT {
 DWORD m_dwFlags;
 PVOID m_pUserBufferPtr;
 DWORD m_dwUserBufferLength;
 PHYSICAL_ADDRESS m_UserBufferPhAddr;
 PHYSICAL_ADDRESS m_OptionalDeviceAddr;
 BOOL m_fRawTransfer;
 PVOID m_lpInPtr;
 DWORD m_nInLen;
}DMA_MDD_TRANFER_CONTEXT, *PDMA_MDD_TRANFER_CONTEXT;

/* DMA_PDD_ADAPTER_CONTEXT  [struct; ce-only] */
typedef struct _DMA_PDD_ADAPTER_CONTEXT {
 DWORD dwAdapterIndex;
 DWORD dwNumOfChannel;
 DWORD dwNumOfHardwareMappingRegister;
 DWORD dwMaximumSizeOfEachRegister;
 DWORD dwMaximumAddressBoundary;
 DWORD dwAddressAlignment;
 DWORD dwDmaSystemMemoryRangeStart;
 DWORD dwDmaSystemMemoryRangeLength;
 LPGetDmaAdapter lpGetDmaAdapter;
 LPAllocateChannel lpAllocateChannel;
 LPFreeDmaChannel lpFreeDmaChannel;
 LPPowerMgmtCallback lpPowerMgmtCallback;
 LPOALAllocateCommonBuffer lpOALAllocateCommonBuffer;
 LPOALFreeCommoneBuffer lpOALFreeCommonBuffer;
 LPPowerOnReset lpPowerOnReset;
 LPIsChannelSuitable lpIsChannelSuitable;
 LPUpdateFlags lpUpdateFlags;
 LPIsPhysAddrSupported lpIsPhysAddrSupported;
}DMA_PDD_ADAPTER_CONTEXT, *PDMA_PDD_ADAPTER_CONTEXT;

/* DMA_PDD_CHANNEL_CONTEXT  [struct; ce-only] */
typedef struct _DMA_PDD_CHANNEL_CONTEXT {
 LPCanArmDma lpCanArmDma;
 LPArmTransfer lpArmTransfer;
 LPTerminateTransfer lpTerminateTransfer;
 LPStartDmaTransfer lpStartDmaTransfer;
 LPPollingForTransferDone lpPollingForTransferDone;
 LPPollingTransferRemaining lpPollingTransferRemaining;
 LPCreateDmaPDDTransfer lpCreateDmaPDDTransfer;
 LPCreateRawDmaPDDTransfer lpCreateRawDmaPDDTransfer;
 LPFreeDmaTransfer lpFreeDmaTransfer;
}DMA_PDD_CHANNEL_CONTEXT, *PDMA_PDD_CHANNEL_CONTEXT;

/* DMA_PDD_TRANFER_CONTEXT  [struct; ce-only] */
typedef struct _DMA_PDD_TRANFER_CONTEXT {
 LPDMAPDDTransferIoControl lpDMAPDDTransferIoControl;
}DMA_PDD_TRANFER_CONTEXT, *PDMA_PDD_TRANFER_CONTEXT;

#if defined(_WIN32_WCE) && ((_WIN32_WCE >= 0x600 && _WIN32_WCE < 0x700)) /* CE 6.0..699 */

/* LPArmTransfer  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPArmTransfer)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext,
 PDMA_MDD_TRANFER_CONTEXT pDmaMDDTransfer,
 PDMA_PDD_TRANFER_CONTEXT pDmaPDDTransfer
);

/* LPCanArmDMA  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPCanArmDMA)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext
);

/* LPCreateDmaPDDTransfer  [callback; ce-only; CE 6.0..699] */
typedef PDMA_PDD_TRANFER_CONTEXT (* LPCreateDmaPDDTransfer)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext,
 PDMA_MDD_TRANFER_CONTEXT pDmaMddTransferContext
);

/* LPCreateRawDmaPDDTransfer  [callback; ce-only; CE 6.0..699] */
typedef PDMA_PDD_TRANFER_CONTEXT (* LPCreateRawDmaPDDTransfer)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext,
 PDMA_MDD_TRANFER_CONTEXT pDmaMDDTransferContext,
 PVOID lpInPtr,
 DWORD nInLen
);

/* LPDMAPDDTransferIoControl  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPDMAPDDTransferIoControl)(
 PDMA_PDD_TRANFER_CONTEXT pDMAPDDTransferContext,
 DWORD dwIoControl,
 PVOID lpInPtr,
 DWORD nInLen,
 LPVOID lpOutBuffer,
 DWORD nOutBufferSize,
 LPDWORD lpBytesReturned
);

/* LPFreeDmaChannel  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPFreeDmaChannel)(
 PDMA_PDD_ADAPTER_CONTEXT lpAdapterContext,
 PDMA_PDD_CHANNEL_CONTEXT lpPDDChannelContext
);

/* LPFreeDmaTransfer  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPFreeDmaTransfer)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext,
 PDMA_PDD_TRANFER_CONTEXT pDmaContexts
);

/* LPIsPhysAddrSupported  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPIsPhysAddrSupported)(
 PDMA_PDD_ADAPTER_CONTEXT lpPddAdapterContext,
 PHYSICAL_ADDRESS BufferPhysAddress,
 DWORD dwLength
);

/* LPPollingForTransferDone  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPPollingForTransferDone)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext
);

/* LPPollingTransferRemaining  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPPollingTransferRemaining)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext,
 PDMA_MDD_TRANFER_CONTEXT pDmaMDDTransfer,
 PDMA_PDD_TRANFER_CONTEXT pDmaPDDTransfer,
 DWORD *dwRemaining
);

/* LPPowerMgmtCallback  [callback; ce-only; CE 6.0..699] */
typedef void (* LPPowerMgmtCallback)(
 PDMA_PDD_ADAPTER_CONTEXT lpAdapterContext,
 BOOL fOff
);

/* LPPowerOnReset  [callback; ce-only; CE 6.0..699] */
typedef void (* LPPowerOnReset)(
 PDMA_PDD_ADAPTER_CONTEXT lpPddAdapterContext
);

/* LPStartDmaTransfer  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPStartDmaTransfer)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext
);

/* LPTerminateTransfer  [callback; ce-only; CE 6.0..699] */
typedef BOOL (* LPTerminateTransfer)(
 PDMA_PDD_CHANNEL_CONTEXT pDmaPDDChannelContext,
 PDMA_MDD_TRANFER_CONTEXT pDmaMDDTransfer,
 PDMA_PDD_TRANFER_CONTEXT pDmaPDDTransfer
);

/* LPUpdateFlags  [callback; ce-only; CE 6.0..699] */
typedef DWORD (* LPUpdateFlags)(
 PDMA_PDD_ADAPTER_CONTEXT lpPddAdapterContext,
 DWORD dwFlags
);
#endif /* _WIN32_WCE */

#endif /* _DMAMIF_ */
