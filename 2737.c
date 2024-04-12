void RenderWidgetHostImpl::WasResized(bool scroll_focused_node_into_view) {
  if (resize_ack_pending_ || !process_->HasConnection() || !view_ ||
      !view_->HasSize() || !renderer_initialized_ || auto_resize_enabled_ ||
      !delegate_) {
    return;
  }

  std::unique_ptr<ResizeParams> params(new ResizeParams);
  if (!GetResizeParams(params.get()))
    return;
  params->scroll_focused_node_into_view = scroll_focused_node_into_view;

  ScreenInfo screen_info = params->screen_info;
  bool width_changed =
      !old_resize_params_ ||
      old_resize_params_->new_size.width() != params->new_size.width();
  if (Send(new ViewMsg_Resize(routing_id_, *params))) {
    resize_ack_pending_ = params->needs_resize_ack;
    next_resize_needs_resize_ack_ = false;
    old_resize_params_.swap(params);
  }

  if (delegate_)
    delegate_->RenderWidgetWasResized(this, screen_info, width_changed);
}
