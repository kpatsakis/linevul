status_t MPEG4Source::parseTrackFragmentHeader(off64_t offset, off64_t size) {

 if (size < 8) {
 return -EINVAL;
 }

 uint32_t flags;
 if (!mDataSource->getUInt32(offset, &flags)) { // actually version + flags
 return ERROR_MALFORMED;
 }

 if (flags & 0xff000000) {
 return -EINVAL;
 }

 if (!mDataSource->getUInt32(offset + 4, (uint32_t*)&mLastParsedTrackId)) {
 return ERROR_MALFORMED;
 }

 if (mLastParsedTrackId != mTrackId) {
 return OK;
 }

    mTrackFragmentHeaderInfo.mFlags = flags;
    mTrackFragmentHeaderInfo.mTrackID = mLastParsedTrackId;
    offset += 8;
    size -= 8;

    ALOGV("fragment header: %08x %08x", flags, mTrackFragmentHeaderInfo.mTrackID);

 if (flags & TrackFragmentHeaderInfo::kBaseDataOffsetPresent) {
 if (size < 8) {
 return -EINVAL;
 }

 if (!mDataSource->getUInt64(offset, &mTrackFragmentHeaderInfo.mBaseDataOffset)) {
 return ERROR_MALFORMED;
 }
        offset += 8;
        size -= 8;
 }

 if (flags & TrackFragmentHeaderInfo::kSampleDescriptionIndexPresent) {
 if (size < 4) {
 return -EINVAL;
 }

 if (!mDataSource->getUInt32(offset, &mTrackFragmentHeaderInfo.mSampleDescriptionIndex)) {
 return ERROR_MALFORMED;
 }
        offset += 4;
        size -= 4;
 }

 if (flags & TrackFragmentHeaderInfo::kDefaultSampleDurationPresent) {
 if (size < 4) {
 return -EINVAL;
 }

 if (!mDataSource->getUInt32(offset, &mTrackFragmentHeaderInfo.mDefaultSampleDuration)) {
 return ERROR_MALFORMED;
 }
        offset += 4;
        size -= 4;
 }

 if (flags & TrackFragmentHeaderInfo::kDefaultSampleSizePresent) {
 if (size < 4) {
 return -EINVAL;
 }

 if (!mDataSource->getUInt32(offset, &mTrackFragmentHeaderInfo.mDefaultSampleSize)) {
 return ERROR_MALFORMED;
 }
        offset += 4;
        size -= 4;
 }

 if (flags & TrackFragmentHeaderInfo::kDefaultSampleFlagsPresent) {
 if (size < 4) {
 return -EINVAL;
 }

 if (!mDataSource->getUInt32(offset, &mTrackFragmentHeaderInfo.mDefaultSampleFlags)) {
 return ERROR_MALFORMED;
 }
        offset += 4;
        size -= 4;
 }

 if (!(flags & TrackFragmentHeaderInfo::kBaseDataOffsetPresent)) {
        mTrackFragmentHeaderInfo.mBaseDataOffset = mCurrentMoofOffset;
 }

    mTrackFragmentHeaderInfo.mDataOffset = 0;
 return OK;
}
