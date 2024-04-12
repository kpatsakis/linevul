NDIS_STATUS ParaNdis_FinishSpecificInitialization(PARANDIS_ADAPTER *pContext)
{
    NDIS_STATUS status = NDIS_STATUS_SUCCESS;
    NET_BUFFER_LIST_POOL_PARAMETERS PoolParams;
    NDIS_MINIPORT_INTERRUPT_CHARACTERISTICS mic;
    DEBUG_ENTRY(0);

    NdisZeroMemory(&mic, sizeof(mic));
    mic.Header.Type = NDIS_OBJECT_TYPE_MINIPORT_INTERRUPT;
    mic.Header.Revision = NDIS_MINIPORT_INTERRUPT_REVISION_1;
    mic.Header.Size = NDIS_SIZEOF_MINIPORT_INTERRUPT_CHARACTERISTICS_REVISION_1;
    mic.DisableInterruptHandler = MiniportDisableInterruptEx;
    mic.EnableInterruptHandler  = MiniportEnableInterruptEx;
    mic.InterruptDpcHandler = MiniportInterruptDPC;
    mic.InterruptHandler = MiniportInterrupt;
    if (pContext->bUsingMSIX)
    {
        mic.MsiSupported = TRUE;
        mic.MsiSyncWithAllMessages = TRUE;
        mic.EnableMessageInterruptHandler = MiniportEnableMSIInterrupt;
        mic.DisableMessageInterruptHandler = MiniportDisableMSIInterrupt;
        mic.MessageInterruptHandler = MiniportMSIInterrupt;
        mic.MessageInterruptDpcHandler = MiniportMSIInterruptDpc;
    }
    PoolParams.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
    PoolParams.Header.Size = sizeof(PoolParams);
    PoolParams.Header.Revision = NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1;
    PoolParams.ProtocolId = NDIS_PROTOCOL_ID_DEFAULT;
    PoolParams.fAllocateNetBuffer = TRUE;
    PoolParams.ContextSize = 0;
    PoolParams.PoolTag = PARANDIS_MEMORY_TAG;
    PoolParams.DataSize = 0;

    pContext->BufferListsPool = NdisAllocateNetBufferListPool(pContext->MiniportHandle, &PoolParams);
    if (!pContext->BufferListsPool)
    {
        status = NDIS_STATUS_RESOURCES;
    }

    if (status == NDIS_STATUS_SUCCESS)
    {
        status = NdisMRegisterInterruptEx(pContext->MiniportHandle, pContext, &mic, &pContext->InterruptHandle);
    }

#ifdef DBG
    if (pContext->bUsingMSIX)
    {
        DPrintf(0, ("[%s] MSIX message table %savailable, count = %u\n", __FUNCTION__, (mic.MessageInfoTable == nullptr ? "not " : ""),
            (mic.MessageInfoTable == nullptr ? 0 : mic.MessageInfoTable->MessageCount)));
    }
    else
    {
        DPrintf(0, ("[%s] Not using MSIX\n", __FUNCTION__));
    }
#endif

    if (status == NDIS_STATUS_SUCCESS)
    {
        NDIS_SG_DMA_DESCRIPTION sgDesc;
        sgDesc.Header.Type = NDIS_OBJECT_TYPE_SG_DMA_DESCRIPTION;
        sgDesc.Header.Revision = NDIS_SG_DMA_DESCRIPTION_REVISION_1;
        sgDesc.Header.Size = sizeof(sgDesc);
        sgDesc.Flags = NDIS_SG_DMA_64_BIT_ADDRESS;
        sgDesc.MaximumPhysicalMapping = 0x10000; // 64K
        sgDesc.ProcessSGListHandler = ProcessSGListHandler;
        sgDesc.SharedMemAllocateCompleteHandler = SharedMemAllocateCompleteHandler;
        sgDesc.ScatterGatherListSize = 0; // OUT value
        status = NdisMRegisterScatterGatherDma(pContext->MiniportHandle, &sgDesc, &pContext->DmaHandle);
        if (status != NDIS_STATUS_SUCCESS)
        {
            DPrintf(0, ("[%s] ERROR: NdisMRegisterScatterGatherDma failed (%X)!\n", __FUNCTION__, status));
        }
        else
        {
            DPrintf(0, ("[%s] SG recommended size %d\n", __FUNCTION__, sgDesc.ScatterGatherListSize));
        }
    }

    if (status == NDIS_STATUS_SUCCESS)
    {
        if (NDIS_CONNECT_MESSAGE_BASED == mic.InterruptType)
        {
            pContext->pMSIXInfoTable = mic.MessageInfoTable;
        }
        else if (pContext->bUsingMSIX)
        {
            DPrintf(0, ("[%s] ERROR: Interrupt type %d, message table %p\n",
                __FUNCTION__, mic.InterruptType, mic.MessageInfoTable));
            status = NDIS_STATUS_RESOURCE_CONFLICT;
        }
        ParaNdis6_ApplyOffloadPersistentConfiguration(pContext);
        DebugParseOffloadBits();
    }
    DEBUG_EXIT_STATUS(0, status);
    return status;
}
