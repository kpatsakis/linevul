bool FrameSelection::Contains(const LayoutPoint& point) {
  if (!GetDocument().GetLayoutView())
    return false;

  const VisibleSelectionInFlatTree& visible_selection =
      ComputeVisibleSelectionInFlatTree();
  if (!visible_selection.IsRange())
    return false;

  HitTestRequest request(HitTestRequest::kReadOnly | HitTestRequest::kActive);
  HitTestResult result(request, point);
  GetDocument().GetLayoutView()->HitTest(result);
  Node* inner_node = result.InnerNode();
  if (!inner_node || !inner_node->GetLayoutObject())
    return false;

  const VisiblePositionInFlatTree& visible_pos =
      CreateVisiblePosition(FromPositionInDOMTree<EditingInFlatTreeStrategy>(
          inner_node->GetLayoutObject()->PositionForPoint(
              result.LocalPoint())));
  if (visible_pos.IsNull())
    return false;

  const VisiblePositionInFlatTree& visible_start =
      visible_selection.VisibleStart();
  const VisiblePositionInFlatTree& visible_end = visible_selection.VisibleEnd();
  if (visible_start.IsNull() || visible_end.IsNull())
    return false;

  const PositionInFlatTree& start = visible_start.DeepEquivalent();
  const PositionInFlatTree& end = visible_end.DeepEquivalent();
  const PositionInFlatTree& pos = visible_pos.DeepEquivalent();
  return start.CompareTo(pos) <= 0 && pos.CompareTo(end) <= 0;
}
