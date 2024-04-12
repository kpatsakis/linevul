HTMLLinkElement* Document::LinkManifest() const {
  HTMLHeadElement* head = this->head();
  if (!head)
    return 0;

  for (HTMLLinkElement* link_element =
           Traversal<HTMLLinkElement>::FirstChild(*head);
       link_element;
       link_element = Traversal<HTMLLinkElement>::NextSibling(*link_element)) {
    if (!link_element->RelAttribute().IsManifest())
      continue;
    return link_element;
  }

  return 0;
}
