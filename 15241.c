ProcXvUngrabPort(ClientPtr client)
{
    XvPortPtr pPort;

    REQUEST(xvGrabPortReq);
    REQUEST_SIZE_MATCH(xvGrabPortReq);

    VALIDATE_XV_PORT(stuff->port, pPort, DixReadAccess);

    return XvdiUngrabPort(client, pPort, stuff->time);
}
