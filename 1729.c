void RenderFrameHostImpl::DisableBeforeUnloadHangMonitorForTesting() {
  beforeunload_timeout_.reset();
}
