XFixesExtensionInit(void)
{
    ExtensionEntry *extEntry;

    if (!dixRegisterPrivateKey
        (&XFixesClientPrivateKeyRec, PRIVATE_CLIENT, sizeof(XFixesClientRec)))
        return;

    if (XFixesSelectionInit() && XFixesCursorInit() && XFixesRegionInit() &&
        (extEntry = AddExtension(XFIXES_NAME, XFixesNumberEvents,
                                 XFixesNumberErrors,
                                 ProcXFixesDispatch, SProcXFixesDispatch,
                                 NULL, StandardMinorOpcode)) != 0) {
        XFixesReqCode = (unsigned char) extEntry->base;
        XFixesEventBase = extEntry->eventBase;
        XFixesErrorBase = extEntry->errorBase;
        EventSwapVector[XFixesEventBase + XFixesSelectionNotify] =
            (EventSwapPtr) SXFixesSelectionNotifyEvent;
        EventSwapVector[XFixesEventBase + XFixesCursorNotify] =
            (EventSwapPtr) SXFixesCursorNotifyEvent;
        SetResourceTypeErrorValue(RegionResType, XFixesErrorBase + BadRegion);
        SetResourceTypeErrorValue(PointerBarrierType,
                                  XFixesErrorBase + BadBarrier);
    }
}
