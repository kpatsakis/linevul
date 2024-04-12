void HTMLFormControlElement::RequiredAttributeChanged() {
  SetNeedsValidityCheck();
  PseudoStateChanged(CSSSelector::kPseudoRequired);
  PseudoStateChanged(CSSSelector::kPseudoOptional);
  if (AXObjectCache* cache = GetDocument().ExistingAXObjectCache())
    cache->CheckedStateChanged(this);
}
