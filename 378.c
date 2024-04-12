void CameraSourceListener::postDataTimestamp(
 nsecs_t timestamp, int32_t msgType, const sp<IMemory>& dataPtr) {

    sp<CameraSource> source = mSource.promote();
 if (source.get() != NULL) {
        source->dataCallbackTimestamp(timestamp/1000, msgType, dataPtr);
 }
}
