bool CNB::ScheduleBuildSGListForTx()
{
    ASSERT(KeGetCurrentIrql() == DISPATCH_LEVEL);

    return NdisMAllocateNetBufferSGList(m_Context->DmaHandle, m_NB, this,
                                        NDIS_SG_LIST_WRITE_TO_DEVICE, nullptr, 0) == NDIS_STATUS_SUCCESS;
}
