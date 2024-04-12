const SelectionInDOMTree& SelectionEditor::GetSelectionInDOMTree() const {
  AssertSelectionValid();
  return selection_;
}
