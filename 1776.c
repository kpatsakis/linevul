ProcXvStopVideo(ClientPtr client)
{
    int ret;
    DrawablePtr pDraw;
    XvPortPtr pPort;

    REQUEST(xvStopVideoReq);
    REQUEST_SIZE_MATCH(xvStopVideoReq);

    VALIDATE_XV_PORT(stuff->port, pPort, DixReadAccess);

    ret = dixLookupDrawable(&pDraw, stuff->drawable, client, 0, DixWriteAccess);
    if (ret != Success)
        return ret;

    return XvdiStopVideo(client, pPort, pDraw);
}
