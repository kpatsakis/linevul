void BuildCharEvent(const WebInputEvent* event, NPPepperEvent* npevent) {
  const WebKeyboardEvent* key_event =
      reinterpret_cast<const WebKeyboardEvent*>(event);
  npevent->u.character.modifier = key_event->modifiers;
  DCHECK(sizeof(npevent->u.character.text) == sizeof(key_event->text));
  DCHECK(sizeof(npevent->u.character.unmodifiedText) ==
         sizeof(key_event->unmodifiedText));
  for (size_t i = 0; i < WebKeyboardEvent::textLengthCap; ++i) {
    npevent->u.character.text[i] = key_event->text[i];
    npevent->u.character.unmodifiedText[i] = key_event->unmodifiedText[i];
  }
}
