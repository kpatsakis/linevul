VOID ParaNdis_UpdateDeviceFilters(PARANDIS_ADAPTER *pContext)
{
    if (pContext->bHasHardwareFilters)
    {
        ParaNdis_DeviceFiltersUpdateRxMode(pContext);
        ParaNdis_DeviceFiltersUpdateAddresses(pContext);
        ParaNdis_DeviceFiltersUpdateVlanId(pContext);
    }
}
