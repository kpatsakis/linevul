void TabAnimationDelegate::AnimationProgressed(
    const gfx::Animation* animation) {
  tab_->SetVisible(tab_strip_->ShouldTabBeVisible(tab_));
}
