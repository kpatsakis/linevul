InitializeMAC(PPARANDIS_ADAPTER pContext, PUCHAR pCurrentMAC)
{
    pContext->bCfgMACAddrSupported = AckFeature(pContext, VIRTIO_NET_F_MAC);
    pContext->bCtrlMACAddrSupported = AckFeature(pContext, VIRTIO_NET_F_CTRL_MAC_ADDR);

    if (pContext->bCfgMACAddrSupported)
    {
        VirtIODeviceGet(pContext->IODevice, 0, &pContext->PermanentMacAddress, ETH_LENGTH_OF_ADDRESS);
        if (!ParaNdis_ValidateMacAddress(pContext->PermanentMacAddress, FALSE))
        {
            DumpMac(0, "Invalid device MAC ignored", pContext->PermanentMacAddress);
            NdisZeroMemory(pContext->PermanentMacAddress, sizeof(pContext->PermanentMacAddress));
        }
    }

    if (ETH_IS_EMPTY(pContext->PermanentMacAddress))
    {
        pContext->PermanentMacAddress[0] = 0x02;
        pContext->PermanentMacAddress[1] = 0x50;
        pContext->PermanentMacAddress[2] = 0xF2;
        pContext->PermanentMacAddress[3] = 0x00;
        pContext->PermanentMacAddress[4] = 0x01;
        pContext->PermanentMacAddress[5] = 0x80 | (UCHAR)(pContext->ulUniqueID & 0xFF);
        DumpMac(0, "No device MAC present, use default", pContext->PermanentMacAddress);
    }
    DumpMac(0, "Permanent device MAC", pContext->PermanentMacAddress);

    if (ParaNdis_ValidateMacAddress(pCurrentMAC, TRUE))
    {
        DPrintf(0, ("[%s] MAC address from configuration used\n", __FUNCTION__));
        ETH_COPY_NETWORK_ADDRESS(pContext->CurrentMacAddress, pCurrentMAC);
    }
    else
    {
        DPrintf(0, ("No valid MAC configured\n", __FUNCTION__));
        ETH_COPY_NETWORK_ADDRESS(pContext->CurrentMacAddress, pContext->PermanentMacAddress);
    }

    SetDeviceMAC(pContext, pContext->CurrentMacAddress);

    DumpMac(0, "Actual MAC", pContext->CurrentMacAddress);
}
