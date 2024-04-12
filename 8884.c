static uint32 SelectSamplesPerPacket(AudioParameters params) {
  int samples = kMinSamplesPerHardwarePacket;
  while (samples <= kMaxSamplesPerHardwarePacket &&
         samples * base::Time::kMillisecondsPerSecond <
         params.sample_rate * kMillisecondsPerHardwarePacket) {
    samples *= 2;
  }
  return samples;
}
