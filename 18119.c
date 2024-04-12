SProcRenderCreateSolidFill(ClientPtr client)
{
    REQUEST(xRenderCreateSolidFillReq);
    REQUEST_AT_LEAST_SIZE(xRenderCreateSolidFillReq);

    swaps(&stuff->length);
    swapl(&stuff->pid);
    swaps(&stuff->color.alpha);
    swaps(&stuff->color.red);
    swaps(&stuff->color.green);
    swaps(&stuff->color.blue);
    return (*ProcRenderVector[stuff->renderReqType]) (client);
}
