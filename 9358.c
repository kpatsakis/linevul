BOOLEAN AnalyzeIP6RoutingExtension(
    PIP6_TYPE2_ROUTING_HEADER routingHdr,
    ULONG dataLength,
    IPV6_ADDRESS **destAddr)
{
    if(dataLength < sizeof(*routingHdr))
        return FALSE;
    if(routingHdr->RoutingType == 2)
    {
        if((dataLength != sizeof(*routingHdr)) || (routingHdr->SegmentsLeft != 1))
            return FALSE;

        *destAddr = &routingHdr->Address;
    }
    else *destAddr = NULL;

    return TRUE;
}
