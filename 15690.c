WebKeyboardEvent* BuildKeyEvent(const PP_InputEvent& event) {
  WebKeyboardEvent* key_event = new WebKeyboardEvent();
  switch (event.type) {
    case PP_INPUTEVENT_TYPE_RAWKEYDOWN:
      key_event->type = WebInputEvent::RawKeyDown;
      break;
    case PP_INPUTEVENT_TYPE_KEYDOWN:
      key_event->type = WebInputEvent::KeyDown;
      break;
    case PP_INPUTEVENT_TYPE_KEYUP:
      key_event->type = WebInputEvent::KeyUp;
      break;
    default:
      NOTREACHED();
  }
  key_event->timeStampSeconds = event.time_stamp;
  key_event->modifiers = event.u.key.modifier;
  key_event->windowsKeyCode = event.u.key.key_code;
  return key_event;
}
