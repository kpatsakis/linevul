status_t Camera3Device::triggerPrecaptureMetering(uint32_t id) {
    ATRACE_CALL();
 Mutex::Autolock il(mInterfaceLock);

    ALOGV("%s: Triggering precapture metering, id %d", __FUNCTION__, id);
 RequestTrigger trigger[] = {
 {
            ANDROID_CONTROL_AE_PRECAPTURE_TRIGGER,
            ANDROID_CONTROL_AE_PRECAPTURE_TRIGGER_START
 },
 {
            ANDROID_CONTROL_AE_PRECAPTURE_ID,
 static_cast<int32_t>(id)
 }
 };

 return mRequestThread->queueTrigger(trigger,
 sizeof(trigger)/sizeof(trigger[0]));
}
