static bool ExecuteUnderline(LocalFrame& frame,
                             Event*,
                             EditorCommandSource source,
                             const String&) {
  CSSIdentifierValue* underline = CSSIdentifierValue::Create(CSSValueUnderline);
  return ExecuteToggleStyleInList(
      frame, source, InputEvent::InputType::kFormatUnderline,
      CSSPropertyWebkitTextDecorationsInEffect, underline);
}
