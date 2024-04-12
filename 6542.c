HeadlessDevToolsManagerDelegate::GetWindowBounds(
    content::DevToolsAgentHost* agent_host,
    int session_id,
    int command_id,
    const base::DictionaryValue* params) {
  HeadlessWebContentsImpl* web_contents;
  const base::Value* window_id_value = params->FindKey("windowId");
  if (!window_id_value || !window_id_value->is_int())
    return CreateInvalidParamResponse(command_id, "windowId");
  web_contents = browser_->GetWebContentsForWindowId(window_id_value->GetInt());
  if (!web_contents) {
    return CreateErrorResponse(command_id, kErrorServerError,
                               "Browser window not found");
  }

  auto result = std::make_unique<base::DictionaryValue>();
  result->Set("bounds", CreateBoundsDict(web_contents));
  return CreateSuccessResponse(command_id, std::move(result));
}
