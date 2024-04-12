bool AXNodeObject::isHovered() const {
  if (Node* node = this->getNode())
    return node->isHovered();
  return false;
}
