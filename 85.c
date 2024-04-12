void RenderFrameHostImpl::OnExitFullscreen() {
  delegate_->ExitFullscreenMode(/* will_cause_resize */ true);

  render_view_host_->GetWidget()->SynchronizeVisualProperties();
}
