bool OmniboxViewViews::SkipDefaultKeyEventProcessing(
    const ui::KeyEvent& event) {
  if (views::FocusManager::IsTabTraversalKeyEvent(event) &&
      ((model()->is_keyword_hint() && !event.IsShiftDown()) ||
       model()->popup_model()->IsOpen())) {
    return true;
  }
  if (event.key_code() == ui::VKEY_ESCAPE)
    return model()->WillHandleEscapeKey();
  return Textfield::SkipDefaultKeyEventProcessing(event);
}
