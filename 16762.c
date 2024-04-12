HeadlessDevToolsManagerDelegate::NetworkDisable(
    content::DevToolsAgentHost* agent_host,
    int session_id,
    int command_id,
    const base::DictionaryValue* params) {
  std::vector<HeadlessBrowserContext*> browser_contexts =
      browser_->GetAllBrowserContexts();
  if (browser_contexts.empty())
    return CreateSuccessResponse(command_id, nullptr);
  SetNetworkConditions(browser_contexts, HeadlessNetworkConditions());
  return CreateSuccessResponse(command_id, nullptr);
}
