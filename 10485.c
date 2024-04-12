bool NavigationControllerImpl::CanGoForward() const {
  int index = GetCurrentEntryIndex();
  return index >= 0 && index < (static_cast<int>(entries_.size()) - 1);
}
