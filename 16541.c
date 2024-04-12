void AXObjectCacheImpl::handleValueChanged(Node* node) {
  postNotification(node, AXObjectCache::AXValueChanged);
}
