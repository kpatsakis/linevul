SProcRenderCreateGlyphSet(ClientPtr client)
{
    REQUEST(xRenderCreateGlyphSetReq);
    REQUEST_SIZE_MATCH(xRenderCreateGlyphSetReq);
    swaps(&stuff->length);
    swapl(&stuff->gsid);
    swapl(&stuff->format);
    return (*ProcRenderVector[stuff->renderReqType]) (client);
}
