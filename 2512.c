void WebContentsImpl::SetDelegate(WebContentsDelegate* delegate) {
  if (delegate == delegate_)
    return;
  if (delegate_)
    delegate_->Detach(this);
  delegate_ = delegate;
  if (delegate_) {
    delegate_->Attach(this);
    if (view_)
      view_->SetOverscrollControllerEnabled(CanOverscrollContent());
  }
}
