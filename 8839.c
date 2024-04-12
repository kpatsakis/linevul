void SoftAAC2::drainDecoder() {
 while (mOutputDelayCompensated > 0) {
        INT_PCM tmpOutBuffer[2048 * MAX_CHANNEL_COUNT];

        mDrcWrap.submitStreamData(mStreamInfo);
        mDrcWrap.update();

        AAC_DECODER_ERROR decoderErr =
            aacDecoder_DecodeFrame(mAACDecoder,
                                   tmpOutBuffer,
 2048 * MAX_CHANNEL_COUNT,
                                   AACDEC_FLUSH);
 if (decoderErr != AAC_DEC_OK) {
            ALOGW("aacDecoder_DecodeFrame decoderErr = 0x%4.4x", decoderErr);
 }

 int32_t tmpOutBufferSamples = mStreamInfo->frameSize * mStreamInfo->numChannels;
 if (tmpOutBufferSamples > mOutputDelayCompensated) {
            tmpOutBufferSamples = mOutputDelayCompensated;
 }
        outputDelayRingBufferPutSamples(tmpOutBuffer, tmpOutBufferSamples);

        mOutputDelayCompensated -= tmpOutBufferSamples;
 }
}
