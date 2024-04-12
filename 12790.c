void LockScreenMediaControlsView::RunResetControlsAnimation() {
  ui::ScopedLayerAnimationSettings animation(
      contents_view_->layer()->GetAnimator());
  animation.SetPreemptionStrategy(
      ui::LayerAnimator::IMMEDIATELY_ANIMATE_TO_NEW_TARGET);
  animation.SetTransitionDuration(kAnimationDuration);

  contents_view_->layer()->SetTransform(gfx::Transform());
  contents_view_->layer()->SetOpacity(1);
}
