bool RenderProcessHostImpl::HasConnection() const {
  return is_initialized_ && !is_dead_;
}
