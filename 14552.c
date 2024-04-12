int LE_process(
 effect_handle_t self, audio_buffer_t *inBuffer, audio_buffer_t *outBuffer)
{
 LoudnessEnhancerContext * pContext = (LoudnessEnhancerContext *)self;

 if (pContext == NULL) {
 return -EINVAL;
 }

 if (inBuffer == NULL || inBuffer->raw == NULL ||
        outBuffer == NULL || outBuffer->raw == NULL ||
        inBuffer->frameCount != outBuffer->frameCount ||
        inBuffer->frameCount == 0) {
 return -EINVAL;
 }

 uint16_t inIdx;
 float inputAmp = pow(10, pContext->mTargetGainmB/2000.0f);
 float leftSample, rightSample;
 for (inIdx = 0 ; inIdx < inBuffer->frameCount ; inIdx++) {
        leftSample  = inputAmp * (float)inBuffer->s16[2*inIdx];
        rightSample = inputAmp * (float)inBuffer->s16[2*inIdx +1];
        pContext->mCompressor->Compress(&leftSample, &rightSample);
        inBuffer->s16[2*inIdx] = (int16_t) leftSample;
        inBuffer->s16[2*inIdx +1] = (int16_t) rightSample;
 }

 if (inBuffer->raw != outBuffer->raw) {
 if (pContext->mConfig.outputCfg.accessMode == EFFECT_BUFFER_ACCESS_ACCUMULATE) {
 for (size_t i = 0; i < outBuffer->frameCount*2; i++) {
                outBuffer->s16[i] = clamp16(outBuffer->s16[i] + inBuffer->s16[i]);
 }
 } else {
            memcpy(outBuffer->raw, inBuffer->raw, outBuffer->frameCount * 2 * sizeof(int16_t));
 }
 }
 if (pContext->mState != LOUDNESS_ENHANCER_STATE_ACTIVE) {
 return -ENODATA;
 }
 return 0;
}
