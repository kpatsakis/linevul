void WebMediaPlayerMS::SetSinkId(
    const blink::WebString& sink_id,
    blink::WebSetSinkIdCallbacks* web_callback) {
  DVLOG(1) << __func__;
  DCHECK(thread_checker_.CalledOnValidThread());
  const media::OutputDeviceStatusCB callback =
      media::ConvertToOutputDeviceStatusCB(web_callback);
  if (audio_renderer_) {
    audio_renderer_->SwitchOutputDevice(sink_id.Utf8(), callback);
  } else {
    callback.Run(media::OUTPUT_DEVICE_STATUS_ERROR_INTERNAL);
  }
}
