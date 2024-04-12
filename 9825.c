void SynchronousCompositorImpl::UpdateFrameMetaData(
    const cc::CompositorFrameMetadata& frame_metadata) {
  RenderWidgetHostViewAndroid* rwhv = static_cast<RenderWidgetHostViewAndroid*>(
      contents_->GetRenderWidgetHostView());
  if (rwhv)
    rwhv->SynchronousFrameMetadata(frame_metadata);
  DeliverMessages();
}
