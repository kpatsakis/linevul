void MediaPlayerService::AudioOutput::close()
{
    ALOGV("close");
    sp<AudioTrack> track;
 {
 Mutex::Autolock lock(mLock);
        track = mTrack;
        close_l(); // clears mTrack
 }
}
