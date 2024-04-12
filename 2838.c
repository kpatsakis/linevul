void HTMLStyleElement::setDisabled(bool set_disabled) {
  if (CSSStyleSheet* style_sheet = sheet())
    style_sheet->setDisabled(set_disabled);
}
