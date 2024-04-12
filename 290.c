void AutomationInternalCustomBindings::OnAtomicUpdateFinished(
    ui::AXTree* tree,
    bool root_changed,
    const std::vector<ui::AXTreeDelegate::Change>& changes) {
  auto iter = axtree_to_tree_cache_map_.find(tree);
  if (iter == axtree_to_tree_cache_map_.end())
    return;

  for (const auto change : changes) {
    ui::AXNode* node = change.node;
    switch (change.type) {
      case NODE_CREATED:
        SendTreeChangeEvent(
            api::automation::TREE_CHANGE_TYPE_NODECREATED,
            tree, node);
        break;
      case SUBTREE_CREATED:
        SendTreeChangeEvent(
            api::automation::TREE_CHANGE_TYPE_SUBTREECREATED,
            tree, node);
        break;
      case NODE_CHANGED:
        SendTreeChangeEvent(
            api::automation::TREE_CHANGE_TYPE_NODECHANGED,
            tree, node);
        break;
    }
  }

  for (int id : text_changed_node_ids_) {
    SendTreeChangeEvent(api::automation::TREE_CHANGE_TYPE_TEXTCHANGED, tree,
                        tree->GetFromId(id));
  }
  text_changed_node_ids_.clear();
}
