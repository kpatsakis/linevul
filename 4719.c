ProcXFixesCreateRegionFromWindow(ClientPtr client)
{
    RegionPtr pRegion;
    Bool copy = TRUE;
    WindowPtr pWin;
    int rc;

    REQUEST(xXFixesCreateRegionFromWindowReq);

    REQUEST_SIZE_MATCH(xXFixesCreateRegionFromWindowReq);
    LEGAL_NEW_RESOURCE(stuff->region, client);
    rc = dixLookupResourceByType((void **) &pWin, stuff->window, RT_WINDOW,
                                 client, DixGetAttrAccess);
    if (rc != Success) {
        client->errorValue = stuff->window;
        return rc;
    }
    switch (stuff->kind) {
    case WindowRegionBounding:
        pRegion = wBoundingShape(pWin);
        if (!pRegion) {
            pRegion = CreateBoundingShape(pWin);
            copy = FALSE;
        }
        break;
    case WindowRegionClip:
        pRegion = wClipShape(pWin);
        if (!pRegion) {
            pRegion = CreateClipShape(pWin);
            copy = FALSE;
        }
        break;
    default:
        client->errorValue = stuff->kind;
        return BadValue;
    }
    if (copy && pRegion)
        pRegion = XFixesRegionCopy(pRegion);
    if (!pRegion)
        return BadAlloc;
    if (!AddResource(stuff->region, RegionResType, (void *) pRegion))
        return BadAlloc;

    return Success;
}
