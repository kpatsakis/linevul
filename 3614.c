void WebRTCAudioDeviceTest::SetAudioUtilCallback(AudioUtilInterface* callback) {
  audio_hardware::ResetCache();
  audio_util_callback_ = callback;
}
