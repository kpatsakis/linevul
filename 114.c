void SoundPool::setVolume(int channelID, float leftVolume, float rightVolume)
{
 Mutex::Autolock lock(&mLock);
 SoundChannel* channel = findChannel(channelID);
 if (channel) {
        channel->setVolume(leftVolume, rightVolume);
 }
}
