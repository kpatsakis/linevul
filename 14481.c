void RenderWidgetHostViewGtk::ModifyEventMovementAndCoords(
    WebKit::WebMouseEvent* event) {
  event->movementX = event->globalX - global_mouse_position_.x();
  event->movementY = event->globalY - global_mouse_position_.y();

  if (mouse_is_being_warped_to_unlocked_position_) {
    event->movementX = 0;
    event->movementY = 0;
    if (MovedToPoint(*event, unlocked_global_mouse_position_))
      mouse_is_being_warped_to_unlocked_position_ = false;
  }

  global_mouse_position_.SetPoint(event->globalX, event->globalY);

  if (mouse_locked_) {
    event->x = unlocked_mouse_position_.x();
    event->y = unlocked_mouse_position_.y();
    event->windowX = unlocked_mouse_position_.x();
    event->windowY = unlocked_mouse_position_.y();
    event->globalX = unlocked_global_mouse_position_.x();
    event->globalY = unlocked_global_mouse_position_.y();
  } else {
    unlocked_mouse_position_.SetPoint(event->windowX, event->windowY);
    unlocked_global_mouse_position_.SetPoint(event->globalX, event->globalY);
  }
}
