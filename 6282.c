String HTMLInputElement::AltText() const {
  String alt = FastGetAttribute(altAttr);
  if (alt.IsNull())
    alt = FastGetAttribute(titleAttr);
  if (alt.IsNull())
    alt = FastGetAttribute(valueAttr);
  if (alt.IsNull())
    alt = GetLocale().QueryString(WebLocalizedString::kInputElementAltText);
  return alt;
}
