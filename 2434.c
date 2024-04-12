static int out_open_pcm_devices(struct stream_out *out)
{
 struct pcm_device *pcm_device;
 struct listnode *node;
 struct audio_device *adev = out->dev;
 int ret = 0;

    list_for_each(node, &out->pcm_dev_list) {
        pcm_device = node_to_item(node, struct pcm_device, stream_list_node);
        ALOGV("%s: Opening PCM device card_id(%d) device_id(%d)",
              __func__, pcm_device->pcm_profile->card, pcm_device->pcm_profile->device);

 if (pcm_device->pcm_profile->dsp_name) {
            pcm_device->dsp_context = cras_dsp_context_new(pcm_device->pcm_profile->config.rate,
 (adev->mode == AUDIO_MODE_IN_CALL || adev->mode == AUDIO_MODE_IN_COMMUNICATION)
 ? "voice-comm" : "playback");
 if (pcm_device->dsp_context) {
                cras_dsp_set_variable(pcm_device->dsp_context, "dsp_name",
                                      pcm_device->pcm_profile->dsp_name);
                cras_dsp_load_pipeline(pcm_device->dsp_context);
 }
 }

        pcm_device->pcm = pcm_open(pcm_device->pcm_profile->card, pcm_device->pcm_profile->device,
                               PCM_OUT | PCM_MONOTONIC, &pcm_device->pcm_profile->config);

 if (pcm_device->pcm && !pcm_is_ready(pcm_device->pcm)) {
            ALOGE("%s: %s", __func__, pcm_get_error(pcm_device->pcm));
            pcm_device->pcm = NULL;
            ret = -EIO;
 goto error_open;
 }
 /*
        * If the stream rate differs from the PCM rate, we need to
        * create a resampler.
        */
 if (out->sample_rate != pcm_device->pcm_profile->config.rate) {
            ALOGV("%s: create_resampler(), pcm_device_card(%d), pcm_device_id(%d), \
                    out_rate(%d), device_rate(%d)",__func__,
                    pcm_device->pcm_profile->card, pcm_device->pcm_profile->device,
                    out->sample_rate, pcm_device->pcm_profile->config.rate);
            ret = create_resampler(out->sample_rate,
                    pcm_device->pcm_profile->config.rate,
                    audio_channel_count_from_out_mask(out->channel_mask),
                    RESAMPLER_QUALITY_DEFAULT,
                    NULL,
 &pcm_device->resampler);
            pcm_device->res_byte_count = 0;
            pcm_device->res_buffer = NULL;
 }
 }
 return ret;

error_open:
    out_close_pcm_devices(out);
 return ret;
}
