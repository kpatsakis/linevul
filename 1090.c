const AXObject::AXObjectVector& AXObject::children() {
  updateChildrenIfNecessary();

  return m_children;
}
