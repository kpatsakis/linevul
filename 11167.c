void NuPlayer::GenericSource::setDrmPlaybackStatusIfNeeded(int playbackStatus, int64_t position) {
 if (mDecryptHandle != NULL) {
        mDrmManagerClient->setPlaybackStatus(mDecryptHandle, playbackStatus, position);
 }
    mSubtitleTrack.mPackets = new AnotherPacketSource(NULL);
    mTimedTextTrack.mPackets = new AnotherPacketSource(NULL);
}
