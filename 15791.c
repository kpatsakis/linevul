void AXObjectCacheImpl::handleAriaSelectedChanged(Node* node) {
  AXObject* obj = get(node);
  if (!obj)
    return;

  postNotification(obj, AXCheckedStateChanged);

  AXObject* listbox = obj->parentObjectUnignored();
  if (listbox && listbox->roleValue() == ListBoxRole)
    postNotification(listbox, AXSelectedChildrenChanged);
}
