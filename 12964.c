void ShelfLayoutManager::OnOverviewModeStartingAnimationComplete(
    bool canceled) {
  UpdateVisibilityState();
  MaybeUpdateShelfBackground(AnimationChangeType::ANIMATE);
}
