NPError WebPluginDelegatePepper::DeviceAudioInitializeContext(
    const NPDeviceContextAudioConfig* config,
    NPDeviceContextAudio* context) {

  if (!render_view_) {
    return NPERR_GENERIC_ERROR;
  }

  scoped_ptr<AudioDeviceContext> audio(new AudioDeviceContext());
  NPError status = audio->Initialize(render_view_->audio_message_filter(),
                                     config, context);
  if (NPERR_NO_ERROR == status) {
    context->reserved =
        reinterpret_cast<void *>(audio_contexts_.Add(audio.release()));
  }
  return status;
}
