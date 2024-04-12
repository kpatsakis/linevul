status_t StreamingProcessor::startStream(StreamType type,
 const Vector<int32_t> &outputStreams) {
    ATRACE_CALL();
 status_t res;

 if (type == NONE) return INVALID_OPERATION;

    sp<CameraDeviceBase> device = mDevice.promote();
 if (device == 0) {
        ALOGE("%s: Camera %d: Device does not exist", __FUNCTION__, mId);
 return INVALID_OPERATION;
 }

    ALOGV("%s: Camera %d: type = %d", __FUNCTION__, mId, type);

 Mutex::Autolock m(mMutex);

 bool isRecordingStreamIdle = !isStreamActive(mActiveStreamIds, mRecordingStreamId);
 bool startRecordingStream = isStreamActive(outputStreams, mRecordingStreamId);
 if (startRecordingStream && isRecordingStreamIdle) {
        releaseAllRecordingFramesLocked();
 }

    ALOGV("%s: Camera %d: %s started, recording heap has %zu free of %zu",
            __FUNCTION__, mId, (type == PREVIEW) ? "preview" : "recording",
            mRecordingHeapFree, mRecordingHeapCount);

 CameraMetadata &request = (type == PREVIEW) ?
            mPreviewRequest : mRecordingRequest;

    res = request.update(
        ANDROID_REQUEST_OUTPUT_STREAMS,
        outputStreams);
 if (res != OK) {
        ALOGE("%s: Camera %d: Unable to set up preview request: %s (%d)",
                __FUNCTION__, mId, strerror(-res), res);
 return res;
 }

    res = request.sort();
 if (res != OK) {
        ALOGE("%s: Camera %d: Error sorting preview request: %s (%d)",
                __FUNCTION__, mId, strerror(-res), res);
 return res;
 }

    res = device->setStreamingRequest(request);
 if (res != OK) {
        ALOGE("%s: Camera %d: Unable to set preview request to start preview: "
 "%s (%d)",
                __FUNCTION__, mId, strerror(-res), res);
 return res;
 }
    mActiveRequest = type;
    mPaused = false;
    mActiveStreamIds = outputStreams;
 return OK;
}
