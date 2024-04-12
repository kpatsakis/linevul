void Textfield::StartBlinkingCursor() {
  DCHECK(ShouldBlinkCursor());
  cursor_blink_timer_.Start(FROM_HERE, Textfield::GetCaretBlinkInterval(), this,
                            &Textfield::OnCursorBlinkTimerFired);
}
