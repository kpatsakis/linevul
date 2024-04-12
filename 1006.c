static __inline USHORT CalculateIpPseudoHeaderChecksum(IPHeader *pIpHeader,
                                                       tTcpIpPacketParsingResult res,
                                                       USHORT headerAndPayloadLen)
{
    if (res.ipStatus == ppresIPV4)
        return CalculateIpv4PseudoHeaderChecksum(&pIpHeader->v4, headerAndPayloadLen);
    if (res.ipStatus == ppresIPV6)
        return CalculateIpv6PseudoHeaderChecksum(&pIpHeader->v6, headerAndPayloadLen);
    return 0;
}
