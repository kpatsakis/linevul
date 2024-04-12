void RenderFrameHostImpl::OnJavaScriptExecuteResponse(
    int id, const base::ListValue& result) {
  const base::Value* result_value;
  if (!result.Get(0, &result_value)) {
    NOTREACHED() << "Got bad arguments for OnJavaScriptExecuteResponse";
    return;
  }

  auto it = javascript_callbacks_.find(id);
  if (it != javascript_callbacks_.end()) {
    it->second.Run(result_value);
    javascript_callbacks_.erase(it);
  } else {
    NOTREACHED() << "Received script response for unknown request";
  }
}
