Document* AXLayoutObject::getDocument() const {
  if (!getLayoutObject())
    return nullptr;
  return &getLayoutObject()->document();
}
