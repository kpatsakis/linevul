VerifyTcpChecksum(
                tCompletePhysicalAddress *pDataPages,
                ULONG ulDataLength,
                ULONG ulStartOffset,
                tTcpIpPacketParsingResult known,
                ULONG whatToFix)
{
    USHORT  phcs;
    tTcpIpPacketParsingResult res = known;
    IPHeader *pIpHeader = (IPHeader *)RtlOffsetToPointer(pDataPages[0].Virtual, ulStartOffset);
    TCPHeader *pTcpHeader = (TCPHeader *)RtlOffsetToPointer(pIpHeader, res.ipHeaderSize);
    USHORT saved = pTcpHeader->tcp_xsum;
    USHORT xxpHeaderAndPayloadLen = GetXxpHeaderAndPayloadLen(pIpHeader, res);
    if (ulDataLength >= res.ipHeaderSize)
    {
        phcs = CalculateIpPseudoHeaderChecksum(pIpHeader, res, xxpHeaderAndPayloadLen);
        res.xxpCheckSum = CompareNetCheckSumOnEndSystem(phcs, saved) ?  ppresPCSOK : ppresCSBad;
        if (res.xxpCheckSum != ppresPCSOK || whatToFix)
        {
            if (whatToFix & pcrFixPHChecksum)
            {
                if (ulDataLength >= (ULONG)(res.ipHeaderSize + sizeof(*pTcpHeader)))
                {
                    pTcpHeader->tcp_xsum = phcs;
                    res.fixedXxpCS = res.xxpCheckSum != ppresPCSOK;
                }
                else
                    res.xxpStatus = ppresXxpIncomplete;
            }
            else if (res.xxpFull)
            {
                pTcpHeader->tcp_xsum = phcs;
                CalculateTcpChecksumGivenPseudoCS(pTcpHeader, pDataPages, ulStartOffset + res.ipHeaderSize, xxpHeaderAndPayloadLen);
                if (CompareNetCheckSumOnEndSystem(pTcpHeader->tcp_xsum, saved))
                    res.xxpCheckSum = ppresCSOK;

                if (!(whatToFix & pcrFixXxpChecksum))
                    pTcpHeader->tcp_xsum = saved;
                else
                    res.fixedXxpCS =
                        res.xxpCheckSum == ppresCSBad || res.xxpCheckSum == ppresPCSOK;
            }
            else if (whatToFix)
            {
                res.xxpStatus = ppresXxpIncomplete;
            }
        }
        else if (res.xxpFull)
        {
            CalculateTcpChecksumGivenPseudoCS(pTcpHeader, pDataPages, ulStartOffset + res.ipHeaderSize, xxpHeaderAndPayloadLen);
            if (CompareNetCheckSumOnEndSystem(pTcpHeader->tcp_xsum, saved))
                res.xxpCheckSum = ppresCSOK;
            pTcpHeader->tcp_xsum = saved;
        }
    }
    else
        res.ipCheckSum = ppresIPTooShort;
    return res;
}
