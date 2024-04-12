int equalizer_get_num_presets(equalizer_context_t *context __unused)
{
    ALOGV("%s: presets_num: %d", __func__,
 sizeof(equalizer_preset_names)/sizeof(char *));
 return sizeof(equalizer_preset_names)/sizeof(char *);
}
