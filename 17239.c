Element* FrameSelection::RootEditableElementOrDocumentElement() const {
  Element* selection_root =
      ComputeVisibleSelectionInDOMTreeDeprecated().RootEditableElement();
  return selection_root ? selection_root : GetDocument().documentElement();
}
