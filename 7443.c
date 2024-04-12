Element* HTMLFormElement::ElementFromPastNamesMap(
    const AtomicString& past_name) {
  if (past_name.IsEmpty() || !past_names_map_)
    return nullptr;
  Element* element = past_names_map_->at(past_name);
#if DCHECK_IS_ON()
  if (!element)
    return nullptr;
  SECURITY_DCHECK(ToHTMLElement(element)->formOwner() == this);
  if (IsHTMLImageElement(*element)) {
    SECURITY_DCHECK(ImageElements().Find(element) != kNotFound);
  } else if (IsHTMLObjectElement(*element)) {
    SECURITY_DCHECK(ListedElements().Find(ToHTMLObjectElement(element)) !=
                    kNotFound);
  } else {
    SECURITY_DCHECK(ListedElements().Find(ToHTMLFormControlElement(element)) !=
                    kNotFound);
  }
#endif
  return element;
}
