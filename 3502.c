NDIS_STATUS ParaNdis6_ReceivePauseRestart(
    PARANDIS_ADAPTER *pContext,
    BOOLEAN bPause,
    ONPAUSECOMPLETEPROC Callback
    )
{
    NDIS_STATUS status = NDIS_STATUS_SUCCESS;

    if (bPause)
    {
        CNdisPassiveWriteAutoLock tLock(pContext->m_PauseLock);

        ParaNdis_DebugHistory(pContext, hopInternalReceivePause, NULL, 1, 0, 0);
        if (pContext->m_upstreamPacketPending != 0)
        {
            pContext->ReceiveState = srsPausing;
            pContext->ReceivePauseCompletionProc = Callback;
            status = NDIS_STATUS_PENDING;
        }
        else
        {
            ParaNdis_DebugHistory(pContext, hopInternalReceivePause, NULL, 0, 0, 0);
            pContext->ReceiveState = srsDisabled;
        }
    }
    else
    {
        ParaNdis_DebugHistory(pContext, hopInternalReceiveResume, NULL, 0, 0, 0);
        pContext->ReceiveState = srsEnabled;
    }
    return status;
}
