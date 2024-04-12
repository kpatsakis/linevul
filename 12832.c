AXObject* AXLayoutObject::computeParentIfExists() const {
  if (!m_layoutObject)
    return 0;

  if (ariaRoleAttribute() == MenuBarRole)
    return axObjectCache().get(m_layoutObject->parent());

  if (ariaRoleAttribute() == MenuRole) {
    AXObject* parent = menuButtonForMenu();
    if (parent)
      return parent;
  }

  LayoutObject* parentObj = layoutParentObject();
  if (parentObj)
    return axObjectCache().get(parentObj);

  if (isWebArea()) {
    LocalFrame* frame = m_layoutObject->frame();
    return axObjectCache().get(frame->pagePopupOwner());
  }

  return 0;
}
