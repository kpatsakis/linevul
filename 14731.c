void SoundChannel::autoPause()
{
 Mutex::Autolock lock(&mLock);
 if (mState == PLAYING) {
        ALOGV("pause track");
        mState = PAUSED;
        mAutoPaused = true;
        mAudioTrack->pause();
 }
}
