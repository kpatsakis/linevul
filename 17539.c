void WebLocalFrameImpl::BindDevToolsAgentRequest(
    mojom::blink::DevToolsAgentAssociatedRequest request) {
  if (!dev_tools_agent_)
    dev_tools_agent_ = WebDevToolsAgentImpl::CreateForFrame(this);
  dev_tools_agent_->BindRequest(std::move(request));
}
