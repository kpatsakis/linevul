void SelectionEditor::AssertSelectionValid() const {
#if DCHECK_IS_ON()
  const_cast<SelectionEditor*>(this)->selection_.dom_tree_version_ =
      GetDocument().DomTreeVersion();
#endif
  selection_.AssertValidFor(GetDocument());
}
