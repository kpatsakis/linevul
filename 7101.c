ProcPseudoramiXQueryScreens(ClientPtr client)
{
    /* REQUEST(xXineramaQueryScreensReq); */
    xXineramaQueryScreensReply rep;

    DEBUG_LOG("noPseudoramiXExtension=%d, pseudoramiXNumScreens=%d\n",
              noPseudoramiXExtension,
              pseudoramiXNumScreens);

    REQUEST_SIZE_MATCH(xXineramaQueryScreensReq);

    rep.type = X_Reply;
    rep.sequenceNumber = client->sequence;
    rep.number = noPseudoramiXExtension ? 0 : pseudoramiXNumScreens;
    rep.length = bytes_to_int32(rep.number * sz_XineramaScreenInfo);
    if (client->swapped) {
        swaps(&rep.sequenceNumber);
        swapl(&rep.length);
        swapl(&rep.number);
    }
    WriteToClient(client, sizeof(xXineramaQueryScreensReply),&rep);

    if (!noPseudoramiXExtension) {
        xXineramaScreenInfo scratch;
        int i;

        for (i = 0; i < pseudoramiXNumScreens; i++) {
            scratch.x_org = pseudoramiXScreens[i].x;
            scratch.y_org = pseudoramiXScreens[i].y;
            scratch.width = pseudoramiXScreens[i].w;
            scratch.height = pseudoramiXScreens[i].h;

            if (client->swapped) {
                swaps(&scratch.x_org);
                swaps(&scratch.y_org);
                swaps(&scratch.width);
                swaps(&scratch.height);
            }
            WriteToClient(client, sz_XineramaScreenInfo,&scratch);
        }
    }

    return Success;
}
