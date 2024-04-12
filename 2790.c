bool SelectionController::HandleDoubleClick(
    const MouseEventWithHitTestResults& event) {
  TRACE_EVENT0("blink",
               "SelectionController::handleMousePressEventDoubleClick");

  if (!Selection().IsAvailable())
    return false;

  if (!mouse_down_allows_multi_click_)
    return HandleSingleClick(event);

  if (event.Event().button != WebPointerProperties::Button::kLeft)
    return false;

  if (Selection().ComputeVisibleSelectionInDOMTreeDeprecated().IsRange()) {
    selection_state_ = SelectionState::kExtendedSelection;
    return true;
  }
  if (!SelectClosestWordFromMouseEvent(event))
    return true;
  if (!Selection().IsHandleVisible())
    return true;
  frame_->GetEventHandler().ShowNonLocatedContextMenu(nullptr,
                                                      kMenuSourceTouch);
  return true;
}
