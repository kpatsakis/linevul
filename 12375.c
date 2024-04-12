void AXObject::ariaLabelledbyElementVector(
    HeapVector<Member<Element>>& elements) const {
  elementsFromAttribute(elements, aria_labelledbyAttr);
  if (!elements.size())
    elementsFromAttribute(elements, aria_labeledbyAttr);
}
