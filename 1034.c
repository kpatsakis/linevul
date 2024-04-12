void FrameSelection::Clear() {
  granularity_ = TextGranularity::kCharacter;
  if (granularity_strategy_)
    granularity_strategy_->Clear();
  SetSelectionAndEndTyping(SelectionInDOMTree());
  is_handle_visible_ = false;
  is_directional_ = ShouldAlwaysUseDirectionalSelection(frame_);
}
