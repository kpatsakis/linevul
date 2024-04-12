void Layer::PauseAnimation(int animation_id, double time_offset) {
  layer_animation_controller_->PauseAnimation(animation_id, time_offset);
  SetNeedsCommit();
}
