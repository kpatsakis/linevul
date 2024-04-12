void ShelfLayoutManager::StopAutoHideTimer() {
  auto_hide_timer_.Stop();
  mouse_over_shelf_when_auto_hide_timer_started_ = false;
}
