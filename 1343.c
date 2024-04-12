void HTMLFormControlElement::formAction(USVStringOrTrustedURL& result) const {
  const AtomicString& action = FastGetAttribute(kFormactionAttr);
  if (action.IsEmpty()) {
    result.SetUSVString(GetDocument().Url());
    return;
  }
  result.SetUSVString(
      GetDocument().CompleteURL(StripLeadingAndTrailingHTMLSpaces(action)));
}
