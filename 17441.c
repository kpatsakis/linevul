void ShelfLayoutManager::UpdateAutoHideForMouseEvent(ui::MouseEvent* event,
                                                     aura::Window* target) {
  in_mouse_drag_ = (event->type() == ui::ET_MOUSE_DRAGGED ||
                    (in_mouse_drag_ && event->type() != ui::ET_MOUSE_RELEASED &&
                     event->type() != ui::ET_MOUSE_CAPTURE_CHANGED)) &&
                   !IsShelfWindow(target) && !IsStatusAreaWindow(target);

  if (visibility_state() != SHELF_AUTO_HIDE || in_shutdown_)
    return;

  if (event->type() == ui::ET_MOUSE_PRESSED ||
      (event->type() == ui::ET_MOUSE_MOVED &&
       GetVisibleShelfBounds().Contains(
           display::Screen::GetScreen()->GetCursorScreenPoint()))) {
    UpdateAutoHideState();
  }
}
