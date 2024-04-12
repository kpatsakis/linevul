DevToolsAgentHostImpl::~DevToolsAgentHostImpl() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  NotifyDestroyed();
}
