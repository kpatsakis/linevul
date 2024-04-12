void Editor::replaceSelectionWithText(const String& text,
                                      bool selectReplacement,
                                      bool smartReplace,
                                      InputEvent::InputType inputType) {
  replaceSelectionWithFragment(createFragmentFromText(selectedRange(), text),
                               selectReplacement, smartReplace, true,
                               inputType);
}
