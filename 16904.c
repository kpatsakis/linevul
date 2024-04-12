const VisibleSelection& SelectionEditor::ComputeVisibleSelectionInDOMTree()
    const {
  DCHECK_EQ(GetFrame()->GetDocument(), GetDocument());
  DCHECK_EQ(GetFrame(), GetDocument().GetFrame());
  UpdateCachedVisibleSelectionIfNeeded();
  if (cached_visible_selection_in_dom_tree_.IsNone())
    return cached_visible_selection_in_dom_tree_;
  DCHECK_EQ(cached_visible_selection_in_dom_tree_.Base().GetDocument(),
            GetDocument());
  return cached_visible_selection_in_dom_tree_;
}
