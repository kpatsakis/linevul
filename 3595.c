    RenderWidgetHostImpl::GetRootBrowserAccessibilityManager() {
  return delegate_ ? delegate_->GetRootBrowserAccessibilityManager() : NULL;
}
