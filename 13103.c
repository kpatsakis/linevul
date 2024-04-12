ProcPanoramiXQueryVersion(ClientPtr client)
{
    /* REQUEST(xPanoramiXQueryVersionReq); */
    xPanoramiXQueryVersionReply rep = {
        .type = X_Reply,
        .sequenceNumber = client->sequence,
        .length = 0,
        .majorVersion = SERVER_PANORAMIX_MAJOR_VERSION,
        .minorVersion = SERVER_PANORAMIX_MINOR_VERSION
    };

    REQUEST_SIZE_MATCH(xPanoramiXQueryVersionReq);
    if (client->swapped) {
        swaps(&rep.sequenceNumber);
        swapl(&rep.length);
        swaps(&rep.majorVersion);
        swaps(&rep.minorVersion);
    }
    WriteToClient(client, sizeof(xPanoramiXQueryVersionReply), &rep);
    return Success;
}
