AccessibilityRole AXLayoutObject::nativeAccessibilityRoleIgnoringAria() const {
  Node* node = m_layoutObject->node();
  LayoutBoxModelObject* cssBox = getLayoutBoxModelObject();

  if ((cssBox && cssBox->isListItem()) || isHTMLLIElement(node))
    return ListItemRole;
  if (m_layoutObject->isListMarker())
    return ListMarkerRole;
  if (m_layoutObject->isBR())
    return LineBreakRole;
  if (m_layoutObject->isText())
    return StaticTextRole;
  if (cssBox && isImageOrAltText(cssBox, node)) {
    if (node && node->isLink())
      return ImageMapRole;
    if (isHTMLInputElement(node))
      return ariaHasPopup() ? PopUpButtonRole : ButtonRole;
    if (isSVGImage())
      return SVGRootRole;
    return ImageRole;
  }
  if (isHTMLCanvasElement(node) && m_layoutObject->isCanvas())
    return CanvasRole;

  if (cssBox && cssBox->isLayoutView())
    return WebAreaRole;

  if (m_layoutObject->isSVGImage())
    return ImageRole;
  if (m_layoutObject->isSVGRoot())
    return SVGRootRole;

  if (m_layoutObject->isTableSection())
    return IgnoredRole;

  if (m_layoutObject->isHR())
    return SplitterRole;

  return AXNodeObject::nativeAccessibilityRoleIgnoringAria();
}
