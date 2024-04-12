static bool ShouldRespectSVGTextBoundaries(
    const Node& target_node,
    const FrameSelection& frame_selection) {
  const PositionInFlatTree& base =
      frame_selection.ComputeVisibleSelectionInFlatTree().Base();
  const Node* const base_node = base.AnchorNode();
  if (!base_node)
    return false;
  LayoutObject* const base_layout_object = base_node->GetLayoutObject();
  if (!base_layout_object || !base_layout_object->IsSVGText())
    return false;
  return target_node.GetLayoutObject()->ContainingBlock() !=
         base_layout_object->ContainingBlock();
}
