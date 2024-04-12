static Position ComputePositionForChildrenRemoval(const Position& position,
                                                  ContainerNode& container) {
  Node* node = position.ComputeContainerNode();
  if (container.ContainsIncludingHostElements(*node))
    return Position::FirstPositionInNode(container);
  return position;
}
