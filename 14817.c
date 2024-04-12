void TreeView::RecursivelyDelete(NodeDetails* node) {
  DCHECK(node);
  HTREEITEM item = node->tree_item;
  DCHECK(item);

  for (HTREEITEM child = TreeView_GetChild(tree_view_, item); child ;) {
    HTREEITEM next = TreeView_GetNextSibling(tree_view_, child);
    RecursivelyDelete(GetNodeDetailsByTreeItem(child));
    child = next;
  }

  TreeView_DeleteItem(tree_view_, item);

  id_to_details_map_.erase(node->id);
  node_to_details_map_.erase(node->node);
  delete node;
}
