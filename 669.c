status_t NuMediaExtractor::readSampleData(const sp<ABuffer> &buffer) {
 Mutex::Autolock autoLock(mLock);

 ssize_t minIndex = fetchTrackSamples();

 if (minIndex < 0) {
 return ERROR_END_OF_STREAM;
 }

 TrackInfo *info = &mSelectedTracks.editItemAt(minIndex);

 size_t sampleSize = info->mSample->range_length();

 if (info->mTrackFlags & kIsVorbis) {
        sampleSize += sizeof(int32_t);
 }

 if (buffer->capacity() < sampleSize) {
 return -ENOMEM;
 }

 const uint8_t *src =
 (const uint8_t *)info->mSample->data()
 + info->mSample->range_offset();

    memcpy((uint8_t *)buffer->data(), src, info->mSample->range_length());

 status_t err = OK;
 if (info->mTrackFlags & kIsVorbis) {
        err = appendVorbisNumPageSamples(info, buffer);
 }

 if (err == OK) {
        buffer->setRange(0, sampleSize);
 }

 return err;
}
