void WT_ProcessVoice (S_WT_VOICE *pWTVoice, S_WT_INT_FRAME *pWTIntFrame)
{

 /* use noise generator */
 if (pWTVoice->loopStart == WT_NOISE_GENERATOR)
        WT_NoiseGenerator(pWTVoice, pWTIntFrame);

 /* generate interpolated samples for looped waves */
 else if (pWTVoice->loopStart != pWTVoice->loopEnd)
        WT_Interpolate(pWTVoice, pWTIntFrame);

 /* generate interpolated samples for unlooped waves */
 else
 {
        WT_InterpolateNoLoop(pWTVoice, pWTIntFrame);
 }

#ifdef _FILTER_ENABLED
 if (pWTIntFrame->frame.k != 0)
        WT_VoiceFilter(&pWTVoice->filter, pWTIntFrame);
#endif

#ifdef UNIFIED_MIXER
 {
        EAS_I32 gainLeft, gainIncLeft;

#if (NUM_OUTPUT_CHANNELS == 2)
        EAS_I32 gainRight, gainIncRight;
#endif

        gainLeft = (pWTIntFrame->prevGain * pWTVoice->gainLeft) << 1;
        gainIncLeft = (((pWTIntFrame->frame.gainTarget * pWTVoice->gainLeft) << 1) - gainLeft) >> SYNTH_UPDATE_PERIOD_IN_BITS;

#if (NUM_OUTPUT_CHANNELS == 2)
        gainRight = (pWTIntFrame->prevGain * pWTVoice->gainRight) << 1;
        gainIncRight = (((pWTIntFrame->frame.gainTarget * pWTVoice->gainRight) << 1) - gainRight) >> SYNTH_UPDATE_PERIOD_IN_BITS;
        EAS_MixStream(
            pWTIntFrame->pAudioBuffer,
            pWTIntFrame->pMixBuffer,
            pWTIntFrame->numSamples,
            gainLeft,
            gainRight,
            gainIncLeft,
            gainIncRight,
            MIX_FLAGS_STEREO_OUTPUT);

#else
        EAS_MixStream(
            pWTIntFrame->pAudioBuffer,
            pWTIntFrame->pMixBuffer,
            pWTIntFrame->numSamples,
            gainLeft,
 0,
            gainIncLeft,
 0,
 0);
#endif
 }

#else
 /* apply gain, and left and right gain */
    WT_VoiceGain(pWTVoice, pWTIntFrame);
#endif
}
