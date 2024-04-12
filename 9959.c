void RenderWidgetHostViewAura::OnDeviceScaleFactorChanged(
    float device_scale_factor) {
  if (!host_)
    return;

  device_scale_factor_ = device_scale_factor;
  BackingStoreAura* backing_store = static_cast<BackingStoreAura*>(
      host_->GetBackingStore(false));
  if (backing_store)  // NULL in hardware path.
    backing_store->ScaleFactorChanged(device_scale_factor);

  UpdateScreenInfo(window_);
  host_->NotifyScreenInfoChanged();
  current_cursor_.SetScaleFactor(device_scale_factor);
}
