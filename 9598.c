void NavigationControllerImpl::GoToIndex(int index) {
  TRACE_EVENT0("browser,navigation,benchmark",
               "NavigationControllerImpl::GoToIndex");
  if (index < 0 || index >= static_cast<int>(entries_.size())) {
    NOTREACHED();
    return;
  }

  if (transient_entry_index_ != -1) {
    if (index == transient_entry_index_) {
      return;
    }
    if (index > transient_entry_index_) {
      index--;
    }
  }

  DiscardNonCommittedEntries();

  DCHECK_EQ(nullptr, pending_entry_);
  DCHECK_EQ(-1, pending_entry_index_);
  pending_entry_ = entries_[index].get();
  pending_entry_index_ = index;
  pending_entry_->SetTransitionType(ui::PageTransitionFromInt(
      pending_entry_->GetTransitionType() | ui::PAGE_TRANSITION_FORWARD_BACK));
  NavigateToPendingEntry(ReloadType::NONE);
}
