AccessibilityRole AXNodeObject::determineAccessibilityRole() {
  if (!getNode())
    return UnknownRole;

  if ((m_ariaRole = determineAriaRoleAttribute()) != UnknownRole)
    return m_ariaRole;
  if (getNode()->isTextNode())
    return StaticTextRole;

  AccessibilityRole role = nativeAccessibilityRoleIgnoringAria();
  if (role != UnknownRole)
    return role;
  if (getNode()->isElementNode()) {
    Element* element = toElement(getNode());
    if (element->isInCanvasSubtree() && element->supportsFocus())
      return GroupRole;
  }
  return UnknownRole;
}
