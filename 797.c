RenderWidgetHostViewAura::~RenderWidgetHostViewAura() {
  if (!shared_surface_handle_.is_null()) {
    ImageTransportFactory* factory = ImageTransportFactory::GetInstance();
    factory->DestroySharedSurfaceHandle(shared_surface_handle_);
    factory->RemoveObserver(this);
  }
  window_->RemoveObserver(window_observer_.get());
  UnlockMouse();
  if (popup_type_ != WebKit::WebPopupTypeNone && popup_parent_host_view_) {
    DCHECK(popup_parent_host_view_->popup_child_host_view_ == NULL ||
           popup_parent_host_view_->popup_child_host_view_ == this);
    popup_parent_host_view_->popup_child_host_view_ = NULL;
  }
  if (popup_child_host_view_) {
    DCHECK(popup_child_host_view_->popup_parent_host_view_ == NULL ||
           popup_child_host_view_->popup_parent_host_view_ == this);
    popup_child_host_view_->popup_parent_host_view_ = NULL;
  }
  aura::client::SetTooltipText(window_, NULL);
  gfx::Screen::GetScreenFor(window_)->RemoveObserver(this);

  DetachFromInputMethod();
}
