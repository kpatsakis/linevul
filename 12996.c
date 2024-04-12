void ShelfBackgroundAnimator::AnimateBackground(
    ShelfBackgroundType background_type,
    AnimationChangeType change_type) {
  StopAnimator();

  if (change_type == AnimationChangeType::IMMEDIATE) {
    animator_.reset();
    SetTargetValues(background_type);
    SetAnimationValues(1.0);
  } else if (CanReuseAnimator(background_type)) {
    if (animator_->IsShowing())
      animator_->Hide();
    else
      animator_->Show();
  } else {
    CreateAnimator(background_type);
    SetTargetValues(background_type);
    animator_->Show();
  }

  if (target_background_type_ != background_type) {
    previous_background_type_ = target_background_type_;
    target_background_type_ = background_type;
  }
}
