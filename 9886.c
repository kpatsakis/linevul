void fillRelationships(AXObject& axObject,
                       protocol::Array<AXProperty>& properties) {
  AXObject::AXObjectVector results;
  axObject.ariaDescribedbyElements(results);
  if (!results.isEmpty())
    properties.addItem(
        createRelatedNodeListProperty(AXRelationshipAttributesEnum::Describedby,
                                      results, aria_describedbyAttr, axObject));
  results.clear();

  axObject.ariaOwnsElements(results);
  if (!results.isEmpty())
    properties.addItem(createRelatedNodeListProperty(
        AXRelationshipAttributesEnum::Owns, results, aria_ownsAttr, axObject));
  results.clear();
}
