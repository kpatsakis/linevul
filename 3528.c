void RenderProcessHostImpl::ResumeDeferredNavigation(
    const GlobalRequestID& request_id) {
  widget_helper_->ResumeDeferredNavigation(request_id);
}
