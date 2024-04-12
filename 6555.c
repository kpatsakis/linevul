MockRenderProcessHost* TestRenderViewHost::GetProcess() const {
  return static_cast<MockRenderProcessHost*>(RenderViewHostImpl::GetProcess());
}
