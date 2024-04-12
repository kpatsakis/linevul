status_t SampleIterator::findSampleTimeAndDuration(
 uint32_t sampleIndex, uint32_t *time, uint32_t *duration) {
 if (sampleIndex >= mTable->mNumSampleSizes) {
 return ERROR_OUT_OF_RANGE;
 }

 while (sampleIndex >= mTTSSampleIndex + mTTSCount) {
 if (mTimeToSampleIndex == mTable->mTimeToSampleCount) {
 return ERROR_OUT_OF_RANGE;
 }

        mTTSSampleIndex += mTTSCount;
        mTTSSampleTime += mTTSCount * mTTSDuration;

        mTTSCount = mTable->mTimeToSample[2 * mTimeToSampleIndex];
        mTTSDuration = mTable->mTimeToSample[2 * mTimeToSampleIndex + 1];

 ++mTimeToSampleIndex;
 }

 *time = mTTSSampleTime + mTTSDuration * (sampleIndex - mTTSSampleIndex);

 int32_t offset = mTable->getCompositionTimeOffset(sampleIndex);
 if ((offset < 0 && *time < (offset == INT32_MIN ?
            INT32_MAX : uint32_t(-offset))) ||
 (offset > 0 && *time > UINT32_MAX - offset)) {
        ALOGE("%u + %d would overflow", *time, offset);
 return ERROR_OUT_OF_RANGE;
 }
 if (offset > 0) {
 *time += offset;
 } else {
 *time -= (offset == INT32_MIN ? INT32_MAX : (-offset));
 }

 *duration = mTTSDuration;

 return OK;
}
