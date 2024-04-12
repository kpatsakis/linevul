void RenderWidgetHostViewAura::OnBlur() {
  host_->SetActive(false);
  host_->Blur();

  DetachFromInputMethod();
  host_->SetInputMethodActive(false);

  if (is_fullscreen_ && !in_shutdown_) {
    in_shutdown_ = true;
    host_->Shutdown();
  }
}
