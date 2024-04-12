void InspectorAccessibilityAgent::addChildren(
    AXObject& axObject,
    AXObject* inspectedAXObject,
    std::unique_ptr<protocol::Array<AXNodeId>>& childIds,
    std::unique_ptr<protocol::Array<AXNode>>& nodes,
    AXObjectCacheImpl& cache) const {
  if (inspectedAXObject && inspectedAXObject->accessibilityIsIgnored() &&
      &axObject == inspectedAXObject->parentObjectUnignored()) {
    childIds->addItem(String::number(inspectedAXObject->axObjectID()));
    return;
  }

  const AXObject::AXObjectVector& children = axObject.children();
  for (unsigned i = 0; i < children.size(); i++) {
    AXObject& childAXObject = *children[i].get();
    childIds->addItem(String::number(childAXObject.axObjectID()));
    if (&childAXObject == inspectedAXObject)
      continue;
    if (&axObject != inspectedAXObject &&
        (axObject.getNode() ||
         axObject.parentObjectUnignored() != inspectedAXObject)) {
      continue;
    }

    std::unique_ptr<AXNode> childNode = buildProtocolAXObject(
        childAXObject, inspectedAXObject, true, nodes, cache);
    nodes->addItem(std::move(childNode));
  }
}
