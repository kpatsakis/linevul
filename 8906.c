static Position UpdatePostionAfterAdoptingTextNodesMerged(
    const Position& position,
    const Text& merged_node,
    const NodeWithIndex& node_to_be_removed_with_index,
    unsigned old_length) {
  Node* const anchor_node = position.AnchorNode();
  const Node& node_to_be_removed = node_to_be_removed_with_index.GetNode();
  switch (position.AnchorType()) {
    case PositionAnchorType::kBeforeChildren:
    case PositionAnchorType::kAfterChildren:
      return position;
    case PositionAnchorType::kBeforeAnchor:
      if (anchor_node == node_to_be_removed)
        return Position(merged_node, merged_node.length());
      return position;
    case PositionAnchorType::kAfterAnchor:
      if (anchor_node == node_to_be_removed)
        return Position(merged_node, merged_node.length());
      if (anchor_node == merged_node)
        return Position(merged_node, old_length);
      return position;
    case PositionAnchorType::kOffsetInAnchor: {
      const int offset = position.OffsetInContainerNode();
      if (anchor_node == node_to_be_removed)
        return Position(merged_node, old_length + offset);
      if (anchor_node == node_to_be_removed.parentNode() &&
          offset == node_to_be_removed_with_index.Index()) {
        return Position(merged_node, old_length);
      }
      return position;
    }
  }
  NOTREACHED() << position;
  return position;
}
