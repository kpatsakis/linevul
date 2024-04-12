void AXObjectCacheImpl::listboxSelectedChildrenChanged(
    HTMLSelectElement* select) {
  postNotification(select, AXSelectedChildrenChanged);
}
