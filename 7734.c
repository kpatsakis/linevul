void Editor::applyStyleToSelection(StylePropertySet* style,
                                   InputEvent::InputType inputType) {
  if (!style || style->isEmpty() || !canEditRichly())
    return;

  applyStyle(style, inputType);
}
