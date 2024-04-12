void HTMLFormElement::reset() {
  LocalFrame* frame = document().frame();
  if (m_isInResetFunction || !frame)
    return;

  m_isInResetFunction = true;

  if (dispatchEvent(Event::createCancelableBubble(EventTypeNames::reset)) !=
      DispatchEventResult::NotCanceled) {
    m_isInResetFunction = false;
    return;
  }

  const FormAssociatedElement::List& elements = associatedElements();
  for (unsigned i = 0; i < elements.size(); ++i) {
    if (elements[i]->isFormControlElement())
      toHTMLFormControlElement(elements[i])->reset();
  }

  m_isInResetFunction = false;
}
