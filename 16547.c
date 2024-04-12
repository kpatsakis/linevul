  bool IsChangedNode(const AXNode* node) {
    return changed_node_ids.find(node->id()) != changed_node_ids.end();
  }
