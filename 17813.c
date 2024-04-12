void RenderFrameHostImpl::ExecuteJavaScriptInIsolatedWorld(
    const base::string16& javascript,
    const JavaScriptResultCallback& callback,
    int world_id) {
  if (world_id <= ISOLATED_WORLD_ID_GLOBAL ||
      world_id > ISOLATED_WORLD_ID_MAX) {
    NOTREACHED();
    return;
  }

  int key = 0;
  bool request_reply = false;
  if (!callback.is_null()) {
    request_reply = true;
    key = g_next_javascript_callback_id++;
    javascript_callbacks_.insert(std::make_pair(key, callback));
  }

  Send(new FrameMsg_JavaScriptExecuteRequestInIsolatedWorld(
      routing_id_, javascript, key, request_reply, world_id));
}
