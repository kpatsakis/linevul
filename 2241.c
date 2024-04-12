bool ContentSecurityPolicy::isNonceableElement(const Element* element) {
  if (RuntimeEnabledFeatures::hideNonceContentAttributeEnabled() &&
      isHTMLScriptElement(element)) {
    if (toHTMLScriptElement(element)->nonce().isNull())
      return false;
  } else if (!element->fastHasAttribute(HTMLNames::nonceAttr)) {
    return false;
  }

  bool nonceable = true;

  static const char scriptString[] = "<script";
  static const char styleString[] = "<style";
  for (const Attribute& attr : element->attributes()) {
    AtomicString name = attr.localName().lowerASCII();
    AtomicString value = attr.value().lowerASCII();
    if (name.find(scriptString) != WTF::kNotFound ||
        name.find(styleString) != WTF::kNotFound ||
        value.find(scriptString) != WTF::kNotFound ||
        value.find(styleString) != WTF::kNotFound) {
      nonceable = false;
      break;
    }
  }

  UseCounter::count(
      element->document(),
      nonceable ? UseCounter::CleanScriptElementWithNonce
                : UseCounter::PotentiallyInjectedScriptElementWithNonce);

  return !RuntimeEnabledFeatures::
             experimentalContentSecurityPolicyFeaturesEnabled() ||
         nonceable;
}
