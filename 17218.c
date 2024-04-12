 bool SoundPool::unload(int sampleID)
{
    ALOGV("unload: sampleID=%d", sampleID);
 Mutex::Autolock lock(&mLock);
 return mSamples.removeItem(sampleID);
}
