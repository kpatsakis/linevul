void SoundChannel::setVolume(float leftVolume, float rightVolume)
{
 Mutex::Autolock lock(&mLock);
    setVolume_l(leftVolume, rightVolume);
}
