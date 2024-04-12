PanoramiXRenderSetPictureClipRectangles(ClientPtr client)
{
    REQUEST(xRenderSetPictureClipRectanglesReq);
    int result = Success, j;
    PanoramiXRes *pict;

    REQUEST_AT_LEAST_SIZE(xRenderSetPictureClipRectanglesReq);

    VERIFY_XIN_PICTURE(pict, stuff->picture, client, DixWriteAccess);

    FOR_NSCREENS_BACKWARD(j) {
        stuff->picture = pict->info[j].id;
        result =
            (*PanoramiXSaveRenderVector[X_RenderSetPictureClipRectangles])
            (client);
        if (result != Success)
            break;
    }

    return result;
}
