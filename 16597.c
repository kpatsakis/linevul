status_t BufferQueueConsumer::disableAsyncBuffer() {
    ATRACE_CALL();

 Mutex::Autolock lock(mCore->mMutex);

 if (mCore->mConsumerListener != NULL) {
        BQ_LOGE("disableAsyncBuffer: consumer already connected");
 return INVALID_OPERATION;
 }

    BQ_LOGV("disableAsyncBuffer");
    mCore->mUseAsyncBuffer = false;
 return NO_ERROR;
}
