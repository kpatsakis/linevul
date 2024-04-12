DGAShutdown(void)
{
    ScrnInfoPtr pScrn;
    int i;

    if (!DGAScreenKeyRegistered)
        return;

    for (i = 0; i < screenInfo.numScreens; i++) {
        pScrn = xf86Screens[i];

        (void) (*pScrn->SetDGAMode) (pScrn, 0, NULL);
    }
}
