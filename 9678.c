void ShelfLayoutManager::ProcessGestureEventOfAutoHideShelf(
    ui::GestureEvent* event,
    aura::Window* target) {
  const bool is_shelf_window = IsShelfWindow(target);
  if (IsVisible() || in_shutdown_) {
    if (!is_shelf_window && !IsStatusAreaWindow(target) &&
        visibility_state() == SHELF_AUTO_HIDE &&
        state_.auto_hide_state == SHELF_AUTO_HIDE_SHOWN &&
        event->type() == ui::ET_GESTURE_TAP) {
      UpdateAutoHideState();
    }
    return;
  }

  if (is_shelf_window) {
    ui::GestureEvent event_in_screen(*event);
    gfx::Point location_in_screen(event->location());
    ::wm::ConvertPointToScreen(target, &location_in_screen);
    event_in_screen.set_location(location_in_screen);
    if (ProcessGestureEvent(event_in_screen))
      event->StopPropagation();
  }
}
