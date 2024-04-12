status_t Parcel::restartWrite(size_t desired)
{
 if (mOwner) {
        freeData();
 return continueWrite(desired);
 }

 uint8_t* data = (uint8_t*)realloc(mData, desired);
 if (!data && desired > mDataCapacity) {
        mError = NO_MEMORY;
 return NO_MEMORY;
 }

    releaseObjects();

 if (data) {
        LOG_ALLOC("Parcel %p: restart from %zu to %zu capacity", this, mDataCapacity, desired);
        pthread_mutex_lock(&gParcelGlobalAllocSizeLock);
        gParcelGlobalAllocSize += desired;
        gParcelGlobalAllocSize -= mDataCapacity;
        pthread_mutex_unlock(&gParcelGlobalAllocSizeLock);
        mData = data;
        mDataCapacity = desired;
 }

    mDataSize = mDataPos = 0;
    ALOGV("restartWrite Setting data size of %p to %zu", this, mDataSize);
    ALOGV("restartWrite Setting data pos of %p to %zu", this, mDataPos);

    free(mObjects);
    mObjects = NULL;
    mObjectsSize = mObjectsCapacity = 0;
    mNextObjectHint = 0;
    mHasFds = false;
    mFdsKnown = true;
    mAllowFds = true;

 return NO_ERROR;
}
