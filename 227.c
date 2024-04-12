static BOOLEAN CheckRunningDpc(PARANDIS_ADAPTER *pContext)
{
    BOOLEAN bStopped;
    BOOLEAN bReportHang = FALSE;
    bStopped = 0 != InterlockedExchange(&pContext->bDPCInactive, TRUE);

    if (bStopped)
    {
        pContext->nDetectedInactivity++;
    }
    else
    {
        pContext->nDetectedInactivity = 0;
    }

    for (UINT i = 0; i < pContext->nPathBundles; i++)
    {
        if (pContext->pPathBundles[i].txPath.HasHWBuffersIsUse())
        {
            if (pContext->nDetectedStoppedTx++ > 1)
            {
                DPrintf(0, ("[%s] - Suspicious Tx inactivity (%d)!\n", __FUNCTION__, pContext->pPathBundles[i].txPath.GetFreeHWBuffers()));
#ifdef DBG_USE_VIRTIO_PCI_ISR_FOR_HOST_REPORT
                WriteVirtIODeviceByte(pContext->IODevice->addr + VIRTIO_PCI_ISR, 0);
#endif
                break;
            }
        }
    }

    if (pContext->Limits.nPrintDiagnostic &&
        ++pContext->Counters.nPrintDiagnostic >= pContext->Limits.nPrintDiagnostic)
    {
        pContext->Counters.nPrintDiagnostic = 0;
        PrintStatistics(pContext);
    }

    if (pContext->Statistics.ifHCInOctets == pContext->Counters.prevIn)
    {
        pContext->Counters.nRxInactivity++;
        if (pContext->Counters.nRxInactivity >= 10)
        {
#if defined(CRASH_ON_NO_RX)
            ONPAUSECOMPLETEPROC proc = (ONPAUSECOMPLETEPROC)(PVOID)1;
            proc(pContext);
#endif
        }
    }
    else
    {
        pContext->Counters.nRxInactivity = 0;
        pContext->Counters.prevIn = pContext->Statistics.ifHCInOctets;
    }
    return bReportHang;
}
