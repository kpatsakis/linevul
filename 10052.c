int InputMethodController::TextInputFlags() const {
  Element* element = GetDocument().FocusedElement();
  if (!element)
    return kWebTextInputFlagNone;

  int flags = 0;

  const AtomicString& autocomplete =
      element->getAttribute(HTMLNames::autocompleteAttr);
  if (autocomplete == "on")
    flags |= kWebTextInputFlagAutocompleteOn;
  else if (autocomplete == "off")
    flags |= kWebTextInputFlagAutocompleteOff;

  const AtomicString& autocorrect =
      element->getAttribute(HTMLNames::autocorrectAttr);
  if (autocorrect == "on")
    flags |= kWebTextInputFlagAutocorrectOn;
  else if (autocorrect == "off")
    flags |= kWebTextInputFlagAutocorrectOff;

  SpellcheckAttributeState spellcheck = element->GetSpellcheckAttributeState();
  if (spellcheck == kSpellcheckAttributeTrue)
    flags |= kWebTextInputFlagSpellcheckOn;
  else if (spellcheck == kSpellcheckAttributeFalse)
    flags |= kWebTextInputFlagSpellcheckOff;

  if (IsTextControlElement(element)) {
    TextControlElement* text_control = ToTextControlElement(element);
    if (text_control->SupportsAutocapitalize()) {
      DEFINE_STATIC_LOCAL(const AtomicString, none, ("none"));
      DEFINE_STATIC_LOCAL(const AtomicString, characters, ("characters"));
      DEFINE_STATIC_LOCAL(const AtomicString, words, ("words"));
      DEFINE_STATIC_LOCAL(const AtomicString, sentences, ("sentences"));

      const AtomicString& autocapitalize = text_control->autocapitalize();
      if (autocapitalize == none)
        flags |= kWebTextInputFlagAutocapitalizeNone;
      else if (autocapitalize == characters)
        flags |= kWebTextInputFlagAutocapitalizeCharacters;
      else if (autocapitalize == words)
        flags |= kWebTextInputFlagAutocapitalizeWords;
      else if (autocapitalize == sentences)
        flags |= kWebTextInputFlagAutocapitalizeSentences;
      else
        NOTREACHED();
    }
  }

  return flags;
}
