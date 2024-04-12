void InputMethodIBus::OnShowPreeditText(IBusInputContext* context) {
  DCHECK_EQ(context_, context);
  if (suppress_next_result_ || IsTextInputTypeNone())
    return;

  composing_text_ = true;
}
