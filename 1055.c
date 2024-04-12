void AXObject::tokenVectorFromAttribute(Vector<String>& tokens,
                                        const QualifiedName& attribute) const {
  Node* node = this->getNode();
  if (!node || !node->isElementNode())
    return;

  String attributeValue = getAttribute(attribute).getString();
  if (attributeValue.isEmpty())
    return;

  attributeValue.simplifyWhiteSpace();
  attributeValue.split(' ', tokens);
}
