void WebContentsImpl::ClearDeviceEmulationSize() {
  RenderWidgetHostView* rwhv = GetMainFrame()->GetView();
  if (!view_size_before_emulation_.IsEmpty() && rwhv &&
      rwhv->GetViewBounds().size() == device_emulation_size_) {
    rwhv->SetSize(view_size_before_emulation_);
  }
  device_emulation_size_ = gfx::Size();
  view_size_before_emulation_ = gfx::Size();
}
