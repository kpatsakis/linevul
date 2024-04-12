RenderWidgetHostImpl::GetKeyboardLayoutMap() {
  if (!view_)
    return {};
  return view_->GetKeyboardLayoutMap();
}
