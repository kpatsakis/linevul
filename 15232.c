SoundPool::SoundPool(int maxChannels, const audio_attributes_t* pAttributes)
{
    ALOGV("SoundPool constructor: maxChannels=%d, attr.usage=%d, attr.flags=0x%x, attr.tags=%s",
            maxChannels, pAttributes->usage, pAttributes->flags, pAttributes->tags);

    mMaxChannels = maxChannels;
 if (mMaxChannels < 1) {
        mMaxChannels = 1;
 }
 else if (mMaxChannels > 32) {
        mMaxChannels = 32;
 }
    ALOGW_IF(maxChannels != mMaxChannels, "App requested %d channels", maxChannels);

    mQuit = false;
    mDecodeThread = 0;
    memcpy(&mAttributes, pAttributes, sizeof(audio_attributes_t));
    mAllocated = 0;
    mNextSampleID = 0;
    mNextChannelID = 0;

    mCallback = 0;
    mUserData = 0;

    mChannelPool = new SoundChannel[mMaxChannels];
 for (int i = 0; i < mMaxChannels; ++i) {
        mChannelPool[i].init(this);
        mChannels.push_back(&mChannelPool[i]);
 }

    startThreads();
}
