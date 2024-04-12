bool HTMLMediaElement::IsURLAttribute(const Attribute& attribute) const {
  return attribute.GetName() == kSrcAttr ||
         HTMLElement::IsURLAttribute(attribute);
}
