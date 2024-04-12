CCHAR GetReceiveQueueForCurrentCPU(PARANDIS_ADAPTER *pContext)
{
#if PARANDIS_SUPPORT_RSS
    return ParaNdis6_RSSGetCurrentCpuReceiveQueue(&pContext->RSSParameters);
#else
    UNREFERENCED_PARAMETER(pContext);

    return PARANDIS_RECEIVE_QUEUE_UNCLASSIFIED;
#endif
}
