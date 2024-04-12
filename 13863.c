status_t Camera3Device::setNotifyCallback(NotificationListener *listener) {
    ATRACE_CALL();
 Mutex::Autolock l(mOutputLock);

 if (listener != NULL && mListener != NULL) {
        ALOGW("%s: Replacing old callback listener", __FUNCTION__);
 }
    mListener = listener;
    mRequestThread->setNotificationListener(listener);
    mPreparerThread->setNotificationListener(listener);

 return OK;
}
