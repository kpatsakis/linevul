void WebContentsImpl::CreateNewWidget(int32_t render_process_id,
                                      int32_t route_id,
                                      bool is_fullscreen,
                                      mojom::WidgetPtr widget,
                                      blink::WebPopupType popup_type) {
  RenderProcessHost* process = RenderProcessHost::FromID(render_process_id);
  if (!HasMatchingProcess(&frame_tree_, render_process_id)) {
    ReceivedBadMessage(process, bad_message::WCI_NEW_WIDGET_PROCESS_MISMATCH);
    return;
  }

  RenderWidgetHostImpl* widget_host = new RenderWidgetHostImpl(
      this, process, route_id, std::move(widget), IsHidden());

  RenderWidgetHostViewBase* widget_view =
      static_cast<RenderWidgetHostViewBase*>(
          view_->CreateViewForPopupWidget(widget_host));
  if (!widget_view)
    return;
  if (!is_fullscreen) {
    widget_view->SetPopupType(popup_type);
  }
  pending_widget_views_[GlobalRoutingID(render_process_id, route_id)] =
      widget_view;
}
