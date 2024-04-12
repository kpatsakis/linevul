void RenderWidgetHostImpl::SetView(RenderWidgetHostViewBase* view) {
  if (view) {
    view_ = view->GetWeakPtr();
    if (enable_viz_) {
      if (!create_frame_sink_callback_.is_null())
        std::move(create_frame_sink_callback_).Run(view_->GetFrameSinkId());
    } else {
      if (renderer_compositor_frame_sink_.is_bound()) {
        view->DidCreateNewRendererCompositorFrameSink(
            renderer_compositor_frame_sink_.get());
      }
      if (needs_begin_frames_)
        view_->SetNeedsBeginFrames(needs_begin_frames_);
    }
  } else {
    view_.reset();
  }

  synthetic_gesture_controller_.reset();
}
