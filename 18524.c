void AXObjectCacheImpl::updateCacheAfterNodeIsAttached(Node* node) {
  get(node);
  if (node->isElementNode())
    updateTreeIfElementIdIsAriaOwned(toElement(node));
}
