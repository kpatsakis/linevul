void AXLayoutObject::addPopupChildren() {
  if (!isHTMLInputElement(getNode()))
    return;
  if (AXObject* axPopup = toHTMLInputElement(getNode())->popupRootAXObject())
    m_children.push_back(axPopup);
}
