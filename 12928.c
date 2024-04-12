HeadlessDevToolsManagerDelegate::NetworkDisable(
    content::DevToolsAgentHost* agent_host,
    int session_id,
    int command_id,
    const base::DictionaryValue* params) {
  HeadlessBrowserContextImpl* browser_context =
      static_cast<HeadlessBrowserContextImpl*>(
          browser_->GetDefaultBrowserContext());
  browser_context->SetNetworkConditions(HeadlessNetworkConditions());
  return CreateSuccessResponse(command_id, nullptr);
}
