bool Document::NeedsLayoutTreeUpdateForNode(const Node& node,
                                            bool ignore_adjacent_style) const {
  if (!node.CanParticipateInFlatTree())
    return false;
  if (!NeedsLayoutTreeUpdate())
    return false;
  if (!node.isConnected())
    return false;

  if (NeedsFullLayoutTreeUpdate() || node.NeedsStyleRecalc() ||
      node.NeedsStyleInvalidation())
    return true;
  for (const ContainerNode* ancestor = LayoutTreeBuilderTraversal::Parent(node);
       ancestor; ancestor = LayoutTreeBuilderTraversal::Parent(*ancestor)) {
    if (ShadowRoot* root = ancestor->GetShadowRoot()) {
      if (root->NeedsStyleRecalc() || root->NeedsStyleInvalidation() ||
          root->NeedsAdjacentStyleRecalc()) {
        return true;
      }
    }
    if (ancestor->NeedsStyleRecalc() || ancestor->NeedsStyleInvalidation() ||
        (ancestor->NeedsAdjacentStyleRecalc() && !ignore_adjacent_style)) {
      return true;
    }
  }
  return false;
}
