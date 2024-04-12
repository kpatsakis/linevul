AXObject* AXLayoutObject::ancestorForWhichThisIsAPresentationalChild() const {
  AXObject* parent = parentObjectIfExists();
  while (parent) {
    if (parent->ariaRoleHasPresentationalChildren())
      break;

    if (parent->isMenuList())
      break;

    parent = parent->parentObjectIfExists();
  }

  return parent;
}
