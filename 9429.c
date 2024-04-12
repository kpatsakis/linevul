void SelectionEditor::DidSplitTextNode(const Text& old_node) {
  if (selection_.IsNone() || !old_node.isConnected()) {
    DidFinishDOMMutation();
    return;
  }
  const Position& new_base =
      UpdatePostionAfterAdoptingTextNodeSplit(selection_.base_, old_node);
  const Position& new_extent =
      UpdatePostionAfterAdoptingTextNodeSplit(selection_.extent_, old_node);
  DidFinishTextChange(new_base, new_extent);
}
