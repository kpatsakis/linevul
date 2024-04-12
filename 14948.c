MediaStreamType PepperMediaDeviceManager::FromPepperDeviceType(
    PP_DeviceType_Dev type) {
  switch (type) {
    case PP_DEVICETYPE_DEV_INVALID:
      return MEDIA_NO_SERVICE;
    case PP_DEVICETYPE_DEV_AUDIOCAPTURE:
      return MEDIA_DEVICE_AUDIO_CAPTURE;
    case PP_DEVICETYPE_DEV_VIDEOCAPTURE:
      return MEDIA_DEVICE_VIDEO_CAPTURE;
    default:
      NOTREACHED();
      return MEDIA_NO_SERVICE;
  }
}
