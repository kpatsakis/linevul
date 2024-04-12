status_t Camera3Device::getStreamInfo(int id,
 uint32_t *width, uint32_t *height,
 uint32_t *format, android_dataspace *dataSpace) {
    ATRACE_CALL();
 Mutex::Autolock il(mInterfaceLock);
 Mutex::Autolock l(mLock);

 switch (mStatus) {
 case STATUS_ERROR:
            CLOGE("Device has encountered a serious error");
 return INVALID_OPERATION;
 case STATUS_UNINITIALIZED:
            CLOGE("Device not initialized!");
 return INVALID_OPERATION;
 case STATUS_UNCONFIGURED:
 case STATUS_CONFIGURED:
 case STATUS_ACTIVE:
 break;
 default:
            SET_ERR_L("Unexpected status: %d", mStatus);
 return INVALID_OPERATION;
 }

 ssize_t idx = mOutputStreams.indexOfKey(id);
 if (idx == NAME_NOT_FOUND) {
        CLOGE("Stream %d is unknown", id);
 return idx;
 }

 if (width) *width  = mOutputStreams[idx]->getWidth();
 if (height) *height = mOutputStreams[idx]->getHeight();
 if (format) *format = mOutputStreams[idx]->getFormat();
 if (dataSpace) *dataSpace = mOutputStreams[idx]->getDataSpace();
 return OK;
}
