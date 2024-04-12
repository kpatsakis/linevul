void SoftAACEncoder::onQueueFilled(OMX_U32 portIndex) {
 if (mSignalledError) {
 return;
 }

 List<BufferInfo *> &inQueue = getPortQueue(0);
 List<BufferInfo *> &outQueue = getPortQueue(1);

 if (!mSentCodecSpecificData) {

 if (outQueue.empty()) {
 return;
 }

 BufferInfo *outInfo = *outQueue.begin();
        OMX_BUFFERHEADERTYPE *outHeader = outInfo->mHeader;
        outHeader->nFilledLen = sizeof(mAudioSpecificConfigData);
        outHeader->nFlags = OMX_BUFFERFLAG_CODECCONFIG;

 uint8_t *out = outHeader->pBuffer + outHeader->nOffset;
        memcpy(out, mAudioSpecificConfigData, sizeof(mAudioSpecificConfigData));

#if 0
        ALOGI("sending codec specific data.");
        hexdump(out, sizeof(mAudioSpecificConfigData));
#endif

        outQueue.erase(outQueue.begin());
        outInfo->mOwnedByUs = false;
        notifyFillBufferDone(outHeader);

        mSentCodecSpecificData = true;
 }

 size_t numBytesPerInputFrame =
        mNumChannels * kNumSamplesPerFrame * sizeof(int16_t);

 for (;;) {

 while (mInputSize < numBytesPerInputFrame) {

 if (mSawInputEOS || inQueue.empty()) {
 return;
 }

 BufferInfo *inInfo = *inQueue.begin();
            OMX_BUFFERHEADERTYPE *inHeader = inInfo->mHeader;

 const void *inData = inHeader->pBuffer + inHeader->nOffset;

 size_t copy = numBytesPerInputFrame - mInputSize;
 if (copy > inHeader->nFilledLen) {
                copy = inHeader->nFilledLen;
 }

 if (mInputFrame == NULL) {
                mInputFrame = new int16_t[kNumSamplesPerFrame * mNumChannels];
 }

 if (mInputSize == 0) {
                mInputTimeUs = inHeader->nTimeStamp;
 }

            memcpy((uint8_t *)mInputFrame + mInputSize, inData, copy);
            mInputSize += copy;

            inHeader->nOffset += copy;
            inHeader->nFilledLen -= copy;

            inHeader->nTimeStamp +=
 (copy * 1000000ll / mSampleRate)
 / (mNumChannels * sizeof(int16_t));

 if (inHeader->nFilledLen == 0) {
 if (inHeader->nFlags & OMX_BUFFERFLAG_EOS) {
                    ALOGV("saw input EOS");
                    mSawInputEOS = true;

                    memset((uint8_t *)mInputFrame + mInputSize,
 0,
                           numBytesPerInputFrame - mInputSize);

                    mInputSize = numBytesPerInputFrame;
 }

                inQueue.erase(inQueue.begin());
                inInfo->mOwnedByUs = false;
                notifyEmptyBufferDone(inHeader);

                inData = NULL;
                inHeader = NULL;
                inInfo = NULL;
 }
 }


 if (outQueue.empty()) {
 return;
 }

 BufferInfo *outInfo = *outQueue.begin();
        OMX_BUFFERHEADERTYPE *outHeader = outInfo->mHeader;

        VO_CODECBUFFER inputData;
        memset(&inputData, 0, sizeof(inputData));
        inputData.Buffer = (unsigned char *)mInputFrame;
        inputData.Length = numBytesPerInputFrame;
        CHECK(VO_ERR_NONE ==
                mApiHandle->SetInputData(mEncoderHandle, &inputData));

        VO_CODECBUFFER outputData;
        memset(&outputData, 0, sizeof(outputData));
        VO_AUDIO_OUTPUTINFO outputInfo;
        memset(&outputInfo, 0, sizeof(outputInfo));

 uint8_t *outPtr = (uint8_t *)outHeader->pBuffer + outHeader->nOffset;
 size_t outAvailable = outHeader->nAllocLen - outHeader->nOffset;

        VO_U32 ret = VO_ERR_NONE;
 size_t nOutputBytes = 0;
 do {
            outputData.Buffer = outPtr;
            outputData.Length = outAvailable - nOutputBytes;
            ret = mApiHandle->GetOutputData(
                    mEncoderHandle, &outputData, &outputInfo);
 if (ret == VO_ERR_NONE) {
                outPtr += outputData.Length;
                nOutputBytes += outputData.Length;
 }
 } while (ret != VO_ERR_INPUT_BUFFER_SMALL);

        outHeader->nFilledLen = nOutputBytes;

        outHeader->nFlags = OMX_BUFFERFLAG_ENDOFFRAME;

 if (mSawInputEOS) {
            outHeader->nFlags = OMX_BUFFERFLAG_EOS;
 }

        outHeader->nTimeStamp = mInputTimeUs;

#if 0
        ALOGI("sending %d bytes of data (time = %lld us, flags = 0x%08lx)",
              nOutputBytes, mInputTimeUs, outHeader->nFlags);

        hexdump(outHeader->pBuffer + outHeader->nOffset, outHeader->nFilledLen);
#endif

        outQueue.erase(outQueue.begin());
        outInfo->mOwnedByUs = false;
        notifyFillBufferDone(outHeader);

        outHeader = NULL;
        outInfo = NULL;

        mInputSize = 0;

     }
 }
