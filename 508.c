ScreenSaverFreeEvents(void *value, XID id)
{
    ScreenSaverEventPtr pOld = (ScreenSaverEventPtr) value;
    ScreenPtr pScreen = pOld->screen;

    SetupScreen(pScreen);
    ScreenSaverEventPtr pEv, *pPrev;

    if (!pPriv)
        return TRUE;
    for (pPrev = &pPriv->events; (pEv = *pPrev) != 0; pPrev = &pEv->next)
        if (pEv == pOld)
            break;
    if (!pEv)
        return TRUE;
    *pPrev = pEv->next;
    free(pEv);
    CheckScreenPrivate(pScreen);
    return TRUE;
}
