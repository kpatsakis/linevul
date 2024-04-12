void RenderWidgetHostImpl::WasResized() {
  if (resize_ack_pending_ || !process_->HasConnection() || !view_ ||
      !renderer_initialized_ || should_auto_resize_) {
    return;
  }

  gfx::Rect view_bounds = view_->GetViewBounds();
  gfx::Size new_size(view_bounds.size());

  bool was_fullscreen = is_fullscreen_;
  is_fullscreen_ = IsFullscreen();
  bool fullscreen_changed = was_fullscreen != is_fullscreen_;
  bool size_changed = new_size != current_size_;

  if (!size_changed && !fullscreen_changed)
    return;

  if (in_flight_size_ != gfx::Size() && new_size == in_flight_size_ &&
      !fullscreen_changed)
    return;

  if (!new_size.IsEmpty() && size_changed)
    resize_ack_pending_ = true;

  if (!Send(new ViewMsg_Resize(routing_id_, new_size,
          GetRootWindowResizerRect(), is_fullscreen_))) {
    resize_ack_pending_ = false;
  } else {
    in_flight_size_ = new_size;
  }
}
