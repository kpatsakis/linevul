  bool IsStackingDraggedTabs() const {
    return drag_controller_.get() && drag_controller_->started_drag() &&
           (drag_controller_->move_behavior() ==
            TabDragController::MOVE_VISIBLE_TABS);
  }
