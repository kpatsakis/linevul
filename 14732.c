void RenderFrameImpl::DidChangeCpuTiming(base::TimeDelta time) {
  for (auto& observer : observers_)
    observer.DidChangeCpuTiming(time);
}
