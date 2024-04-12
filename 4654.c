status_t OMXCodec::read(
 MediaBuffer **buffer, const ReadOptions *options) {
 status_t err = OK;
 *buffer = NULL;

 Mutex::Autolock autoLock(mLock);

 if (mState != EXECUTING && mState != RECONFIGURING) {
 return UNKNOWN_ERROR;
 }

 bool seeking = false;
 int64_t seekTimeUs;
 ReadOptions::SeekMode seekMode;
 if (options && options->getSeekTo(&seekTimeUs, &seekMode)) {
        seeking = true;
 }

 if (mInitialBufferSubmit) {
        mInitialBufferSubmit = false;

 if (seeking) {
            CHECK(seekTimeUs >= 0);
            mSeekTimeUs = seekTimeUs;
            mSeekMode = seekMode;

            seeking = false;
            mPaused = false;
 }

        drainInputBuffers();

 if (mState == EXECUTING) {
            fillOutputBuffers();
 }
 }

 if (seeking) {
 while (mState == RECONFIGURING) {
 if ((err = waitForBufferFilled_l()) != OK) {
 return err;
 }
 }

 if (mState != EXECUTING) {
 return UNKNOWN_ERROR;
 }

        CODEC_LOGV("seeking to %" PRId64 " us (%.2f secs)", seekTimeUs, seekTimeUs / 1E6);

        mSignalledEOS = false;

        CHECK(seekTimeUs >= 0);
        mSeekTimeUs = seekTimeUs;
        mSeekMode = seekMode;

        mFilledBuffers.clear();

        CHECK_EQ((int)mState, (int)EXECUTING);

 bool emulateInputFlushCompletion = !flushPortAsync(kPortIndexInput);
 bool emulateOutputFlushCompletion = !flushPortAsync(kPortIndexOutput);

 if (emulateInputFlushCompletion) {
            onCmdComplete(OMX_CommandFlush, kPortIndexInput);
 }

 if (emulateOutputFlushCompletion) {
            onCmdComplete(OMX_CommandFlush, kPortIndexOutput);
 }

 while (mSeekTimeUs >= 0) {
 if ((err = waitForBufferFilled_l()) != OK) {
 return err;
 }
 }
 }

 while (mState != ERROR && !mNoMoreOutputData && mFilledBuffers.empty()) {
 if ((err = waitForBufferFilled_l()) != OK) {
 return err;
 }
 }

 if (mState == ERROR) {
 return UNKNOWN_ERROR;
 }

 if (mFilledBuffers.empty()) {
 return mSignalledEOS ? mFinalStatus : ERROR_END_OF_STREAM;
 }

 if (mOutputPortSettingsHaveChanged) {
        mOutputPortSettingsHaveChanged = false;

 return INFO_FORMAT_CHANGED;
 }

 size_t index = *mFilledBuffers.begin();
    mFilledBuffers.erase(mFilledBuffers.begin());

 BufferInfo *info = &mPortBuffers[kPortIndexOutput].editItemAt(index);
    CHECK_EQ((int)info->mStatus, (int)OWNED_BY_US);
    info->mStatus = OWNED_BY_CLIENT;

    info->mMediaBuffer->add_ref();
 if (mSkipCutBuffer != NULL) {
        mSkipCutBuffer->submit(info->mMediaBuffer);
 }
 *buffer = info->mMediaBuffer;

 return OK;
}
