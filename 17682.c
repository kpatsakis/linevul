void SoftAVC::onQueueFilled(OMX_U32 portIndex) {
    IV_STATUS_T status;
    WORD32 timeDelay, timeTaken;

    UNUSED(portIndex);

 if (mCodecCtx == NULL) {
 if (OMX_ErrorNone != initEncoder()) {
            ALOGE("Failed to initialize encoder");
            notify(OMX_EventError, OMX_ErrorUndefined, 0 /* arg2 */, NULL /* data */);
 return;
 }
 }
 if (mSignalledError) {
 return;
 }

 List<BufferInfo *> &inQueue = getPortQueue(0);
 List<BufferInfo *> &outQueue = getPortQueue(1);

 while (!mSawOutputEOS && !outQueue.empty()) {

        OMX_ERRORTYPE error;
 ive_video_encode_ip_t s_encode_ip;
 ive_video_encode_op_t s_encode_op;
 BufferInfo *outputBufferInfo = *outQueue.begin();
        OMX_BUFFERHEADERTYPE *outputBufferHeader = outputBufferInfo->mHeader;

 BufferInfo *inputBufferInfo;
        OMX_BUFFERHEADERTYPE *inputBufferHeader;

 if (mSawInputEOS) {
            inputBufferHeader = NULL;
            inputBufferInfo = NULL;
 } else if (!inQueue.empty()) {
            inputBufferInfo = *inQueue.begin();
            inputBufferHeader = inputBufferInfo->mHeader;
 } else {
 return;
 }

        outputBufferHeader->nTimeStamp = 0;
        outputBufferHeader->nFlags = 0;
        outputBufferHeader->nOffset = 0;
        outputBufferHeader->nFilledLen = 0;
        outputBufferHeader->nOffset = 0;

 if (inputBufferHeader != NULL) {
            outputBufferHeader->nFlags = inputBufferHeader->nFlags;
 }

 uint8_t *outPtr = (uint8_t *)outputBufferHeader->pBuffer;

 if (!mSpsPpsHeaderReceived) {
            error = setEncodeArgs(&s_encode_ip, &s_encode_op, NULL, outputBufferHeader);
 if (error != OMX_ErrorNone) {
                mSignalledError = true;
                notify(OMX_EventError, OMX_ErrorUndefined, 0, 0);
 return;
 }
            status = ive_api_function(mCodecCtx, &s_encode_ip, &s_encode_op);

 if (IV_SUCCESS != status) {
                ALOGE("Encode Frame failed = 0x%x\n",
                        s_encode_op.u4_error_code);
 } else {
                ALOGV("Bytes Generated in header %d\n",
                        s_encode_op.s_out_buf.u4_bytes);
 }

            mSpsPpsHeaderReceived = true;

            outputBufferHeader->nFlags = OMX_BUFFERFLAG_CODECCONFIG;
            outputBufferHeader->nFilledLen = s_encode_op.s_out_buf.u4_bytes;
 if (inputBufferHeader != NULL) {
                outputBufferHeader->nTimeStamp = inputBufferHeader->nTimeStamp;
 }

            outQueue.erase(outQueue.begin());
            outputBufferInfo->mOwnedByUs = false;

            DUMP_TO_FILE(
                    mOutFile, outputBufferHeader->pBuffer,
                    outputBufferHeader->nFilledLen);
            notifyFillBufferDone(outputBufferHeader);

            setEncMode(IVE_ENC_MODE_PICTURE);
 return;
 }

 if (mBitrateUpdated) {
            setBitRate();
 }

 if (mKeyFrameRequested) {
            setFrameType(IV_IDR_FRAME);
 }

 if ((inputBufferHeader != NULL)
 && (inputBufferHeader->nFlags & OMX_BUFFERFLAG_EOS)) {
            mSawInputEOS = true;
 }

 /* In normal mode, store inputBufferInfo and this will be returned
           when encoder consumes this input */
 if (!mInputDataIsMeta && (inputBufferInfo != NULL)) {
 for (size_t i = 0; i < MAX_INPUT_BUFFER_HEADERS; i++) {
 if (NULL == mInputBufferInfo[i]) {
                    mInputBufferInfo[i] = inputBufferInfo;
 break;
 }
 }
 }
        error = setEncodeArgs(
 &s_encode_ip, &s_encode_op, inputBufferHeader, outputBufferHeader);

 if (error != OMX_ErrorNone) {
            mSignalledError = true;
            notify(OMX_EventError, OMX_ErrorUndefined, 0, 0);
 return;
 }

        DUMP_TO_FILE(
                mInFile, s_encode_ip.s_inp_buf.apv_bufs[0],
 (mHeight * mStride * 3 / 2));

        GETTIME(&mTimeStart, NULL);
 /* Compute time elapsed between end of previous decode()
         * to start of current decode() */
        TIME_DIFF(mTimeEnd, mTimeStart, timeDelay);
        status = ive_api_function(mCodecCtx, &s_encode_ip, &s_encode_op);

 if (IV_SUCCESS != status) {
            ALOGE("Encode Frame failed = 0x%x\n",
                    s_encode_op.u4_error_code);
            mSignalledError = true;
            notify(OMX_EventError, OMX_ErrorUndefined, 0, 0);
 return;
 }

        GETTIME(&mTimeEnd, NULL);
 /* Compute time taken for decode() */
        TIME_DIFF(mTimeStart, mTimeEnd, timeTaken);

        ALOGV("timeTaken=%6d delay=%6d numBytes=%6d", timeTaken, timeDelay,
                s_encode_op.s_out_buf.u4_bytes);

 /* In encoder frees up an input buffer, mark it as free */
 if (s_encode_op.s_inp_buf.apv_bufs[0] != NULL) {
 if (mInputDataIsMeta) {
 for (size_t i = 0; i < MAX_CONVERSION_BUFFERS; i++) {
 if (mConversionBuffers[i] == s_encode_op.s_inp_buf.apv_bufs[0]) {
                        mConversionBuffersFree[i] = 1;
 break;
 }
 }
 } else {
 /* In normal mode, call EBD on inBuffeHeader that is freed by the codec */
 for (size_t i = 0; i < MAX_INPUT_BUFFER_HEADERS; i++) {
 uint8_t *buf = NULL;
                    OMX_BUFFERHEADERTYPE *bufHdr = NULL;
 if (mInputBufferInfo[i] != NULL) {
                        bufHdr = mInputBufferInfo[i]->mHeader;
                        buf = bufHdr->pBuffer + bufHdr->nOffset;
 }
 if (s_encode_op.s_inp_buf.apv_bufs[0] == buf) {
                        mInputBufferInfo[i]->mOwnedByUs = false;
                        notifyEmptyBufferDone(bufHdr);
                        mInputBufferInfo[i] = NULL;
 break;
 }
 }
 }
 }

        outputBufferHeader->nFilledLen = s_encode_op.s_out_buf.u4_bytes;

 if (IV_IDR_FRAME == s_encode_op.u4_encoded_frame_type) {
            outputBufferHeader->nFlags |= OMX_BUFFERFLAG_SYNCFRAME;
 }

 if (inputBufferHeader != NULL) {
            inQueue.erase(inQueue.begin());

 /* If in meta data, call EBD on input */
 /* In case of normal mode, EBD will be done once encoder
            releases the input buffer */
 if (mInputDataIsMeta) {
                inputBufferInfo->mOwnedByUs = false;
                notifyEmptyBufferDone(inputBufferHeader);
 }
 }

 if (s_encode_op.u4_is_last) {
            outputBufferHeader->nFlags |= OMX_BUFFERFLAG_EOS;
            mSawOutputEOS = true;
 } else {
            outputBufferHeader->nFlags &= ~OMX_BUFFERFLAG_EOS;
 }

 if (outputBufferHeader->nFilledLen || s_encode_op.u4_is_last) {
            outputBufferHeader->nTimeStamp = s_encode_op.u4_timestamp_high;
            outputBufferHeader->nTimeStamp <<= 32;
            outputBufferHeader->nTimeStamp |= s_encode_op.u4_timestamp_low;
            outputBufferInfo->mOwnedByUs = false;
            outQueue.erase(outQueue.begin());
            DUMP_TO_FILE(mOutFile, outputBufferHeader->pBuffer,
                    outputBufferHeader->nFilledLen);
            notifyFillBufferDone(outputBufferHeader);
 }

 if (s_encode_op.u4_is_last == 1) {
 return;
 }
 }
 return;
}
