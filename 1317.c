bool Performance::IsResourceTimingBufferFull() {
  return resource_timing_buffer_.size() >= resource_timing_buffer_size_;
}
