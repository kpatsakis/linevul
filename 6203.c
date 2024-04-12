status_t SampleTable::findSampleAtTime(
 uint64_t req_time, uint64_t scale_num, uint64_t scale_den,
 uint32_t *sample_index, uint32_t flags) {
    buildSampleEntriesTable();

 uint32_t left = 0;
 uint32_t right_plus_one = mNumSampleSizes;
 while (left < right_plus_one) {
 uint32_t center = left + (right_plus_one - left) / 2;
 uint64_t centerTime =
            getSampleTime(center, scale_num, scale_den);

 if (req_time < centerTime) {
            right_plus_one = center;
 } else if (req_time > centerTime) {
            left = center + 1;
 } else {
 *sample_index = mSampleTimeEntries[center].mSampleIndex;
 return OK;
 }
 }

 uint32_t closestIndex = left;

 if (closestIndex == mNumSampleSizes) {
 if (flags == kFlagAfter) {
 return ERROR_OUT_OF_RANGE;
 }
        flags = kFlagBefore;
 } else if (closestIndex == 0) {
 if (flags == kFlagBefore) {
 }
        flags = kFlagAfter;
 }

 switch (flags) {
 case kFlagBefore:
 {
 --closestIndex;
 break;
 }

 case kFlagAfter:
 {
 break;
 }

 default:
 {
            CHECK(flags == kFlagClosest);
 if (abs_difference(
                    getSampleTime(closestIndex, scale_num, scale_den), req_time) >
                abs_difference(
                    req_time, getSampleTime(closestIndex - 1, scale_num, scale_den))) {
 --closestIndex;
 }
 break;
 }
 }

 *sample_index = mSampleTimeEntries[closestIndex].mSampleIndex;
 return OK;
}
