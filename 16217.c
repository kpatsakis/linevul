void SoundPool::addToStopList(SoundChannel* channel)
{
 Mutex::Autolock lock(&mRestartLock);
 if (!mQuit) {
        mStop.push_back(channel);
        mCondition.signal();
 }
}
