void InputMethodIBus::UpdateContextFocusState() {
  const bool old_context_focused = context_focused_;
  switch (GetTextInputType()) {
    case TEXT_INPUT_TYPE_NONE:
    case TEXT_INPUT_TYPE_PASSWORD:
      context_focused_ = false;
      break;
    default:
      context_focused_ = true;
      break;
  }
  if (!GetEngine())
    return;

  if (old_context_focused && !context_focused_) {
    GetEngine()->FocusOut();
  } else if (!old_context_focused && context_focused_) {
    GetEngine()->FocusIn();
    OnCaretBoundsChanged(GetTextInputClient());
  }
}
