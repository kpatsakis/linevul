void AudioRendererAlgorithm::AlignToFrameBoundary(int* value) {
  (*value) -= ((*value) % bytes_per_frame_);
}
