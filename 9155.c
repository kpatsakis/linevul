void Shell::SetTouchHudProjectionEnabled(bool enabled) {
  if (is_touch_hud_projection_enabled_ == enabled)
    return;

  is_touch_hud_projection_enabled_ = enabled;
  FOR_EACH_OBSERVER(ShellObserver, observers_,
                    OnTouchHudProjectionToggled(enabled));
}
