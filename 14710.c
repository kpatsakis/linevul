status_t MediaPlayerService::Client::setAudioAttributes_l(const Parcel &parcel)
{
 if (mAudioAttributes != NULL) { free(mAudioAttributes); }
    mAudioAttributes = (audio_attributes_t *) calloc(1, sizeof(audio_attributes_t));
 if (mAudioAttributes == NULL) {
 return NO_MEMORY;
 }
    unmarshallAudioAttributes(parcel, mAudioAttributes);

    ALOGV("setAudioAttributes_l() usage=%d content=%d flags=0x%x tags=%s",
            mAudioAttributes->usage, mAudioAttributes->content_type, mAudioAttributes->flags,
            mAudioAttributes->tags);

 if (mAudioOutput != 0) {
        mAudioOutput->setAudioAttributes(mAudioAttributes);
 }
 return NO_ERROR;
}
