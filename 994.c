bool IsScrolledBy(LayerImpl* child, ScrollNode* ancestor) {
  DCHECK(ancestor && ancestor->scrollable);
  if (!child)
    return false;

  auto* property_trees = child->layer_tree_impl()->property_trees();
  ScrollTree& scroll_tree = property_trees->scroll_tree;
  for (ScrollNode* scroll_node = scroll_tree.Node(child->scroll_tree_index());
       scroll_node; scroll_node = scroll_tree.parent(scroll_node)) {
    if (scroll_node->id == ancestor->id)
      return true;
  }
  return false;
}
