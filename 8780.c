void TabletModeWindowManager::StopWindowAnimations() {
  for (auto& pair : window_state_map_)
    pair.first->layer()->GetAnimator()->StopAnimating();
}
