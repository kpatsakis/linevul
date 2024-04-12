DGAAvailable(int index)
{
    ScreenPtr pScreen;

    assert(index < MAXSCREENS);
    pScreen = screenInfo.screens[index];
    return DGAScreenAvailable(pScreen);
}
