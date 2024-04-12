sp<MediaSource> MPEG4Extractor::getTrack(size_t index) {
 status_t err;
 if ((err = readMetaData()) != OK) {
 return NULL;
 }

 Track *track = mFirstTrack;
 while (index > 0) {
 if (track == NULL) {
 return NULL;
 }

        track = track->next;
 --index;
 }

 if (track == NULL) {
 return NULL;
 }

    ALOGV("getTrack called, pssh: %d", mPssh.size());

 return new MPEG4Source(
            track->meta, mDataSource, track->timescale, track->sampleTable,
            mSidxEntries, mMoofOffset);
}
