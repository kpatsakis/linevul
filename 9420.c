bool RenderViewHostImpl::IsRenderViewLive() const {
  return GetProcess()->HasConnection() && renderer_initialized_;
}
