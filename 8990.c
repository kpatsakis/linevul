status_t Parcel::finishWrite(size_t len)
{
    mDataPos += len;
    ALOGV("finishWrite Setting data pos of %p to %zu", this, mDataPos);
 if (mDataPos > mDataSize) {
        mDataSize = mDataPos;
        ALOGV("finishWrite Setting data size of %p to %zu", this, mDataSize);
 }
 return NO_ERROR;
}
