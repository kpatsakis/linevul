bool HTMLInputElement::IsURLAttribute(const Attribute& attribute) const {
  return attribute.GetName() == srcAttr ||
         attribute.GetName() == formactionAttr ||
         TextControlElement::IsURLAttribute(attribute);
}
