void RenderViewHostImpl::OnDocumentAvailableInMainFrame() {
  delegate_->DocumentAvailableInMainFrame(this);
}
