void InputMethodController::Clear() {
  has_composition_ = false;
  if (composition_range_) {
    composition_range_->setStart(&GetDocument(), 0);
    composition_range_->collapse(true);
  }
  GetDocument().Markers().RemoveMarkersOfTypes(DocumentMarker::kComposition);
}
