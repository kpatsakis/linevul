SProcScreenSaverSuspend(ClientPtr client)
{
    REQUEST(xScreenSaverSuspendReq);

    swaps(&stuff->length);
    REQUEST_SIZE_MATCH(xScreenSaverSuspendReq);
    return ProcScreenSaverSuspend(client);
}
