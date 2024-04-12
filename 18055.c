void WebContentsImpl::DidChangeVisibleSecurityState() {
  if (delegate_) {
    delegate_->VisibleSecurityStateChanged(this);
    for (auto& observer : observers_)
      observer.DidChangeVisibleSecurityState();
  }
}
