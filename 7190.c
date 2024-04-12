void RenderFrameImpl::OnJavaScriptExecuteRequestInIsolatedWorld(
    const base::string16& jscript,
    int id,
    bool notify_result,
    int world_id) {
  TRACE_EVENT_INSTANT0("test_tracing",
                       "OnJavaScriptExecuteRequestInIsolatedWorld",
                       TRACE_EVENT_SCOPE_THREAD);

  if (world_id <= ISOLATED_WORLD_ID_GLOBAL ||
      world_id > ISOLATED_WORLD_ID_MAX) {
    NOTREACHED();
    return;
  }

  v8::HandleScope handle_scope(v8::Isolate::GetCurrent());
  WebScriptSource script = WebScriptSource(jscript);
  JavaScriptIsolatedWorldRequest* request = new JavaScriptIsolatedWorldRequest(
      id, notify_result, routing_id_, weak_factory_.GetWeakPtr());
  frame_->requestExecuteScriptInIsolatedWorld(world_id, &script, 1, 0, false,
                                              request);
}
