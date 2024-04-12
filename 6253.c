void AutofillPopupBaseView::OnGestureEvent(ui::GestureEvent* event) {
  switch (event->type()) {
    case ui::ET_GESTURE_TAP_DOWN:
    case ui::ET_GESTURE_SCROLL_BEGIN:
    case ui::ET_GESTURE_SCROLL_UPDATE:
      if (HitTestPoint(event->location()))
        SetSelection(event->location());
      else
        ClearSelection();
      break;
    case ui::ET_GESTURE_TAP:
    case ui::ET_GESTURE_SCROLL_END:
      if (HitTestPoint(event->location()))
        AcceptSelection(event->location());
      else
        ClearSelection();
      break;
    case ui::ET_GESTURE_TAP_CANCEL:
    case ui::ET_SCROLL_FLING_START:
      ClearSelection();
      break;
    default:
      return;
  }
  event->SetHandled();
}
