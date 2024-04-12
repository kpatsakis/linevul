void RenderViewImpl::zoomLevelChanged() {
  bool remember = !webview()->mainFrame()->document().isPluginDocument();
  float zoom_level = webview()->zoomLevel();

  FOR_EACH_OBSERVER(RenderViewObserver, observers_, ZoomLevelChanged());

  Send(new ViewHostMsg_DidZoomURL(
      routing_id_, zoom_level, remember,
      GURL(webview()->mainFrame()->document().url())));
}
