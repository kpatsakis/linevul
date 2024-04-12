WebDevToolsAgentImpl::~WebDevToolsAgentImpl()
{
    ClientMessageLoopAdapter::inspectedViewClosed(m_webViewImpl);
    if (m_attached)
        blink::Platform::current()->currentThread()->removeTaskObserver(this);
}
