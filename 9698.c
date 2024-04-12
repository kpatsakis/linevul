void TabletModeWindowManager::OnWindowHierarchyChanged(
    const HierarchyChangeParams& params) {
  if (params.new_parent && IsContainerWindow(params.new_parent) &&
      !base::Contains(window_state_map_, params.target)) {
    if (!params.target->IsVisible()) {
      if (!base::Contains(added_windows_, params.target)) {
        added_windows_.insert(params.target);
        params.target->AddObserver(this);
      }
      return;
    }
    TrackWindow(params.target);
    if (base::Contains(window_state_map_, params.target)) {
      wm::WMEvent event(wm::WM_EVENT_ADDED_TO_WORKSPACE);
      wm::GetWindowState(params.target)->OnWMEvent(&event);
    }
  }
}
