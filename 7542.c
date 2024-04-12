Vector<String> HTMLInputElement::AcceptMIMETypes() const {
  return ParseAcceptAttribute(FastGetAttribute(acceptAttr), IsValidMIMEType);
}
