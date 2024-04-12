void VoiceInteractionOverlay::HideAnimation() {
  animation_state_ = AnimationState::HIDDEN;

  {
    ui::ScopedLayerAnimationSettings settings(ripple_layer_->GetAnimator());
    settings.SetTransitionDuration(
        base::TimeDelta::FromMilliseconds(kHideDurationMs));
    settings.SetTweenType(gfx::Tween::LINEAR_OUT_SLOW_IN);
    settings.SetPreemptionStrategy(
        ui::LayerAnimator::PreemptionStrategy::ENQUEUE_NEW_ANIMATION);

    ripple_layer_->SetOpacity(0);
  }

  {
    ui::ScopedLayerAnimationSettings settings(icon_layer_->GetAnimator());
    settings.SetTransitionDuration(
        base::TimeDelta::FromMilliseconds(kHideDurationMs));
    settings.SetTweenType(gfx::Tween::LINEAR_OUT_SLOW_IN);
    settings.SetPreemptionStrategy(
        ui::LayerAnimator::PreemptionStrategy::ENQUEUE_NEW_ANIMATION);

    icon_layer_->SetOpacity(0);
    icon_layer_->StopAnimation();
  }

  {
    ui::ScopedLayerAnimationSettings settings(background_layer_->GetAnimator());
    settings.SetTransitionDuration(
        base::TimeDelta::FromMilliseconds(kHideDurationMs));
    settings.SetTweenType(gfx::Tween::LINEAR_OUT_SLOW_IN);
    settings.SetPreemptionStrategy(
        ui::LayerAnimator::PreemptionStrategy::ENQUEUE_NEW_ANIMATION);

    background_layer_->SetOpacity(0);
  }
}
