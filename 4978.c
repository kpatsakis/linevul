const char* RendererSchedulerImpl::VirtualTimePolicyToString(
    VirtualTimePolicy virtual_time_policy) {
  switch (virtual_time_policy) {
    case VirtualTimePolicy::kAdvance:
      return "ADVANCE";
    case VirtualTimePolicy::kPause:
      return "PAUSE";
    case VirtualTimePolicy::kDeterministicLoading:
      return "DETERMINISTIC_LOADING";
    default:
      NOTREACHED();
      return nullptr;
  }
}
