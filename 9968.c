static VOID MiniportDisableMSIInterrupt(
    IN PVOID  MiniportInterruptContext,
    IN ULONG  MessageId
    )
{
    PARANDIS_ADAPTER *pContext = (PARANDIS_ADAPTER *)MiniportInterruptContext;
    /* TODO - How we prevent DPC procedure from re-enabling interrupt? */

    CParaNdisAbstractPath *path = GetPathByMessageId(pContext, MessageId);
    path->DisableInterrupts();
}
