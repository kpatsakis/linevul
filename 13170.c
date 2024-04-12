CSSStyleSheet* Document::createEmptyCSSStyleSheet(
    ScriptState* script_state,
    ExceptionState& exception_state) {
  return Document::createEmptyCSSStyleSheet(
      script_state, CSSStyleSheetInit::Create(), exception_state);
}
