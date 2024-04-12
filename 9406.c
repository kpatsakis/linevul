RenderWidgetHostView* WebContentsImpl::GetCreatedWidget(int process_id,
                                                        int route_id) {
  auto iter = pending_widget_views_.find(std::make_pair(process_id, route_id));
  if (iter == pending_widget_views_.end()) {
    DCHECK(false);
    return nullptr;
  }

  RenderWidgetHostView* widget_host_view = iter->second;
  pending_widget_views_.erase(std::make_pair(process_id, route_id));

  RenderWidgetHost* widget_host = widget_host_view->GetRenderWidgetHost();
  if (!widget_host->GetProcess()->HasConnection()) {
    return nullptr;
  }

  return widget_host_view;
}
