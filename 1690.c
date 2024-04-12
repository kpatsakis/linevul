status_t InputDispatcher::unregisterInputChannel(const sp<InputChannel>& inputChannel) {
#if DEBUG_REGISTRATION
    ALOGD("channel '%s' ~ unregisterInputChannel", inputChannel->getName().string());
#endif

 { // acquire lock
 AutoMutex _l(mLock);

 status_t status = unregisterInputChannelLocked(inputChannel, false /*notify*/);
 if (status) {
 return status;
 }
 } // release lock

    mLooper->wake();
 return OK;
}
