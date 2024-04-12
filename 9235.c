ProcXvQueryImageAttributes(ClientPtr client)
{
    xvQueryImageAttributesReply rep;
    int size, num_planes, i;
    CARD16 width, height;
    XvImagePtr pImage = NULL;
    XvPortPtr pPort;
    int *offsets;
    int *pitches;
    int planeLength;

    REQUEST(xvQueryImageAttributesReq);

    REQUEST_SIZE_MATCH(xvQueryImageAttributesReq);

    VALIDATE_XV_PORT(stuff->port, pPort, DixReadAccess);

    for (i = 0; i < pPort->pAdaptor->nImages; i++) {
        if (pPort->pAdaptor->pImages[i].id == stuff->id) {
            pImage = &(pPort->pAdaptor->pImages[i]);
            break;
        }
    }

#ifdef XvMCExtension
    if (!pImage)
        pImage = XvMCFindXvImage(pPort, stuff->id);
#endif

    if (!pImage)
        return BadMatch;

    num_planes = pImage->num_planes;

    if (!(offsets = malloc(num_planes << 3)))
        return BadAlloc;
    pitches = offsets + num_planes;

    width = stuff->width;
    height = stuff->height;

    size = (*pPort->pAdaptor->ddQueryImageAttributes) (pPort, pImage,
                                                       &width, &height, offsets,
                                                       pitches);

    rep = (xvQueryImageAttributesReply) {
        .type = X_Reply,
        .sequenceNumber = client->sequence,
        .length = planeLength = num_planes << 1,
        .num_planes = num_planes,
        .width = width,
        .height = height,
        .data_size = size
    };

    _WriteQueryImageAttributesReply(client, &rep);
    if (client->swapped)
        SwapLongs((CARD32 *) offsets, planeLength);
    WriteToClient(client, planeLength << 2, offsets);

    free(offsets);

    return Success;
}
