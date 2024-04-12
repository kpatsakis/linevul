DGAUninstallColormap(ColormapPtr pmap)
{
    ScreenPtr pScreen = pmap->pScreen;
    DGAScreenPtr pScreenPriv = DGA_GET_SCREEN_PRIV(pScreen);

    if (pScreenPriv->current && pScreenPriv->dgaColormap) {
        if (pmap == pScreenPriv->dgaColormap) {
            pScreenPriv->dgaColormap = NULL;
        }
    }

    pScreen->UninstallColormap = pScreenPriv->UninstallColormap;
    (*pScreen->UninstallColormap) (pmap);
    pScreen->UninstallColormap = DGAUninstallColormap;
}
