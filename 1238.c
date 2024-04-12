sp<ABuffer> NuPlayer::GenericSource::mediaBufferToABuffer(
 MediaBuffer* mb,
        media_track_type trackType,
 int64_t *actualTimeUs) {
 bool audio = trackType == MEDIA_TRACK_TYPE_AUDIO;
 size_t outLength = mb->range_length();

 if (audio && mAudioIsVorbis) {
        outLength += sizeof(int32_t);
 }

    sp<ABuffer> ab;
 if (mIsWidevine && !audio) {
        ab = new ABuffer(NULL, mb->range_length());
        mb->add_ref();
        ab->setMediaBufferBase(mb);
 } else {
        ab = new ABuffer(outLength);
        memcpy(ab->data(),
 (const uint8_t *)mb->data() + mb->range_offset(),
               mb->range_length());
 }

 if (audio && mAudioIsVorbis) {
 int32_t numPageSamples;
 if (!mb->meta_data()->findInt32(kKeyValidSamples, &numPageSamples)) {
            numPageSamples = -1;
 }

 uint8_t* abEnd = ab->data() + mb->range_length();
        memcpy(abEnd, &numPageSamples, sizeof(numPageSamples));
 }

    sp<AMessage> meta = ab->meta();

 int64_t timeUs;
    CHECK(mb->meta_data()->findInt64(kKeyTime, &timeUs));
    meta->setInt64("timeUs", timeUs);

 if (trackType == MEDIA_TRACK_TYPE_TIMEDTEXT) {
 const char *mime;
        CHECK(mTimedTextTrack.mSource != NULL
 && mTimedTextTrack.mSource->getFormat()->findCString(kKeyMIMEType, &mime));
        meta->setString("mime", mime);
 }

 int64_t durationUs;
 if (mb->meta_data()->findInt64(kKeyDuration, &durationUs)) {
        meta->setInt64("durationUs", durationUs);
 }

 if (trackType == MEDIA_TRACK_TYPE_SUBTITLE) {
        meta->setInt32("trackIndex", mSubtitleTrack.mIndex);
 }

 if (actualTimeUs) {
 *actualTimeUs = timeUs;
 }

    mb->release();
    mb = NULL;

 return ab;
}
