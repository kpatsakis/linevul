DGACreateColormap(int index, ClientPtr client, int id, int mode, int alloc)
{
    ScreenPtr pScreen = screenInfo.screens[index];
    DGAScreenPtr pScreenPriv = DGA_GET_SCREEN_PRIV(pScreen);
    FakedVisualList *fvlp;
    VisualPtr pVisual;
    DGAModePtr pMode;
    ColormapPtr pmap;

    if (!mode || (mode > pScreenPriv->numModes))
        return BadValue;

    if ((alloc != AllocNone) && (alloc != AllocAll))
        return BadValue;

    pMode = &(pScreenPriv->modes[mode - 1]);

    if (!(pVisual = malloc(sizeof(VisualRec))))
        return BadAlloc;

    pVisual->vid = FakeClientID(0);
    pVisual->class = pMode->visualClass;
    pVisual->nplanes = pMode->depth;
    pVisual->ColormapEntries = 1 << pMode->depth;
    pVisual->bitsPerRGBValue = (pMode->depth + 2) / 3;

    switch (pVisual->class) {
    case PseudoColor:
    case GrayScale:
    case StaticGray:
        pVisual->bitsPerRGBValue = 8;   /* not quite */
        pVisual->redMask = 0;
        pVisual->greenMask = 0;
        pVisual->blueMask = 0;
        pVisual->offsetRed = 0;
        pVisual->offsetGreen = 0;
        pVisual->offsetBlue = 0;
        break;
    case DirectColor:
    case TrueColor:
        pVisual->ColormapEntries = 1 << pVisual->bitsPerRGBValue;
        /* fall through */
    case StaticColor:
        pVisual->redMask = pMode->red_mask;
        pVisual->greenMask = pMode->green_mask;
        pVisual->blueMask = pMode->blue_mask;
        pVisual->offsetRed = BitsClear(pVisual->redMask);
        pVisual->offsetGreen = BitsClear(pVisual->greenMask);
        pVisual->offsetBlue = BitsClear(pVisual->blueMask);
    }

    if (!(fvlp = malloc(sizeof(FakedVisualList)))) {
        free(pVisual);
        return BadAlloc;
    }

    fvlp->free = FALSE;
    fvlp->pVisual = pVisual;
    fvlp->next = pScreenPriv->fakedVisuals;
    pScreenPriv->fakedVisuals = fvlp;

    LEGAL_NEW_RESOURCE(id, client);

    return CreateColormap(id, pScreen, pVisual, &pmap, alloc, client->index);
}
