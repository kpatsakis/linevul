void ConversionContext::PopState() {
  DCHECK_EQ(nullptr, previous_transform_);

  const auto& previous_state = state_stack_.back();
  AppendRestore(previous_state.saved_count);
  current_transform_ = previous_state.transform;
  previous_transform_ = previous_state.previous_transform;
  current_clip_ = previous_state.clip;
  current_effect_ = previous_state.effect;
  state_stack_.pop_back();
}
