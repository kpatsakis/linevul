VOID NBLSet8021QInfo(PPARANDIS_ADAPTER pContext, PNET_BUFFER_LIST pNBL, PNET_PACKET_INFO pPacketInfo)
{
    NDIS_NET_BUFFER_LIST_8021Q_INFO qInfo;
    qInfo.Value = NULL;

    if (IsPrioritySupported(pContext))
        qInfo.TagHeader.UserPriority = pPacketInfo->Vlan.UserPriority;

    if (IsVlanSupported(pContext))
        qInfo.TagHeader.VlanId = pPacketInfo->Vlan.VlanId;

    if(qInfo.Value != NULL)
        pContext->extraStatistics.framesRxPriority++;

    NET_BUFFER_LIST_INFO(pNBL, Ieee8021QNetBufferListInfo) = qInfo.Value;
}
