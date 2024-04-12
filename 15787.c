DevToolsAgentHostImpl::DevToolsAgentHostImpl(const std::string& id) : id_(id) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
}
