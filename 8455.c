status_t StreamingProcessor::recordingStreamNeedsUpdate(
 const Parameters &params, bool *needsUpdate) {
 status_t res;

 if (needsUpdate == 0) {
        ALOGE("%s: Camera %d: invalid argument", __FUNCTION__, mId);
 return INVALID_OPERATION;
 }

 if (mRecordingStreamId == NO_STREAM) {
 *needsUpdate = true;
 return OK;
 }

    sp<CameraDeviceBase> device = mDevice.promote();
 if (device == 0) {
        ALOGE("%s: Camera %d: Device does not exist", __FUNCTION__, mId);
 return INVALID_OPERATION;
 }

 uint32_t currentWidth, currentHeight, currentFormat;
    android_dataspace currentDataSpace;
    res = device->getStreamInfo(mRecordingStreamId,
 &currentWidth, &currentHeight, &currentFormat, &currentDataSpace);
 if (res != OK) {
        ALOGE("%s: Camera %d: Error querying recording output stream info: "
 "%s (%d)", __FUNCTION__, mId,
                strerror(-res), res);
 return res;
 }

 if (mRecordingConsumer == 0 ||
            currentWidth != (uint32_t)params.videoWidth ||
            currentHeight != (uint32_t)params.videoHeight ||
            currentFormat != (uint32_t)mRecordingFormat ||
            currentDataSpace != mRecordingDataSpace) {
 *needsUpdate = true;
 }
 *needsUpdate = false;
 return res;
}
