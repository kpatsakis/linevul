ProcXineramaIsActive(ClientPtr client)
{
    /* REQUEST(xXineramaIsActiveReq); */
    xXineramaIsActiveReply rep;

    REQUEST_SIZE_MATCH(xXineramaIsActiveReq);

    rep = (xXineramaIsActiveReply) {
        .type = X_Reply,
        .sequenceNumber = client->sequence,
        .length = 0,
#if 1
        /* The following hack fools clients into thinking that Xinerama
         * is disabled even though it is not. */
        .state = !noPanoramiXExtension && !PanoramiXExtensionDisabledHack
#else
        .state = !noPanoramiXExtension;
#endif
    };
    if (client->swapped) {
        swaps(&rep.sequenceNumber);
        swapl(&rep.length);
        swapl(&rep.state);
    }
    WriteToClient(client, sizeof(xXineramaIsActiveReply), &rep);
    return Success;
}
