void AXObject::detach() {
  clearChildren();

  m_axObjectCache = nullptr;
}
