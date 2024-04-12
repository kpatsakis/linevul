void SoundChannel::setVolume_l(float leftVolume, float rightVolume)
{
    mLeftVolume = leftVolume;
    mRightVolume = rightVolume;
 if (mAudioTrack != NULL)
        mAudioTrack->setVolume(leftVolume, rightVolume);
}
