GranularityStrategy* FrameSelection::GetGranularityStrategy() {
  SelectionStrategy strategy_type = SelectionStrategy::kCharacter;
  Settings* settings = frame_ ? frame_->GetSettings() : nullptr;
  if (settings &&
      settings->GetSelectionStrategy() == SelectionStrategy::kDirection)
    strategy_type = SelectionStrategy::kDirection;

  if (granularity_strategy_ &&
      granularity_strategy_->GetType() == strategy_type)
    return granularity_strategy_.get();

  if (strategy_type == SelectionStrategy::kDirection)
    granularity_strategy_ = std::make_unique<DirectionGranularityStrategy>();
  else
    granularity_strategy_ = std::make_unique<CharacterGranularityStrategy>();
  return granularity_strategy_.get();
}
