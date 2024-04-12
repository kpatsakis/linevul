int Downmix_Configure(downmix_module_t *pDwmModule, effect_config_t *pConfig, bool init) {

 downmix_object_t *pDownmixer = &pDwmModule->context;

 if (pConfig->inputCfg.samplingRate != pConfig->outputCfg.samplingRate
 || pConfig->outputCfg.channels != DOWNMIX_OUTPUT_CHANNELS
 || pConfig->inputCfg.format != AUDIO_FORMAT_PCM_16_BIT
 || pConfig->outputCfg.format != AUDIO_FORMAT_PCM_16_BIT) {
        ALOGE("Downmix_Configure error: invalid config");
 return -EINVAL;
 }

 if (&pDwmModule->config != pConfig) {
        memcpy(&pDwmModule->config, pConfig, sizeof(effect_config_t));
 }

 if (init) {
        pDownmixer->type = DOWNMIX_TYPE_FOLD;
        pDownmixer->apply_volume_correction = false;
        pDownmixer->input_channel_count = 8; // matches default input of AUDIO_CHANNEL_OUT_7POINT1
 } else {
 if (!Downmix_validChannelMask(pConfig->inputCfg.channels)) {
            ALOGE("Downmix_Configure error: input channel mask(0x%x) not supported",
                                                        pConfig->inputCfg.channels);
 return -EINVAL;
 }
        pDownmixer->input_channel_count =
                audio_channel_count_from_out_mask(pConfig->inputCfg.channels);
 }

 Downmix_Reset(pDownmixer, init);

 return 0;
}
