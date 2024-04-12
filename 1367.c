RenderFrameImpl::JavaScriptIsolatedWorldRequest::JavaScriptIsolatedWorldRequest(
    int id,
    bool notify_result,
    int routing_id,
    base::WeakPtr<RenderFrameImpl> render_frame_impl)
    : id_(id),
      notify_result_(notify_result),
      routing_id_(routing_id),
      render_frame_impl_(render_frame_impl) {
}
