ProcXF86DRIGetClientDriverName(register ClientPtr client)
{
    xXF86DRIGetClientDriverNameReply rep = {
        .type = X_Reply,
        .sequenceNumber = client->sequence,
        .clientDriverNameLength = 0
    };
    char *clientDriverName;

    REQUEST(xXF86DRIGetClientDriverNameReq);
    REQUEST_SIZE_MATCH(xXF86DRIGetClientDriverNameReq);
    if (stuff->screen >= screenInfo.numScreens) {
        client->errorValue = stuff->screen;
        return BadValue;
    }

    DRIGetClientDriverName(screenInfo.screens[stuff->screen],
                           (int *) &rep.ddxDriverMajorVersion,
                           (int *) &rep.ddxDriverMinorVersion,
                           (int *) &rep.ddxDriverPatchVersion,
                           &clientDriverName);

    if (clientDriverName)
        rep.clientDriverNameLength = strlen(clientDriverName);
    rep.length = bytes_to_int32(SIZEOF(xXF86DRIGetClientDriverNameReply) -
                                SIZEOF(xGenericReply) +
                                pad_to_int32(rep.clientDriverNameLength));

    WriteToClient(client, sizeof(xXF86DRIGetClientDriverNameReply), &rep);
    if (rep.clientDriverNameLength)
        WriteToClient(client, rep.clientDriverNameLength, clientDriverName);
    return Success;
}
