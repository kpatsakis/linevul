void MediaStreamManager::SetUpRequest(const std::string& label) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  DeviceRequest* request = FindRequest(label);
  if (!request) {
    DVLOG(1) << "SetUpRequest label " << label << " doesn't exist!!";
    return;  // This can happen if the request has been canceled.
  }

  request->SetAudioType(AdjustAudioStreamTypeBasedOnCommandLineSwitches(
      request->controls.audio.stream_type));
  request->SetVideoType(request->controls.video.stream_type);

  const bool is_display_capture =
      request->video_type() == MEDIA_DISPLAY_VIDEO_CAPTURE;
  if (is_display_capture && !SetUpDisplayCaptureRequest(request)) {
    FinalizeRequestFailed(label, request, MEDIA_DEVICE_SCREEN_CAPTURE_FAILURE);
    return;
  }

  const bool is_tab_capture =
      request->audio_type() == MEDIA_GUM_TAB_AUDIO_CAPTURE ||
      request->video_type() == MEDIA_GUM_TAB_VIDEO_CAPTURE;
  if (is_tab_capture) {
    if (!SetUpTabCaptureRequest(request, label)) {
      FinalizeRequestFailed(label, request, MEDIA_DEVICE_TAB_CAPTURE_FAILURE);
    }
    return;
  }

  const bool is_screen_capture =
      request->video_type() == MEDIA_GUM_DESKTOP_VIDEO_CAPTURE;
  if (is_screen_capture && !SetUpScreenCaptureRequest(request)) {
    FinalizeRequestFailed(label, request, MEDIA_DEVICE_SCREEN_CAPTURE_FAILURE);
    return;
  }

  if (!is_tab_capture && !is_screen_capture && !is_display_capture) {
    if (IsDeviceMediaType(request->audio_type()) ||
        IsDeviceMediaType(request->video_type())) {
      StartEnumeration(request, label);
      return;
    }
    if (!SetUpDeviceCaptureRequest(request, MediaDeviceEnumeration())) {
      FinalizeRequestFailed(label, request, MEDIA_DEVICE_NO_HARDWARE);
      return;
    }
  }
  ReadOutputParamsAndPostRequestToUI(label, request, MediaDeviceEnumeration());
}
