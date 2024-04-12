status_t Camera3Device::RequestThread::flush() {
    ATRACE_CALL();
 Mutex::Autolock l(mFlushLock);

 if (mHal3Device->common.version >= CAMERA_DEVICE_API_VERSION_3_1) {
 return mHal3Device->ops->flush(mHal3Device);
 }

 return -ENOTSUP;
}
