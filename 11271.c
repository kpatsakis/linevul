bool IsTabDraggingSourceWindow(aura::Window* window) {
  if (!window)
    return false;

  MruWindowTracker::WindowList window_list =
      Shell::Get()->mru_window_tracker()->BuildMruWindowList(kActiveDesk);
  if (window_list.empty())
    return false;

  aura::Window* dragged_window = nullptr;
  for (auto* window : window_list) {
    if (wm::IsDraggingTabs(window)) {
      dragged_window = window;
      break;
    }
  }
  if (!dragged_window)
    return false;

  return dragged_window->GetProperty(ash::kTabDraggingSourceWindowKey) ==
         window;
}
