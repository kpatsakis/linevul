ConversionContext::~ConversionContext() {
  while (state_stack_.size()) {
    if (state_stack_.back().type == StateEntry::kEffect)
      EndEffect();
    else
      EndClip();
  }
  EndTransform();
  if (translated_for_layer_offset_)
    AppendRestore(1);
}
