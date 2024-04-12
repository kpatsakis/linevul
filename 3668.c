void VirtualizerGetSpeakerAngles(audio_channel_mask_t channelMask __unused,
 audio_devices_t deviceType __unused, int32_t *pSpeakerAngles) {
 *pSpeakerAngles++ = (int32_t) AUDIO_CHANNEL_OUT_FRONT_LEFT;
 *pSpeakerAngles++ = -90; // azimuth
 *pSpeakerAngles++ = 0; // elevation
 *pSpeakerAngles++ = (int32_t) AUDIO_CHANNEL_OUT_FRONT_RIGHT;
 *pSpeakerAngles++ = 90; // azimuth
 *pSpeakerAngles   = 0; // elevation
}
