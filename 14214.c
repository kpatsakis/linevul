void WebContentsImpl::LostMouseLock(RenderWidgetHostImpl* render_widget_host) {
  CHECK(mouse_lock_widget_);

  if (mouse_lock_widget_->delegate()->GetAsWebContents() != this)
    return mouse_lock_widget_->delegate()->LostMouseLock(render_widget_host);

  mouse_lock_widget_->SendMouseLockLost();
  for (WebContentsImpl* current = this; current;
       current = current->GetOuterWebContents()) {
    current->mouse_lock_widget_ = nullptr;
  }

  if (delegate_)
    delegate_->LostMouseLock();
}
