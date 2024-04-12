static NDIS_STATUS SetupDPCTarget(PARANDIS_ADAPTER *pContext)
{
    ULONG i;
#if NDIS_SUPPORT_NDIS620
    NDIS_STATUS status;
    PROCESSOR_NUMBER procNumber;
#endif

    for (i = 0; i < pContext->nPathBundles; i++)
    {
#if NDIS_SUPPORT_NDIS620
        status = KeGetProcessorNumberFromIndex(i, &procNumber);
        if (status != NDIS_STATUS_SUCCESS)
        {
            DPrintf(0, ("[%s] - KeGetProcessorNumberFromIndex failed for index %lu - %d\n", __FUNCTION__, i, status));
            return status;
        }
        ParaNdis_ProcessorNumberToGroupAffinity(&pContext->pPathBundles[i].rxPath.DPCAffinity, &procNumber);
        pContext->pPathBundles[i].txPath.DPCAffinity = pContext->pPathBundles[i].rxPath.DPCAffinity;
#elif NDIS_SUPPORT_NDIS6
        pContext->pPathBundles[i].rxPath.DPCTargetProcessor = 1i64 << i;
        pContext->pPathBundles[i].txPath.DPCTargetProcessor = pContext->pPathBundles[i].rxPath.DPCTargetProcessor;
#else
#error not supported
#endif
    }

#if NDIS_SUPPORT_NDIS620
    pContext->CXPath.DPCAffinity = pContext->pPathBundles[0].rxPath.DPCAffinity;
#elif NDIS_SUPPORT_NDIS6
    pContext->CXPath.DPCTargetProcessor = pContext->pPathBundles[0].rxPath.DPCTargetProcessor;
#else
#error not yet defined
#endif
    return NDIS_STATUS_SUCCESS;
}
