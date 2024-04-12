void AudioSource::waitOutstandingEncodingFrames_l() {
    ALOGV("waitOutstandingEncodingFrames_l: %" PRId64, mNumClientOwnedBuffers);
 while (mNumClientOwnedBuffers > 0) {
        mFrameEncodingCompletionCondition.wait(mLock);
 }
}
