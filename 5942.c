AtomicString PerformanceNavigationTiming::AlpnNegotiatedProtocol() const {
  return resource_timing_info_->FinalResponse().AlpnNegotiatedProtocol();
}
