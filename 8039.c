BOOLEAN AnalyzeL2Hdr(
    PNET_PACKET_INFO packetInfo)
{
    PETH_HEADER dataBuffer = (PETH_HEADER) packetInfo->headersBuffer;

    if (packetInfo->dataLength < ETH_HEADER_SIZE)
        return FALSE;

    packetInfo->ethDestAddr = dataBuffer->DstAddr;

    if (ETH_IS_BROADCAST(dataBuffer))
    {
        packetInfo->isBroadcast = TRUE;
    }
    else if (ETH_IS_MULTICAST(dataBuffer))
    {
        packetInfo->isMulticast = TRUE;
    }
    else
    {
        packetInfo->isUnicast = TRUE;
    }

    if(ETH_HAS_PRIO_HEADER(dataBuffer))
    {
        PVLAN_HEADER vlanHdr = ETH_GET_VLAN_HDR(dataBuffer);

        if(packetInfo->dataLength < ETH_HEADER_SIZE + ETH_PRIORITY_HEADER_SIZE)
            return FALSE;

        packetInfo->hasVlanHeader     = TRUE;
        packetInfo->Vlan.UserPriority = VLAN_GET_USER_PRIORITY(vlanHdr);
        packetInfo->Vlan.VlanId       = VLAN_GET_VLAN_ID(vlanHdr);
        packetInfo->L2HdrLen          = ETH_HEADER_SIZE + ETH_PRIORITY_HEADER_SIZE;
        AnalyzeL3Proto(vlanHdr->EthType, packetInfo);
    }
    else
    {
        packetInfo->L2HdrLen = ETH_HEADER_SIZE;
        AnalyzeL3Proto(dataBuffer->EthType, packetInfo);
    }

    packetInfo->L2PayloadLen = packetInfo->dataLength - packetInfo->L2HdrLen;

    return TRUE;
}
