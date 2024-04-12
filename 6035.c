Response PageHandler::StartScreencast(Maybe<std::string> format,
                                      Maybe<int> quality,
                                      Maybe<int> max_width,
                                      Maybe<int> max_height,
                                      Maybe<int> every_nth_frame) {
  WebContentsImpl* web_contents = GetWebContents();
  if (!web_contents)
    return Response::InternalError();
  RenderWidgetHostImpl* widget_host =
      host_ ? host_->GetRenderWidgetHost() : nullptr;
  if (!widget_host)
    return Response::InternalError();

  screencast_enabled_ = true;
  screencast_format_ = format.fromMaybe(kPng);
  screencast_quality_ = quality.fromMaybe(kDefaultScreenshotQuality);
  if (screencast_quality_ < 0 || screencast_quality_ > 100)
    screencast_quality_ = kDefaultScreenshotQuality;
  screencast_max_width_ = max_width.fromMaybe(-1);
  screencast_max_height_ = max_height.fromMaybe(-1);
  ++session_id_;
  frame_counter_ = 0;
  frames_in_flight_ = 0;
  capture_every_nth_frame_ = every_nth_frame.fromMaybe(1);
  bool visible = !widget_host->is_hidden();
  NotifyScreencastVisibility(visible);

  if (video_consumer_) {
    gfx::Size surface_size = gfx::Size();
    RenderWidgetHostViewBase* const view =
        static_cast<RenderWidgetHostViewBase*>(host_->GetView());
    if (view) {
      surface_size = view->GetCompositorViewportPixelSize();
      last_surface_size_ = surface_size;
    }

    gfx::Size snapshot_size = DetermineSnapshotSize(
        surface_size, screencast_max_width_, screencast_max_height_);
    if (!snapshot_size.IsEmpty())
      video_consumer_->SetMinAndMaxFrameSize(snapshot_size, snapshot_size);

    video_consumer_->StartCapture();
    return Response::FallThrough();
  }

  if (!visible)
    return Response::FallThrough();

  if (has_compositor_frame_metadata_) {
    InnerSwapCompositorFrame();
  } else {
    widget_host->Send(
        new WidgetMsg_ForceRedraw(widget_host->GetRoutingID(), 0));
  }
  return Response::FallThrough();
}
