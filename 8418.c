bool RenderWidgetHostImpl::IsMouseLocked() const {
  return view_ ? view_->IsMouseLocked() : false;
}
