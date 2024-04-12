InputHandlerProxy::EventDisposition InputHandlerProxy::HitTestTouchEvent(
    const blink::WebTouchEvent& touch_event,
    bool* is_touching_scrolling_layer,
    cc::TouchAction* white_listed_touch_action) {
  *is_touching_scrolling_layer = false;
  EventDisposition result = DROP_EVENT;
  for (size_t i = 0; i < touch_event.touches_length; ++i) {
    if (touch_event.touch_start_or_first_touch_move)
      DCHECK(white_listed_touch_action);
    else
      DCHECK(!white_listed_touch_action);

    if (touch_event.GetType() == WebInputEvent::kTouchStart &&
        touch_event.touches[i].state != WebTouchPoint::kStatePressed) {
      continue;
    }

    cc::TouchAction touch_action = cc::kTouchActionAuto;
    cc::InputHandler::TouchStartOrMoveEventListenerType event_listener_type =
        input_handler_->EventListenerTypeForTouchStartOrMoveAt(
            gfx::Point(touch_event.touches[i].PositionInWidget().x,
                       touch_event.touches[i].PositionInWidget().y),
            &touch_action);
    if (white_listed_touch_action)
      *white_listed_touch_action &= touch_action;

    if (event_listener_type !=
        cc::InputHandler::TouchStartOrMoveEventListenerType::NO_HANDLER) {
      *is_touching_scrolling_layer =
          event_listener_type ==
          cc::InputHandler::TouchStartOrMoveEventListenerType::
              HANDLER_ON_SCROLLING_LAYER;
      if (compositor_touch_action_enabled_ && white_listed_touch_action &&
          *white_listed_touch_action != cc::kTouchActionNone)
        result = DID_HANDLE_NON_BLOCKING;
      else
        result = DID_NOT_HANDLE;
      break;
    }
  }

  if (result == DROP_EVENT) {
    switch (input_handler_->GetEventListenerProperties(
        cc::EventListenerClass::kTouchStartOrMove)) {
      case cc::EventListenerProperties::kPassive:
        result = DID_HANDLE_NON_BLOCKING;
        break;
      case cc::EventListenerProperties::kBlocking:
        result = DROP_EVENT;
        break;
      case cc::EventListenerProperties::kBlockingAndPassive:
        result = DID_HANDLE_NON_BLOCKING;
        break;
      case cc::EventListenerProperties::kNone:
        result = DROP_EVENT;
        break;
      default:
        NOTREACHED();
        result = DROP_EVENT;
        break;
    }
  }

  if (result == DROP_EVENT &&
      (skip_touch_filter_all_ ||
       (skip_touch_filter_discrete_ &&
        touch_event.GetType() == WebInputEvent::kTouchStart)))
    result = DID_HANDLE_NON_BLOCKING;

  if (touch_result_ == kEventDispositionUndefined ||
      touch_result_ == DROP_EVENT || result == DID_NOT_HANDLE)
    touch_result_ = result;
  return result;
}
