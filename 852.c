AudioInputDeviceManager* MediaStreamManager::audio_input_device_manager() {
  DCHECK(audio_input_device_manager_.get());
  return audio_input_device_manager_.get();
}
