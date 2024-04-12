void AXObjectCacheImpl::handleAttributeChanged(const QualifiedName& attrName,
                                               Element* element) {
  if (attrName == roleAttr)
    handleAriaRoleChanged(element);
  else if (attrName == altAttr || attrName == titleAttr)
    textChanged(element);
  else if (attrName == forAttr && isHTMLLabelElement(*element))
    labelChanged(element);
  else if (attrName == idAttr)
    updateTreeIfElementIdIsAriaOwned(element);

  if (!attrName.localName().startsWith("aria-"))
    return;

  if (attrName == aria_activedescendantAttr)
    handleActiveDescendantChanged(element);
  else if (attrName == aria_valuenowAttr || attrName == aria_valuetextAttr)
    postNotification(element, AXObjectCacheImpl::AXValueChanged);
  else if (attrName == aria_labelAttr || attrName == aria_labeledbyAttr ||
           attrName == aria_labelledbyAttr)
    textChanged(element);
  else if (attrName == aria_checkedAttr)
    checkedStateChanged(element);
  else if (attrName == aria_selectedAttr)
    handleAriaSelectedChanged(element);
  else if (attrName == aria_expandedAttr)
    handleAriaExpandedChange(element);
  else if (attrName == aria_hiddenAttr)
    childrenChanged(element->parentNode());
  else if (attrName == aria_invalidAttr)
    postNotification(element, AXObjectCacheImpl::AXInvalidStatusChanged);
  else if (attrName == aria_ownsAttr)
    childrenChanged(element);
  else
    postNotification(element, AXObjectCacheImpl::AXAriaAttributeChanged);
}
