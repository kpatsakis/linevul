void WindowTreeHostManager::CreateOrUpdateMirroringDisplay(
    const DisplayInfoList& info_list) {
  if (GetDisplayManager()->IsInMirrorMode() ||
      GetDisplayManager()->IsInUnifiedMode()) {
    mirror_window_controller_->UpdateWindow(info_list);
    cursor_window_controller_->UpdateContainer();
  } else {
    NOTREACHED();
  }
}
