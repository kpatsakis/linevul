std::string GetPlacementOverride(aura::Window* window) {
  gfx::Rect* bounds = window->GetProperty(kRestoreBoundsOverrideKey);
  if (bounds) {
    gfx::Rect restore_bounds = *bounds;
    ui::WindowShowState restore_state = ToWindowShowState(
        window->GetProperty(kRestoreWindowStateTypeOverrideKey));
    return GetPlacementString(restore_bounds, restore_state);
  }
  return std::string();
}
