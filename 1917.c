static bool NodeHasAncestor(const TransformPaintPropertyNode* node,
                            const TransformPaintPropertyNode* ancestor) {
  while (node) {
    if (node == ancestor)
      return true;
    node = node->Parent();
  }
  return false;
}
