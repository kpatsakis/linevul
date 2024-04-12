void Document::ActiveChainNodeDetached(Element& element) {
  if (active_element_ && element == active_element_) {
    active_element_ =
        SkipDisplayNoneAncestorsOrReturnNullIfFlatTreeIsDirty(element);
  }
}
