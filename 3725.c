int WebContentsImpl::GetTopControlsHeight() const {
  return delegate_ ? delegate_->GetTopControlsHeight() : 0;
}
