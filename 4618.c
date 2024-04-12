bool ExecuteScriptInIsolatedWorldAndExtractBool(
    const ToRenderFrameHost& adapter,
    const int world_id,
    const std::string& script,
    bool* result) {
  DCHECK(result);
  std::unique_ptr<base::Value> value;
  if (!ExecuteScriptInIsolatedWorldHelper(adapter.render_frame_host(), world_id,
                                          script, &value) ||
      !value.get()) {
    return false;
  }

  return value->GetAsBoolean(result);
}
