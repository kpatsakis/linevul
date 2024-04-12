static bool EnabledSelectAll(LocalFrame& frame,
                             Event*,
                             EditorCommandSource source) {
  frame.GetDocument()->UpdateStyleAndLayoutIgnorePendingStylesheets();
  const VisibleSelection& selection =
      frame.Selection().ComputeVisibleSelectionInDOMTree();
  if (selection.IsNone())
    return true;
  if (source == kCommandFromMenuOrKeyBinding && frame.Selection().IsHidden())
    return true;
  if (Node* root = HighestEditableRoot(selection.Start())) {
    if (!root->hasChildren())
      return false;
  }
  return true;
}
