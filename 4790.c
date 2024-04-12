ProcXvPutStill(ClientPtr client)
{
    DrawablePtr pDraw;
    XvPortPtr pPort;
    GCPtr pGC;
    int status;

    REQUEST(xvPutStillReq);
    REQUEST_SIZE_MATCH(xvPutStillReq);

    VALIDATE_DRAWABLE_AND_GC(stuff->drawable, pDraw, DixWriteAccess);
    VALIDATE_XV_PORT(stuff->port, pPort, DixReadAccess);

    if (!(pPort->pAdaptor->type & XvInputMask) ||
        !(pPort->pAdaptor->type & XvStillMask)) {
        client->errorValue = stuff->port;
        return BadMatch;
    }

    status = XvdiMatchPort(pPort, pDraw);
    if (status != Success) {
        return status;
    }

    return XvdiPutStill(client, pDraw, pPort, pGC, stuff->vid_x, stuff->vid_y,
                        stuff->vid_w, stuff->vid_h, stuff->drw_x, stuff->drw_y,
                        stuff->drw_w, stuff->drw_h);
}
