RenderWidgetHostView* RenderViewHostDelegateViewHelper::CreateNewWidget(
    int route_id, bool activatable, RenderProcessHost* process) {
  RenderWidgetHost* widget_host =
      new RenderWidgetHost(process, route_id);
  RenderWidgetHostView* widget_view =
      RenderWidgetHostView::CreateViewForWidget(widget_host);
  widget_view->set_activatable(activatable);
  pending_widget_views_[route_id] = widget_view;
  return widget_view;
}
