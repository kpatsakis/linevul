void WebRTCAudioDeviceTest::OnGetHardwareInputSampleRate(double* sample_rate) {
  EXPECT_TRUE(audio_util_callback_);
  *sample_rate = audio_util_callback_ ?
      audio_util_callback_->GetAudioInputHardwareSampleRate(
          AudioManagerBase::kDefaultDeviceId) : 0.0;
}
