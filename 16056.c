  void EndScroll(bool is_fling, float velocity_y) {
    IncreaseTimestamp();
    ui::GestureEventDetails event_details =
        is_fling
            ? ui::GestureEventDetails(ui::ET_SCROLL_FLING_START, 0, velocity_y)
            : ui::GestureEventDetails(ui::ET_GESTURE_SCROLL_END);
    ui::GestureEvent event =
        ui::GestureEvent(current_point_.x(), current_point_.y(), ui::EF_NONE,
                         timestamp_, event_details);
    GetShelfLayoutManager()->ProcessGestureEvent(event);
  }
