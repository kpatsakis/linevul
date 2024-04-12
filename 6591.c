bool WebContentsImpl::FocusLocationBarByDefault() {
  NavigationEntryImpl* entry = controller_.GetPendingEntry();
  if (controller_.IsInitialNavigation() && entry &&
      !entry->is_renderer_initiated() &&
      entry->GetURL() == url::kAboutBlankURL) {
    return true;
  }
  return delegate_ && delegate_->ShouldFocusLocationBarByDefault(this);
}
