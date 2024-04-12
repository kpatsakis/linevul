static VOID ParaNdis_AddDriverOKStatus(PPARANDIS_ADAPTER pContext)
{
    pContext->bDeviceInitialized = TRUE;

    KeMemoryBarrier();

    VirtIODeviceAddStatus(pContext->IODevice, VIRTIO_CONFIG_S_DRIVER_OK);
}
