bool MediaStreamManager::RequestDone(const DeviceRequest& request) const {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  const bool requested_audio = IsAudioInputMediaType(request.audio_type());
  const bool requested_video = IsVideoMediaType(request.video_type());

  const bool audio_done =
      !requested_audio ||
      request.state(request.audio_type()) == MEDIA_REQUEST_STATE_DONE ||
      request.state(request.audio_type()) == MEDIA_REQUEST_STATE_ERROR;
  if (!audio_done)
    return false;

  const bool video_done =
      !requested_video ||
      request.state(request.video_type()) == MEDIA_REQUEST_STATE_DONE ||
      request.state(request.video_type()) == MEDIA_REQUEST_STATE_ERROR;
  if (!video_done)
    return false;

  return true;
}
