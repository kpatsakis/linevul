static bool ExecuteMakeTextWritingDirectionLeftToRight(LocalFrame& frame,
                                                       Event*,
                                                       EditorCommandSource,
                                                       const String&) {
  MutableStylePropertySet* style =
      MutableStylePropertySet::Create(kHTMLQuirksMode);
  style->SetProperty(CSSPropertyUnicodeBidi, CSSValueIsolate);
  style->SetProperty(CSSPropertyDirection, CSSValueLtr);
  frame.GetEditor().ApplyStyle(
      style, InputEvent::InputType::kFormatSetBlockTextDirection);
  return true;
}
