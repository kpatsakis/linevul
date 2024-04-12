std::unique_ptr<base::DictionaryValue> HeadlessDevToolsManagerDelegate::Close(
    content::DevToolsAgentHost* agent_host,
    int session_id,
    int command_id,
    const base::DictionaryValue* params) {
  content::BrowserThread::PostTask(
      content::BrowserThread::UI, FROM_HERE,
      base::BindOnce(&HeadlessBrowserImpl::Shutdown, browser_));

  return CreateSuccessResponse(command_id, nullptr);
}
