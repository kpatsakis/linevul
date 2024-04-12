int VirtualizerForceVirtualizationMode(EffectContext *pContext, audio_devices_t forcedDevice) {
    ALOGV("VirtualizerForceVirtualizationMode: forcedDev=0x%x enabled=%d tmpDisabled=%d",
            forcedDevice, pContext->pBundledContext->bVirtualizerEnabled,
            pContext->pBundledContext->bVirtualizerTempDisabled);
 int status = 0;
 bool useVirtualizer = false;

 if (VirtualizerIsDeviceSupported(forcedDevice) != 0) {
 if (forcedDevice != AUDIO_DEVICE_NONE) {
            forcedDevice = AUDIO_DEVICE_NONE;
            status = -EINVAL;
 }
 }

 if (forcedDevice == AUDIO_DEVICE_NONE) {
 if (VirtualizerIsDeviceSupported(pContext->pBundledContext->nOutputDevice) == 0) {
            useVirtualizer = (pContext->pBundledContext->bVirtualizerEnabled == LVM_TRUE);
 }
        pContext->pBundledContext->nVirtualizerForcedDevice = AUDIO_DEVICE_NONE;
 } else {
        pContext->pBundledContext->nVirtualizerForcedDevice = AUDIO_DEVICE_OUT_WIRED_HEADPHONE;
        useVirtualizer = (pContext->pBundledContext->bVirtualizerEnabled == LVM_TRUE);
 }

 if (useVirtualizer) {
 if (pContext->pBundledContext->bVirtualizerTempDisabled == LVM_TRUE) {
            ALOGV("\tVirtualizerForceVirtualizationMode re-enable LVM_VIRTUALIZER");
            android::LvmEffect_enable(pContext);
            pContext->pBundledContext->bVirtualizerTempDisabled = LVM_FALSE;
 } else {
            ALOGV("\tVirtualizerForceVirtualizationMode leaving LVM_VIRTUALIZER enabled");
 }
 } else {
 if (pContext->pBundledContext->bVirtualizerTempDisabled == LVM_FALSE) {
            ALOGV("\tVirtualizerForceVirtualizationMode disable LVM_VIRTUALIZER");
            android::LvmEffect_disable(pContext);
            pContext->pBundledContext->bVirtualizerTempDisabled = LVM_TRUE;
 } else {
            ALOGV("\tVirtualizerForceVirtualizationMode leaving LVM_VIRTUALIZER disabled");
 }
 }

    ALOGV("\tafter VirtualizerForceVirtualizationMode: enabled=%d tmpDisabled=%d",
            pContext->pBundledContext->bVirtualizerEnabled,
            pContext->pBundledContext->bVirtualizerTempDisabled);

 return status;
}
