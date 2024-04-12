  bool IsNewNode(const AXNode* node) {
    return new_nodes.find(node) != new_nodes.end();
  }
