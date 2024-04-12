ProcXvQueryEncodings(ClientPtr client)
{
    xvEncodingInfo einfo;
    xvQueryEncodingsReply rep;
    int totalSize;
    int nameSize;
    XvPortPtr pPort;
    int ne;
    XvEncodingPtr pe;

    REQUEST(xvQueryEncodingsReq);
    REQUEST_SIZE_MATCH(xvQueryEncodingsReq);

    VALIDATE_XV_PORT(stuff->port, pPort, DixReadAccess);

    rep = (xvQueryEncodingsReply) {
        .type = X_Reply,
        .sequenceNumber = client->sequence,
        .num_encodings = pPort->pAdaptor->nEncodings
    };

    /* FOR EACH ENCODING ADD UP THE BYTES FOR ENCODING NAMES */

    ne = pPort->pAdaptor->nEncodings;
    pe = pPort->pAdaptor->pEncodings;
    totalSize = ne * sz_xvEncodingInfo;
    while (ne--) {
        totalSize += pad_to_int32(strlen(pe->name));
        pe++;
    }

    rep.length = bytes_to_int32(totalSize);

    _WriteQueryEncodingsReply(client, &rep);

    ne = pPort->pAdaptor->nEncodings;
    pe = pPort->pAdaptor->pEncodings;
    while (ne--) {
        einfo.encoding = pe->id;
        einfo.name_size = nameSize = strlen(pe->name);
        einfo.width = pe->width;
        einfo.height = pe->height;
        einfo.rate.numerator = pe->rate.numerator;
        einfo.rate.denominator = pe->rate.denominator;
        _WriteEncodingInfo(client, &einfo);
        WriteToClient(client, nameSize, pe->name);
        pe++;
    }

    return Success;
}
