ProcXvGetVideo(ClientPtr client)
{
    DrawablePtr pDraw;
    XvPortPtr pPort;
    GCPtr pGC;
    int status;

    REQUEST(xvGetVideoReq);
    REQUEST_SIZE_MATCH(xvGetVideoReq);

    VALIDATE_DRAWABLE_AND_GC(stuff->drawable, pDraw, DixReadAccess);
    VALIDATE_XV_PORT(stuff->port, pPort, DixReadAccess);

    if (!(pPort->pAdaptor->type & XvOutputMask) ||
        !(pPort->pAdaptor->type & XvVideoMask)) {
        client->errorValue = stuff->port;
        return BadMatch;
    }

    status = XvdiMatchPort(pPort, pDraw);
    if (status != Success) {
        return status;
    }

    return XvdiGetVideo(client, pDraw, pPort, pGC, stuff->vid_x, stuff->vid_y,
                        stuff->vid_w, stuff->vid_h, stuff->drw_x, stuff->drw_y,
                        stuff->drw_w, stuff->drw_h);
}
