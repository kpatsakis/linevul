void ShelfBackgroundAnimator::OnBackgroundTypeChanged(
    ShelfBackgroundType background_type,
    AnimationChangeType change_type) {
  PaintBackground(background_type, change_type);
}
