static __inline USHORT CalculateIpv4PseudoHeaderChecksum(IPv4Header *pIpHeader, USHORT headerAndPayloadLen)
{
    tIPv4PseudoHeader ipph;
    USHORT checksum;
    ipph.ipph_src  = pIpHeader->ip_src;
    ipph.ipph_dest = pIpHeader->ip_dest;
    ipph.ipph_zero = 0;
    ipph.ipph_protocol = pIpHeader->ip_protocol;
    ipph.ipph_length = swap_short(headerAndPayloadLen);
    checksum = CheckSumCalculatorFlat(&ipph, sizeof(ipph));
    return ~checksum;
}
