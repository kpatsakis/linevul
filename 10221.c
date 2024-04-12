bool Editor::canCut() const {
  return canCopy() && canDelete();
}
