int32 RenderThread::RoutingIDForCurrentContext() {
  int32 routing_id = MSG_ROUTING_CONTROL;
  if (v8::Context::InContext()) {
    WebFrame* frame = WebFrame::frameForCurrentContext();
    if (frame) {
      RenderView* view = RenderView::FromWebView(frame->view());
      if (view)
        routing_id = view->routing_id();
    }
  } else {
    DLOG(WARNING) << "Not called within a script context!";
  }
  return routing_id;
}
