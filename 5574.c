void HTMLFormControlElement::dispatchBlurEvent(
    Element* newFocusedElement,
    WebFocusType type,
    InputDeviceCapabilities* sourceCapabilities) {
  if (type != WebFocusTypePage)
    m_wasFocusedByMouse = false;
  HTMLElement::dispatchBlurEvent(newFocusedElement, type, sourceCapabilities);
  hideVisibleValidationMessage();
}
