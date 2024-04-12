status_t Camera3Device::RequestThread::removeTriggers(
 const sp<CaptureRequest> &request) {
 Mutex::Autolock al(mTriggerMutex);

 CameraMetadata &metadata = request->mSettings;

 /**
     * Replace all old entries with their old values.
     */
 for (size_t i = 0; i < mTriggerReplacedMap.size(); ++i) {
 RequestTrigger trigger = mTriggerReplacedMap.valueAt(i);

 status_t res;

 uint32_t tag = trigger.metadataTag;
 switch (trigger.getTagType()) {
 case TYPE_BYTE: {
 uint8_t entryValue = static_cast<uint8_t>(trigger.entryValue);
                res = metadata.update(tag,
 &entryValue,
 /*count*/1);
 break;
 }
 case TYPE_INT32:
                res = metadata.update(tag,
 &trigger.entryValue,
 /*count*/1);
 break;
 default:
                ALOGE("%s: Type not supported: 0x%x",
                      __FUNCTION__,
                      trigger.getTagType());
 return INVALID_OPERATION;
 }

 if (res != OK) {
            ALOGE("%s: Failed to restore request metadata with trigger tag %s"
 ", trigger value %d", __FUNCTION__,
                  trigger.getTagName(), trigger.entryValue);
 return res;
 }
 }
    mTriggerReplacedMap.clear();

 /**
     * Remove all new entries.
     */
 for (size_t i = 0; i < mTriggerRemovedMap.size(); ++i) {
 RequestTrigger trigger = mTriggerRemovedMap.valueAt(i);
 status_t res = metadata.erase(trigger.metadataTag);

 if (res != OK) {
            ALOGE("%s: Failed to erase metadata with trigger tag %s"
 ", trigger value %d", __FUNCTION__,
                  trigger.getTagName(), trigger.entryValue);
 return res;
 }
 }
    mTriggerRemovedMap.clear();

 return OK;
}
