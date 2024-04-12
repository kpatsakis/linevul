void TreeView::CommitEdit() {
  DCHECK(tree_view_);
  TreeView_EndEditLabelNow(tree_view_, FALSE);
}
