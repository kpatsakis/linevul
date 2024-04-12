sp<IMediaCodecList> MediaPlayerService::getCodecList() const {
 return MediaCodecList::getLocalInstance();
}
