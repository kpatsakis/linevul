static bool ExecuteToggleBold(LocalFrame& frame,
                              Event*,
                              EditorCommandSource source,
                              const String&) {
  return ExecuteToggleStyle(frame, source, InputEvent::InputType::kFormatBold,
                            CSSPropertyFontWeight, "normal", "bold");
}
