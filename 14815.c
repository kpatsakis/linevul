bool Editor::canCopy() const {
  if (imageElementFromImageDocument(frame().document()))
    return true;
  FrameSelection& selection = frame().selection();
  return selection.computeVisibleSelectionInDOMTreeDeprecated().isRange() &&
         !selection.isInPasswordField();
}
