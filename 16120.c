ProcXvQueryExtension(ClientPtr client)
{
    xvQueryExtensionReply rep = {
        .type = X_Reply,
        .sequenceNumber = client->sequence,
        .length = 0,
        .version = XvVersion,
        .revision = XvRevision
    };

    /* REQUEST(xvQueryExtensionReq); */
    REQUEST_SIZE_MATCH(xvQueryExtensionReq);

    _WriteQueryExtensionReply(client, &rep);

    return Success;
}
