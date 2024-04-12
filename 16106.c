static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state)
{
 struct audio_device *adev = (struct audio_device *)dev;

 *state = adev->mic_mute;

 return 0;
}
