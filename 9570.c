DGAStealButtonEvent(DeviceIntPtr dev, int index, int button, int is_down)
{
    DGAScreenPtr pScreenPriv;
    DGAEvent event;

    if (!DGAScreenKeyRegistered)        /* no DGA */
        return FALSE;

    pScreenPriv = DGA_GET_SCREEN_PRIV(screenInfo.screens[index]);

    if (!pScreenPriv || !pScreenPriv->grabMouse)
        return FALSE;

    event = (DGAEvent) {
        .header = ET_Internal,
        .type = ET_DGAEvent,
        .length = sizeof(event),
        .time = GetTimeInMillis(),
        .subtype = (is_down ? ET_ButtonPress : ET_ButtonRelease),
        .detail = button,
        .dx = 0,
        .dy = 0
    };
    mieqEnqueue(dev, (InternalEvent *) &event);

    return TRUE;
}
