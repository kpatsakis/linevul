void Textfield::OnGestureEvent(ui::GestureEvent* event) {
  switch (event->type()) {
    case ui::ET_GESTURE_TAP_DOWN:
      RequestFocus();
      ShowImeIfNeeded();
      event->SetHandled();
      break;
    case ui::ET_GESTURE_TAP:
      if (controller_ && controller_->HandleGestureEvent(this, *event)) {
        event->SetHandled();
        return;
      }
      if (event->details().tap_count() == 1) {
        if (touch_selection_controller_ ||
            !GetRenderText()->IsPointInSelection(event->location())) {
          OnBeforeUserAction();
          MoveCursorTo(event->location(), false);
          OnAfterUserAction();
        }
      } else if (event->details().tap_count() == 2) {
        OnBeforeUserAction();
        SelectWordAt(event->location());
        OnAfterUserAction();
      } else {
        OnBeforeUserAction();
        SelectAll(false);
        OnAfterUserAction();
      }
      CreateTouchSelectionControllerAndNotifyIt();
#if defined(OS_WIN)
      if (!read_only()) {
        DCHECK(ui::OnScreenKeyboardDisplayManager::GetInstance());
        ui::OnScreenKeyboardDisplayManager::GetInstance()
            ->DisplayVirtualKeyboard(nullptr);
      }
#endif
      event->SetHandled();
      break;
    case ui::ET_GESTURE_LONG_PRESS:
      if (!GetRenderText()->IsPointInSelection(event->location())) {
        OnBeforeUserAction();
        SelectWordAt(event->location());
        OnAfterUserAction();
        CreateTouchSelectionControllerAndNotifyIt();
        if (touch_selection_controller_)
          event->SetHandled();
      } else {
        DestroyTouchSelection();
        initiating_drag_ = switches::IsTouchDragDropEnabled();
      }
      break;
    case ui::ET_GESTURE_LONG_TAP:
      if (touch_selection_controller_)
        event->SetHandled();
      break;
    case ui::ET_GESTURE_SCROLL_BEGIN:
      touch_handles_hidden_due_to_scroll_ = touch_selection_controller_ != NULL;
      DestroyTouchSelection();
      drag_start_location_ = event->location();
      drag_start_display_offset_ =
          GetRenderText()->GetUpdatedDisplayOffset().x();
      event->SetHandled();
      break;
    case ui::ET_GESTURE_SCROLL_UPDATE: {
      int new_offset = drag_start_display_offset_ + event->location().x() -
                       drag_start_location_.x();
      GetRenderText()->SetDisplayOffset(new_offset);
      SchedulePaint();
      event->SetHandled();
      break;
    }
    case ui::ET_GESTURE_SCROLL_END:
    case ui::ET_SCROLL_FLING_START:
      if (touch_handles_hidden_due_to_scroll_) {
        CreateTouchSelectionControllerAndNotifyIt();
        touch_handles_hidden_due_to_scroll_ = false;
      }
      event->SetHandled();
      break;
    default:
      return;
  }
}
