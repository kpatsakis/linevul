bool TestNavigationManager::WaitForRequestStart() {
  DCHECK(desired_state_ == NavigationState::STARTED);
  return WaitForDesiredState();
}
