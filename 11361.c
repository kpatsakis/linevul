void NavigationControllerImpl::SetTransientEntry(
    std::unique_ptr<NavigationEntry> entry) {
  int index = 0;
  if (last_committed_entry_index_ != -1)
    index = last_committed_entry_index_ + 1;
  DiscardTransientEntry();
  entries_.insert(entries_.begin() + index,
                  NavigationEntryImpl::FromNavigationEntry(std::move(entry)));
  transient_entry_index_ = index;
  delegate_->NotifyNavigationStateChanged(INVALIDATE_TYPE_ALL);
}
