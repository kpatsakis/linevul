SProcXFixesChangeCursorByName(ClientPtr client)
{
    REQUEST(xXFixesChangeCursorByNameReq);

    swaps(&stuff->length);
    REQUEST_AT_LEAST_SIZE(xXFixesChangeCursorByNameReq);
    swapl(&stuff->source);
    swaps(&stuff->nbytes);
    return (*ProcXFixesVector[stuff->xfixesReqType]) (client);
}
