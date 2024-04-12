bool AXNodeObject::isInPageLinkTarget() const {
  if (!m_node || !m_node->isElementNode())
    return false;
  Element* element = toElement(m_node);
  if (element->containingShadowRoot())
    return false;

  if (isHTMLAnchorElement(element)) {
    HTMLAnchorElement* htmlElement = toHTMLAnchorElement(element);
    return htmlElement->hasName() || htmlElement->hasID();
  }

  if (element->hasID() && (isLandmarkRelated() || isHTMLDivElement(element)))
    return true;
  return false;
}
