void AXLayoutObject::ariaLabelledbyElements(AXObjectVector& labelledby) const {
  accessibilityChildrenFromAttribute(aria_labelledbyAttr, labelledby);
}
