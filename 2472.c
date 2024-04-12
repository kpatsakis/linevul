getEventMask(ScreenPtr pScreen, ClientPtr client)
{
    SetupScreen(pScreen);
    ScreenSaverEventPtr pEv;

    if (!pPriv)
        return 0;
    for (pEv = pPriv->events; pEv; pEv = pEv->next)
        if (pEv->client == client)
            return pEv->mask;
    return 0;
}
