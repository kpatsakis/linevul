void AudioRendererAlgorithm::IncreaseQueueCapacity() {
  audio_buffer_.set_forward_capacity(
      std::min(2 * audio_buffer_.forward_capacity(), kMaxBufferSizeInBytes));
}
