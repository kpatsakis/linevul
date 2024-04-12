int LE_setConfig(LoudnessEnhancerContext *pContext, effect_config_t *pConfig)
{
    ALOGV("LE_setConfig(%p)", pContext);

 if (pConfig->inputCfg.samplingRate != pConfig->outputCfg.samplingRate) return -EINVAL;
 if (pConfig->inputCfg.channels != pConfig->outputCfg.channels) return -EINVAL;
 if (pConfig->inputCfg.format != pConfig->outputCfg.format) return -EINVAL;
 if (pConfig->inputCfg.channels != AUDIO_CHANNEL_OUT_STEREO) return -EINVAL;
 if (pConfig->outputCfg.accessMode != EFFECT_BUFFER_ACCESS_WRITE &&
            pConfig->outputCfg.accessMode != EFFECT_BUFFER_ACCESS_ACCUMULATE) return -EINVAL;
 if (pConfig->inputCfg.format != AUDIO_FORMAT_PCM_16_BIT) return -EINVAL;

    pContext->mConfig = *pConfig;

    LE_reset(pContext);

 return 0;
}
