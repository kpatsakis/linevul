void WebRTCAudioDeviceTest::OnGetHardwareSampleRate(double* sample_rate) {
  EXPECT_TRUE(audio_util_callback_);
  *sample_rate = audio_util_callback_ ?
      audio_util_callback_->GetAudioHardwareSampleRate() : 0.0;
}
