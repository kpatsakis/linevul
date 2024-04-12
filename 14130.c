void RenderFrameImpl::OnStop() {
  DCHECK(frame_);
  frame_->stopLoading();
  if (!frame_->parent())
    FOR_EACH_OBSERVER(RenderViewObserver, render_view_->observers_, OnStop());

  FOR_EACH_OBSERVER(RenderFrameObserver, observers_, OnStop());
}
