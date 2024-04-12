void Textfield::SetCursorEnabled(bool enabled) {
  if (GetRenderText()->cursor_enabled() == enabled)
    return;

  GetRenderText()->SetCursorEnabled(enabled);
  UpdateCursorViewPosition();
  UpdateCursorVisibility();
}
