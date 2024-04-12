int SoundPool::run()
{
    mRestartLock.lock();
 while (!mQuit) {
        mCondition.wait(mRestartLock);
        ALOGV("awake");
 if (mQuit) break;

 while (!mStop.empty()) {
 SoundChannel* channel;
            ALOGV("Getting channel from stop list");
 List<SoundChannel* >::iterator iter = mStop.begin();
            channel = *iter;
            mStop.erase(iter);
            mRestartLock.unlock();
 if (channel != 0) {
 Mutex::Autolock lock(&mLock);
                channel->stop();
 }
            mRestartLock.lock();
 if (mQuit) break;
 }

 while (!mRestart.empty()) {
 SoundChannel* channel;
            ALOGV("Getting channel from list");
 List<SoundChannel*>::iterator iter = mRestart.begin();
            channel = *iter;
            mRestart.erase(iter);
            mRestartLock.unlock();
 if (channel != 0) {
 Mutex::Autolock lock(&mLock);
                channel->nextEvent();
 }
            mRestartLock.lock();
 if (mQuit) break;
 }
 }

    mStop.clear();
    mRestart.clear();
    mCondition.signal();
    mRestartLock.unlock();
    ALOGV("goodbye");
 return 0;
}
