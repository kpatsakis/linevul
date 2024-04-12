void SelectionController::SelectClosestMisspellingFromHitTestResult(
    const HitTestResult& result,
    AppendTrailingWhitespace append_trailing_whitespace) {
  Node* inner_node = result.InnerNode();

  if (!inner_node || !inner_node->GetLayoutObject())
    return;

  const VisiblePositionInFlatTree& pos = VisiblePositionOfHitTestResult(result);
  if (pos.IsNull()) {
    UpdateSelectionForMouseDownDispatchingSelectStart(
        inner_node, SelectionInFlatTree(), TextGranularity::kWord,
        HandleVisibility::kNotVisible);
    return;
  }

  const PositionInFlatTree& marker_position =
      pos.DeepEquivalent().ParentAnchoredEquivalent();
  const DocumentMarker* const marker =
      inner_node->GetDocument().Markers().MarkerAtPosition(
          ToPositionInDOMTree(marker_position),
          DocumentMarker::MisspellingMarkers());
  if (!marker) {
    UpdateSelectionForMouseDownDispatchingSelectStart(
        inner_node, SelectionInFlatTree(), TextGranularity::kWord,
        HandleVisibility::kNotVisible);
    return;
  }

  Node* const container_node = marker_position.ComputeContainerNode();
  const PositionInFlatTree start(container_node, marker->StartOffset());
  const PositionInFlatTree end(container_node, marker->EndOffset());
  const VisibleSelectionInFlatTree& new_selection = CreateVisibleSelection(
      SelectionInFlatTree::Builder().Collapse(start).Extend(end).Build());
  const SelectionInFlatTree& adjusted_selection =
      append_trailing_whitespace == AppendTrailingWhitespace::kShouldAppend
          ? AdjustSelectionWithTrailingWhitespace(new_selection.AsSelection())
          : new_selection.AsSelection();
  UpdateSelectionForMouseDownDispatchingSelectStart(
      inner_node,
      ExpandSelectionToRespectUserSelectAll(inner_node, adjusted_selection),
      TextGranularity::kWord, HandleVisibility::kNotVisible);
}
