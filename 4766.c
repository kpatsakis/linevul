static TriState StateStyle(LocalFrame& frame,
                           CSSPropertyID property_id,
                           const char* desired_value) {
  frame.GetDocument()->UpdateStyleAndLayoutIgnorePendingStylesheets();
  if (frame.GetEditor().Behavior().ShouldToggleStyleBasedOnStartOfSelection())
    return frame.GetEditor().SelectionStartHasStyle(property_id, desired_value)
               ? kTrueTriState
               : kFalseTriState;
  return frame.GetEditor().SelectionHasStyle(property_id, desired_value);
}
