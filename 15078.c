void RenderWidgetHostImpl::OnMsgDidActivateAcceleratedCompositing(
    bool activated) {
  TRACE_EVENT1("renderer_host",
               "RenderWidgetHostImpl::OnMsgDidActivateAcceleratedCompositing",
               "activated", activated);
  is_accelerated_compositing_active_ = activated;
  if (view_)
    view_->OnAcceleratedCompositingStateChange();
}
