void Tab::AnimationEnded(const gfx::Animation* animation) {
  DCHECK_EQ(animation, &title_animation_);
  title_->SetBoundsRect(target_title_bounds_);
}
