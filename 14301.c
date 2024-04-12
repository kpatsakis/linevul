bool SelectionController::HandleGestureLongPress(
    const HitTestResult& hit_test_result) {
  TRACE_EVENT0("blink", "SelectionController::handleGestureLongPress");

  if (!Selection().IsAvailable())
    return false;
  if (hit_test_result.IsLiveLink())
    return false;

  Node* inner_node = hit_test_result.InnerNode();
  inner_node->GetDocument().UpdateStyleAndLayoutTree();
  bool inner_node_is_selectable = HasEditableStyle(*inner_node) ||
                                  inner_node->IsTextNode() ||
                                  inner_node->CanStartSelection();
  if (!inner_node_is_selectable)
    return false;

  if (SelectClosestWordFromHitTestResult(hit_test_result,
                                         AppendTrailingWhitespace::kDontAppend,
                                         SelectInputEventType::kTouch))
    return Selection().IsAvailable();

  if (!inner_node->isConnected() || !inner_node->GetLayoutObject())
    return false;
  SetCaretAtHitTestResult(hit_test_result);
  return false;
}
