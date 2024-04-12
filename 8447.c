void HTMLMediaElement::AudioSourceProviderImpl::ProvideInput(
    AudioBus* bus,
    size_t frames_to_process) {
  DCHECK(bus);

  MutexTryLocker try_locker(provide_input_lock);
  if (!try_locker.Locked() || !web_audio_source_provider_ || !client_.Get()) {
    bus->Zero();
    return;
  }

  size_t n = bus->NumberOfChannels();
  WebVector<float*> web_audio_data(n);
  for (size_t i = 0; i < n; ++i)
    web_audio_data[i] = bus->Channel(i)->MutableData();

  web_audio_source_provider_->ProvideInput(web_audio_data, frames_to_process);
}
