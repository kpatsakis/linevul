bool AXNodeObject::isGenericFocusableElement() const {
  if (!canSetFocusAttribute())
    return false;

  if (isControl())
    return false;

  if (m_ariaRole != UnknownRole)
    return false;


  if (hasContentEditableAttributeSet())
    return false;

  if (roleValue() == WebAreaRole)
    return false;
  if (isHTMLBodyElement(getNode()))
    return false;

  if (roleValue() == SVGRootRole)
    return false;

  return true;
}
