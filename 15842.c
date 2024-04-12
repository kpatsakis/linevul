void RenderWidgetHostImpl::SetTouchEventEmulationEnabled(
    bool enabled, ui::GestureProviderConfigType config_type) {
  if (enabled) {
    if (!touch_emulator_) {
      touch_emulator_.reset(new TouchEmulator(
          this,
          view_.get() ? content::GetScaleFactorForView(view_.get()) : 1.0f));
    }
    touch_emulator_->Enable(config_type);
  } else {
    if (touch_emulator_)
      touch_emulator_->Disable();
  }
}
