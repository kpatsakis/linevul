status_t DRMSource::start(MetaData *params) {
 int32_t val;
 if (params && params->findInt32(kKeyWantsNALFragments, &val)
 && val != 0) {
        mWantsNALFragments = true;
 } else {
        mWantsNALFragments = false;
 }

 return mOriginalMediaSource->start(params);
}
