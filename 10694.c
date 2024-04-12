const Element* AXObjectCacheImpl::rootAXEditableElement(const Node* node) {
  const Element* result = rootEditableElement(*node);
  const Element* element =
      node->isElementNode() ? toElement(node) : node->parentElement();

  for (; element; element = element->parentElement()) {
    if (nodeIsTextControl(element))
      result = element;
  }

  return result;
}
