void Camera3Device::RequestThread::configurationComplete() {
 Mutex::Autolock l(mRequestLock);
    mReconfigured = true;
}
