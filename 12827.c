mojom::FrameNavigationControl* RenderFrameHostImpl::GetNavigationControl() {
  if (!navigation_control_)
    GetRemoteAssociatedInterfaces()->GetInterface(&navigation_control_);
  return navigation_control_.get();
}
