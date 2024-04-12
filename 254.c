status_t Camera3Device::disconnect() {
    ATRACE_CALL();
 Mutex::Autolock il(mInterfaceLock);

    ALOGV("%s: E", __FUNCTION__);

 status_t res = OK;

 {
 Mutex::Autolock l(mLock);
 if (mStatus == STATUS_UNINITIALIZED) return res;

 if (mStatus == STATUS_ACTIVE ||
 (mStatus == STATUS_ERROR && mRequestThread != NULL)) {
            res = mRequestThread->clearRepeatingRequests();
 if (res != OK) {
                SET_ERR_L("Can't stop streaming");
 } else {
                res = waitUntilStateThenRelock(/*active*/ false, kShutdownTimeout);
 if (res != OK) {
                    SET_ERR_L("Timeout waiting for HAL to drain");
 }
 }
 }

 if (mStatus == STATUS_ERROR) {
            CLOGE("Shutting down in an error state");
 }

 if (mStatusTracker != NULL) {
            mStatusTracker->requestExit();
 }

 if (mRequestThread != NULL) {
            mRequestThread->requestExit();
 }

        mOutputStreams.clear();
        mInputStream.clear();
 }

 if (mRequestThread != NULL && mStatus != STATUS_ERROR) {
        mRequestThread->join();
 }

 if (mStatusTracker != NULL) {
        mStatusTracker->join();
 }

 camera3_device_t *hal3Device;
 {
 Mutex::Autolock l(mLock);

        mRequestThread.clear();
        mStatusTracker.clear();

        hal3Device = mHal3Device;
 }

 if (hal3Device != NULL) {
        ATRACE_BEGIN("camera3->close");
        hal3Device->common.close(&hal3Device->common);
        ATRACE_END();
 }

 {
 Mutex::Autolock l(mLock);
        mHal3Device = NULL;
        internalUpdateStatusLocked(STATUS_UNINITIALIZED);
 }

    ALOGV("%s: X", __FUNCTION__);
 return res;
}
