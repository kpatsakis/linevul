UninstallSaverColormap(ScreenPtr pScreen)
{
    SetupScreen(pScreen);
    ColormapPtr pCmap;
    int rc;

    if (pPriv && pPriv->installedMap != None) {
        rc = dixLookupResourceByType((void **) &pCmap, pPriv->installedMap,
                                     RT_COLORMAP, serverClient,
                                     DixUninstallAccess);
        if (rc == Success)
            (*pCmap->pScreen->UninstallColormap) (pCmap);
        pPriv->installedMap = None;
        CheckScreenPrivate(pScreen);
    }
}
