void InfoBar::AnimationEnded(const ui::Animation* animation) {
  if (container_) {
    container_->InfoBarAnimated(false);

    if (!animation_->IsShowing())
      Close();
  }
}
